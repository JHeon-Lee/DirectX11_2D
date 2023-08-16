#pragma once

// �⺻���� �ʱ�ȭ �۾�

/*
DirectX 11
DirectX June 2010 SDK
software development kit
*/
class D3DEnumAdapterInfo;
class D3DEnumOutputInfo;

class Graphics : public SingletonBase<Graphics>
{
public:
	friend class SingletonBase<Graphics>;

	ID3D11Device* GetDevice() { return device;}
	ID3D11DeviceContext* GetDC() { return deviceContext; }
	
	void Resize(const UINT& width, const UINT& height);
	void SetViewport(const UINT& width, const UINT& height);
	void InitViewport();

	void Begin();
	void End();

	void GUI();
private:
	void CreateSwapchain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:
	Graphics();
	~Graphics();

private:
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo);


private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport;
	D3DXCOLOR clearColor = 0xff555566;

	UINT numerator = 0;
	UINT denominator = 1;

	UINT gpuMemorySize;
	wstring gpuName;

	vector<D3DEnumAdapterInfo*> adapterInfos;
	int selectedAdapterIndex = 0;

	bool bVsync = true;
};

class D3DEnumAdapterInfo
{
public:
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	IDXGIAdapter1* adapter = nullptr;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	D3DEnumOutputInfo* outputInfo = nullptr;
};

class D3DEnumOutputInfo
{
public:
	~D3DEnumOutputInfo();

	IDXGIOutput* output = nullptr;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	UINT numerator = 0;
	UINT denominator = 1;
};

/*
	ID3D11Device
		- GPU�� ������ �� �ִ� �������̽�
		- ��� ���� ���˰� �ڿ� �Ҵ翡 ���

	ID3D11DeviceContext
		- ������ ����� �����ϴ� ����̽� ���ؽ�Ʈ(DeviceContext)�� ��Ÿ��
	
	DeviceContext
		- �׷��� ���������ο� ���� ���¸� ����, ���ҽ� ����, ���ε�, �����ϴ� ����

	IDXGISwapChain
		- DirectX �׷��� API���� ��µ� ����� ���÷��̿� �����ֱ� ���� �������̽�
		- �� ���ۿ� ����Ʈ ���۸� ����
			- �� ���� : ���� �������� ������ ����� �ӽ÷� �����ϴ� ����
			- ����Ʈ ���� : ���� ȭ�鿡 �������� �̹����� ��� �ִ� ����
		- �� ���ۿ� ����Ʈ ���۸� ��ü�Ͽ� ���÷��̿� �̹����� �����ִµ� �̸� '����' �̶�� ��
	
	DXGI
		- DirectX �׷��� ��Ÿ�Ӱ� �������� �� �ִ� ���� ���� �۾��� ����
			1) �׷��� ����� ����
			2) ���÷��� ��� ����
			3) ���� ���� ����
			4) ���μ��� �� �ڿ� ����
			5) �������� �������� ���� ���� â �Ǵ� ����Ϳ� ǥ���ϴ� �۾�

	ID3D11RenderTargetView
		- ���� Ÿ���� ��Ÿ���� �������̽�
		- OM �ܰ�(��� ���� �ܰ�) ���� ���� ������ ���ҽ�

	D3D11_VIEWPORT
		- ī�޶��� �þ߸� ��Ÿ���� �簢�� ����
*/

// I : interface -> release�� �Ҵ� ����(new -> delete ó��)