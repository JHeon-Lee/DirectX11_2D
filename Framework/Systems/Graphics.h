#pragma once

// 기본적인 초기화 작업

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
		- GPU를 제어할 수 있는 인터페이스
		- 기능 지원 점검과 자원 할당에 사용

	ID3D11DeviceContext
		- 렌더링 명령을 생성하는 디바이스 컨텍스트(DeviceContext)를 나타냄
	
	DeviceContext
		- 그래픽 파이프라인에 대한 상태를 설정, 리소스 생성, 바인딩, 실행하는 역할

	IDXGISwapChain
		- DirectX 그래픽 API에서 출력된 결과를 디스플레이에 보여주기 위한 인터페이스
		- 백 버퍼와 프론트 버퍼를 관리
			- 백 버퍼 : 다음 프레임의 렌더링 결과를 임시로 저장하는 버퍼
			- 프론트 버퍼 : 현재 화면에 보여지는 이미지를 담고 있는 버퍼
		- 백 버퍼와 프론트 버퍼를 교체하여 디스플레이에 이미지를 보여주는데 이를 '스왑' 이라고 함
	
	DXGI
		- DirectX 그래픽 런타임과 독립적일 수 있는 하위 수준 작업을 관리
			1) 그래픽 어댑터 열기
			2) 디스플레이 모드 열거
			3) 버퍼 형식 선택
			4) 프로세스 간 자원 공유
			5) 렌더링된 프레임을 띄우기 위한 창 또는 모니터에 표시하는 작업

	ID3D11RenderTargetView
		- 렌더 타겟을 나타내는 인터페이스
		- OM 단계(출력 병합 단계) 에서 쓰기 가능한 리소스

	D3D11_VIEWPORT
		- 카메라의 시야를 나타내는 사각형 영역
*/

// I : interface -> release로 할당 해제(new -> delete 처럼)