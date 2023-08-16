#include "Framework.h"
#include "Graphics.h"

void Graphics::Resize(const UINT & width, const UINT & height) // 크기 조정시
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

void Graphics::SetViewport(const UINT & width, const UINT & height) // Viewport 설정
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

void Graphics::Begin() // TODO : 렌더링 파이프라인 알아봐야함, 단계 외우기 -->> 면접에 나올 수 있음
{
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	deviceContext->RSSetViewports(1, &viewport);
	deviceContext->ClearRenderTargetView(rtv, clearColor);
}

void Graphics::End()
{
	// Front, Back 버퍼 넘기는 과정
	HRESULT hr = swapChain->Present(bVsync == true ?  1 : 0, 0); // bVsync : 수직동기화 -> 티어링 방지
	assert(SUCCEEDED(hr));
}

void Graphics::GUI()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ 0, 15 });
	ImGui::SetNextWindowSize(ImVec2(200, 30)); // 위젯 창 크기 설정
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

	// 버퍼의 쓰임새 정의
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering
		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0; // 안티앨리어싱 --> 4배 or 8배 설정한 늘린 화면으로 보여줌
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
			// 기수 / 서수
			// 일이삼사 첫번째 두번째
		adapter->GetDesc1(&adapterInfo->adapterDesc);
		adapterInfo->adapter = adapter;

		EnumerateAdapterOutput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		index++;
	}
	SAFE_RELEASE(factory);
}

bool Graphics::EnumerateAdapterOutput(D3DEnumAdapterInfo * adapterInfo) // 모니터 내용 검사
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
		- 3D 그래픽의 출력 결과를 생성하기 위해 여러 단계를 거쳐 처리하는 과정
		- CPU와 GPU의 협업으로 이루어짐

	1. IA (입력 어셈블러, InputAssembler)
		- 정점 버퍼와 인덱스 버퍼를 사용하여 기본 도형(프리미티브)을 생성

	2. VS (정점 쉐이더, Vertex Shader)
		- IA에서 생성된 프리미티브에 대한 버텍스 데이터를 처리
		- 각각의 버텍스는 정점 위치, 텍스처 좌표, 노멀 벡터 등의 정보를 가지고 있다
		- 이러한 정보를 바탕으로 쉐이더는 각 버텍스의 최종 위치를 계산

	3. HS (헐 쉐이더, Hull Shader)
		- 공간 분할 단계 중 하나로, 모델의 한 표면을 효율적으로 많은 삼각형으로 나눈다
		- 각 입력 패치(사각형, 삼각형 또는 선)에 해당하는 기하 도형 패치(및 패치 상수)를 생성
		- 헐 셰이더는 패치당 한번 호출되어, 낮은 차수의 표면을 정의하는 입력 제어점을 패치를 구성하는 제어점으로 변환

	4. TS (분할기, Tessellator)
		- 테셀레이션 단계는 하드웨어에서 테셀레이션을 구현
		- 그래픽 파이프라인은 낮은 디테일(낮은 다각형 수) 모델을 평가하고 더 높은 디테일로 렌더링 할 수 있다
		- 낮은 차수의 표면을 Direct3D 그래픽 파이프라인 내에서 자세한 렌더링을 위한 많은 삼각형으로 변하는데에 함께 작동

	5. DS (도메인 쉐이더, Domain Shader)
		- 출력 패치의 세분화된 지점의 꼭지점 위치를 출력
		- 테셀레이션에서 생성된 패치 정보를 받아서, 모델을 구성하는 도형을 만듬

	6. GS (지오메트리 쉐이더, Geometry Shader)
		- 도메인 쉐이더에서 생성된 도형 정보를 가지고 추가적인 변환을 수행하거나, 기하학적 모양을 만들어낸다

	7. SO (스트림 출력, Stream Output)
		- 정점 데이터를 갭처하고 저장

	8. RS (레스터라이저, Rasterizer)
		- 3D 공간에서 저장된 3D 모델을 2D 화면으로 변환하는 과정
		- 각 3D 폴리곤을 2D 픽셀로 변환하고, 이 픽셀에 대한 정보(색상, 깊이 등) 을 계산하여 RTV에 출력

	9. PS (픽셀 쉐이더, Pixel Shader)
		- 화면에 출력되는 각 픽셀에 대한 정보(색상, 깊이 등)를 계산
		- 모델이 화면에서 차지하는 픽셀의 개수만큼 픽셀 쉐이더가 실행
		- 색상, 그림자, 광원 등을 계산하여 화면에 출력

	10. OM (출력 병합기, Output Merger)
		- 렌더링된 픽셀을 프레임 버퍼에 병합

	참고 사이트 : 
	https://learn.microsoft.com/ko-kr/windows/uwp/graphics-concepts/graphics-pipeline

	World - SRT(scale, rotation, translation) View, Projection

	3 ~ 5 : 공간분할 단계(Tessellation Stage)

	3 ~ 8 : 3D 쪽 영역

	Homework : 렌더링 파이프라인 최대한 상세하게 적어보기
*/