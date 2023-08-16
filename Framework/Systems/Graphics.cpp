#include "Framework.h"
#include "Graphics.h"

void Graphics::Resize(const UINT & width, const UINT & height) // ũ�� ������
{
	DeleteSurface();
	{
		HRESULT hr = swapChain->ResizeBuffers
		(
			0,
			width,
			height,
			DXGI_FORMAT_UNKNOWN,
			0
		);
		assert(SUCCEEDED(hr));
	}
	CreateRenderTargetView();
	SetViewport(width, height);

}

void Graphics::SetViewport(const UINT & width, const UINT & height) // Viewport ����
{
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::InitViewport()
{
	deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::Begin() // TODO : ������ ���������� �˾ƺ�����, �ܰ� �ܿ�� -->> ������ ���� �� ����
{
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	deviceContext->RSSetViewports(1, &viewport);
	deviceContext->ClearRenderTargetView(rtv, clearColor);
}

void Graphics::End()
{
	// Front, Back ���� �ѱ�� ����
	HRESULT hr = swapChain->Present(bVsync == true ?  1 : 0, 0); // bVsync : ��������ȭ -> Ƽ� ����
	assert(SUCCEEDED(hr));
}

void Graphics::GUI()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ 0, 15 });
	ImGui::SetNextWindowSize(ImVec2(200, 30)); // ���� â ũ�� ����
	ImGui::Begin
	(
		"Vstnc", 
		&bOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar
	);
	{
		ImGui::Checkbox("##Vsync", &bVsync);
	}
	ImGui::End();
}

void Graphics::CreateSwapchain()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(swapChain);

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;

	if (bVsync)
	{
		desc.BufferDesc.RefreshRate.Numerator = adapterInfos[0]->outputInfo->numerator;
		desc.BufferDesc.RefreshRate.Denominator = adapterInfos[0]->outputInfo->denominator;
	}
	else
	{
		desc.BufferDesc.RefreshRate.Numerator = 0;
		desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// ������ ���ӻ� ����
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering
		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0; // ��Ƽ�ٸ���� --> 4�� or 8�� ������ �ø� ȭ������ ������
	desc.OutputWindow = handle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	

	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT maxVRam = 0;
	for (UINT i = 0; i < adapterInfos.size(); i++)
	{
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVRam)
		{
			selectedAdapterIndex = i;
			maxVRam = adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	for (int i = 0; i < adapterInfos.size(); i++)
	{
		gpuName = adapterInfos[i]->adapterDesc.Description;
		wcout << "GPU Name : " << adapterInfos[i]->adapterDesc.Description << endl;
		cout << "VRAM : " << adapterInfos[i]->adapterDesc.DedicatedVideoMemory << endl;
		cout << endl;
	}

	wcout << "Selected GPU Name : " 
		<< adapterInfos[selectedAdapterIndex]->
		adapterDesc.Description << endl;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		adapterInfos[selectedAdapterIndex]->adapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		0,
		featureLevel.data(),
		featureLevel.size(),
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		nullptr,
		&deviceContext
	);
	assert(SUCCEEDED(hr));

	Resize(WinMaxWidth, WinMaxHeight);
}

void Graphics::CreateRenderTargetView()
{
	ID3D11Texture2D* backbuffer = nullptr;
	HRESULT hr = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backbuffer
	);
	assert(SUCCEEDED(hr));

	hr = device->CreateRenderTargetView
	(
		backbuffer,
		nullptr,
		&rtv
	);
	assert(SUCCEEDED(hr));
	SAFE_RELEASE(backbuffer);
}

void Graphics::DeleteSurface()
{
	SAFE_RELEASE(rtv);
}

Graphics::Graphics()
{
	EnumerateAdapters();
	CreateSwapchain();
}

Graphics::~Graphics()
{
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

void Graphics::EnumerateAdapters()
{
	IDXGIFactory1* factory;
	if(FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
		return;

	UINT index = 0;
	while (true)
	{
		IDXGIAdapter1* adapter = nullptr;
		HRESULT hr = factory->EnumAdapters1(index, &adapter);
		if (hr == DXGI_ERROR_NOT_FOUND)
			break;
		assert(SUCCEEDED(hr));

		D3DEnumAdapterInfo* adapterInfo = new D3DEnumAdapterInfo();
		ZeroMemory(adapterInfo, sizeof(D3DEnumAdapterInfo));
		adapterInfo->adapterOrdinal = index;
			// ��� / ����
			// ���̻�� ù��° �ι�°
		adapter->GetDesc1(&adapterInfo->adapterDesc);
		adapterInfo->adapter = adapter;

		EnumerateAdapterOutput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		index++;
	}
	SAFE_RELEASE(factory);
}

bool Graphics::EnumerateAdapterOutput(D3DEnumAdapterInfo * adapterInfo) // ����� ���� �˻�
{
	IDXGIOutput* output = nullptr;
	HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &output);

	if (DXGI_ERROR_NOT_FOUND == hr)
		return false;
	assert(SUCCEEDED(hr));

	D3DEnumOutputInfo* outputInfo = new D3DEnumOutputInfo();
	ZeroMemory(outputInfo, sizeof(D3DEnumOutputInfo));

	output->GetDesc(&outputInfo->outputDesc);
	outputInfo->output = output;

	UINT numModes = 0;
	DXGI_MODE_DESC* displayModes = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	assert(SUCCEEDED(hr));

	displayModes = new DXGI_MODE_DESC[numModes];
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);
	assert(SUCCEEDED(hr));

	for (UINT i = 0; i < numModes; i++)
	{
		bool bCheck = true;
		bCheck &= displayModes[i].Width == WinMaxWidth;
		bCheck &= displayModes[i].Height == WinMaxHeight;

		if (bCheck == true)
		{
			outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
			outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
		}
	}

	adapterInfo->outputInfo = outputInfo;
	SAFE_DELETE_ARRAY(displayModes);
	return true;
}

D3DEnumAdapterInfo::~D3DEnumAdapterInfo()
{
	SAFE_RELEASE(adapter);
	SAFE_DELETE(outputInfo);
}

D3DEnumOutputInfo::~D3DEnumOutputInfo()
{
	SAFE_RELEASE(output);
}

/*
	Grapic Pipeline
		- 3D �׷����� ��� ����� �����ϱ� ���� ���� �ܰ踦 ���� ó���ϴ� ����
		- CPU�� GPU�� �������� �̷����

	1. IA (�Է� �����, InputAssembler)
		- ���� ���ۿ� �ε��� ���۸� ����Ͽ� �⺻ ����(������Ƽ��)�� ����

	2. VS (���� ���̴�, Vertex Shader)
		- IA���� ������ ������Ƽ�꿡 ���� ���ؽ� �����͸� ó��
		- ������ ���ؽ��� ���� ��ġ, �ؽ�ó ��ǥ, ��� ���� ���� ������ ������ �ִ�
		- �̷��� ������ �������� ���̴��� �� ���ؽ��� ���� ��ġ�� ���

	3. HS (�� ���̴�, Hull Shader)
		- ���� ���� �ܰ� �� �ϳ���, ���� �� ǥ���� ȿ�������� ���� �ﰢ������ ������
		- �� �Է� ��ġ(�簢��, �ﰢ�� �Ǵ� ��)�� �ش��ϴ� ���� ���� ��ġ(�� ��ġ ���)�� ����
		- �� ���̴��� ��ġ�� �ѹ� ȣ��Ǿ�, ���� ������ ǥ���� �����ϴ� �Է� �������� ��ġ�� �����ϴ� ���������� ��ȯ

	4. TS (���ұ�, Tessellator)
		- �׼����̼� �ܰ�� �ϵ����� �׼����̼��� ����
		- �׷��� ������������ ���� ������(���� �ٰ��� ��) ���� ���ϰ� �� ���� �����Ϸ� ������ �� �� �ִ�
		- ���� ������ ǥ���� Direct3D �׷��� ���������� ������ �ڼ��� �������� ���� ���� �ﰢ������ ���ϴµ��� �Բ� �۵�

	5. DS (������ ���̴�, Domain Shader)
		- ��� ��ġ�� ����ȭ�� ������ ������ ��ġ�� ���
		- �׼����̼ǿ��� ������ ��ġ ������ �޾Ƽ�, ���� �����ϴ� ������ ����

	6. GS (������Ʈ�� ���̴�, Geometry Shader)
		- ������ ���̴����� ������ ���� ������ ������ �߰����� ��ȯ�� �����ϰų�, �������� ����� ������

	7. SO (��Ʈ�� ���, Stream Output)
		- ���� �����͸� ��ó�ϰ� ����

	8. RS (�����Ͷ�����, Rasterizer)
		- 3D �������� ����� 3D ���� 2D ȭ������ ��ȯ�ϴ� ����
		- �� 3D �������� 2D �ȼ��� ��ȯ�ϰ�, �� �ȼ��� ���� ����(����, ���� ��) �� ����Ͽ� RTV�� ���

	9. PS (�ȼ� ���̴�, Pixel Shader)
		- ȭ�鿡 ��µǴ� �� �ȼ��� ���� ����(����, ���� ��)�� ���
		- ���� ȭ�鿡�� �����ϴ� �ȼ��� ������ŭ �ȼ� ���̴��� ����
		- ����, �׸���, ���� ���� ����Ͽ� ȭ�鿡 ���

	10. OM (��� ���ձ�, Output Merger)
		- �������� �ȼ��� ������ ���ۿ� ����

	���� ����Ʈ : 
	https://learn.microsoft.com/ko-kr/windows/uwp/graphics-concepts/graphics-pipeline

	World - SRT(scale, rotation, translation) View, Projection

	3 ~ 5 : �������� �ܰ�(Tessellation Stage)

	3 ~ 8 : 3D �� ����

	Homework : ������ ���������� �ִ��� ���ϰ� �����
*/