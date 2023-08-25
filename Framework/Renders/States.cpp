#include "Framework.h"
#include "States.h"

// static 변수들은 공간을 먼저 확보해둬야함
D3D11_RASTERIZER_DESC		States::rsDesc;
D3D11_DEPTH_STENCIL_DESC	States::dsDesc;
D3D11_SAMPLER_DESC			States::spDesc;
D3D11_BLEND_DESC			States::blDesc;

#define ZERO(p) ZeroMemory(&p, sizeof(p))

void States::Create()
{
	CreateRasterizerDesc();
	CreateDepthStencilDesc();
	CreateSamplerDesc();
	CreateBlendDesc();
}

void States::GetRasterizerDesc(D3D11_RASTERIZER_DESC* desc)
{
	memcpy(desc, &rsDesc, sizeof(D3D11_RASTERIZER_DESC));
}

void States::GetDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc)
{
	memcpy(desc, &dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
}

void States::GetSamplerDesc(D3D11_SAMPLER_DESC* desc)
{
	memcpy(desc, &spDesc, sizeof(D3D11_SAMPLER_DESC));
}

void States::GetBlendDesc(D3D11_BLEND_DESC* desc)
{
	memcpy(desc, &blDesc, sizeof(D3D11_BLEND_DESC));
}

void States::CreateRasterizer(D3D11_RASTERIZER_DESC* desc, ID3D11RasterizerState** state)
{
	HRESULT hr = DEVICE->CreateRasterizerState(desc, state);
	CHECK(hr);
}

void States::CreateDepthStencil(D3D11_DEPTH_STENCIL_DESC* desc, ID3D11DepthStencilState** state)
{
	HRESULT hr = DEVICE->CreateDepthStencilState(desc, state);
	CHECK(hr);
}

void States::CreateSampler(D3D11_SAMPLER_DESC* desc, ID3D11SamplerState** state)
{
	HRESULT hr = DEVICE->CreateSamplerState(desc, state);
	CHECK(hr);
}

void States::CreateBlend(D3D11_BLEND_DESC* desc, ID3D11BlendState** state)
{
	HRESULT hr = DEVICE->CreateBlendState(desc, state);
	CHECK(hr);
}

void States::CreateRasterizerDesc()
{
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.FillMode = D3D11_FILL_SOLID; // 다각형의 채우기 모드
	rsDesc.CullMode = D3D11_CULL_BACK; // 후면 컬링 사용 설정
	rsDesc.FrontCounterClockwise = false; // 전면 면의 방향을 시계방향으로 설정
	rsDesc.DepthBias = 0; // 깊이 바이어스 값
	rsDesc.DepthBiasClamp = 0.0f; // 깊이 바이어스 클램프 값
	rsDesc.SlopeScaledDepthBias = 0.0f; // 경사도에 따른 깊이 바이어스 값
	rsDesc.ScissorEnable = false; // 가위 테스트 사용 설정(렌더링 대상의 특정 영역만 렌더링 하는데 사용)
	rsDesc.MultisampleEnable = false; // 멀티 샘플링 사용 설정
	rsDesc.AntialiasedLineEnable = false; // 선 안티앨리어싱 사용 설정
}

void States::CreateDepthStencilDesc()
{
	ZERO(dsDesc);

	dsDesc.DepthEnable = true; // 깊이 테스트 사용 설정
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이 버퍼의 모든 비트에 대해 쓰기 작업 허용
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS; // 깊이 테스트 함수 LESS로 설정
	dsDesc.StencilEnable = true; // 스텐실 테스트 사용 설정
	dsDesc.StencilReadMask = 0xFF; // 스텐실 버퍼에서 읽을 수 이쓴 비트 마스크 설정
	dsDesc.StencilWriteMask = 0xFF; // 스텐실 테스트 사용 설정

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; // 전면 면의 스텐실 실패 작업 설정
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR; // 전면 면의 스텐실 싶이 실패 작업 설정
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; // 전면 면의 스텐실 패스 작업 설정
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // 전면 면의 스텐실 함수 설정

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
}

void States::CreateSamplerDesc()
{
	ZERO(spDesc);

	spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // 선형 필터링을 사용하여 텍스처를 샘플링
	spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // u 좌표에 대해 텍스처 좌표를 래핑
	spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; // v 좌표에 대해 텍스처 좌표를 래핑
	spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; // w 좌표에 대해 텍스처 좌표를 래핑
	spDesc.MaxAnisotropy = 1; // 아니소트로피 필터링에 사용 (여기서는 사용 안함)
	spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS; // 비교 샘플링에 사용 (여기서는 사용 안함)
	spDesc.MinLOD = FLT_MIN; // 텍스처의 최소 LOD 레벨 설정 (LOD : level of detail -> 거리에 따른 세밀도)
	spDesc.MaxLOD = FLT_MAX; // 텍스처의 최대 LOD 레벨 설정
}

void States::CreateBlendDesc()
{
	ZERO(blDesc);
	
	blDesc.AlphaToCoverageEnable = false; // alpha to coverage 사용 여부
	blDesc.IndependentBlendEnable = false; // 독립적인 블렌드 사용 여부

	blDesc.RenderTarget[0].BlendEnable = false; // 렌더 타겟에 대한 블렌딩 사용 여부
	blDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // 소스 색상에 대한 블렌드 인수를 설정
	blDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // 목적지 색상에 대한 블렌드 인수를 설정
	blDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // 색상에 대한 블렌드 연산을 설정

	blDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO; // 목적지 알파에 대한 블렌드 인수를 설정
	blDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE; // 소스 알파에 대한 블렌드 인수를 설정
	blDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // 알파에 대한 블렌드 연산을 설정

	blDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 모든 색상 채널이 렌더 타겟에 기록
}

/*
	Depth : 3D 그래픽에서 픽셀의 깊이를 나타내는 값
		- 보통 깊이 버퍼라는 2D 이미지 버퍼에 저장
		- 깊이 버퍼는 각 픽셀에 대해 깊이 값을 저장, 이 값은 렌더링 중에 테스트 및 업데이트
		- 깊이 버퍼를 사용하면 3D 장면에서 물체들이 올바른 순서로 겹쳐지도록 할 수 있음

	Depth Test
		- 렌더링된 픽셀의 깊이 값을 검사하여 렌더링 여부를 결정하는데 사용
		- 깊이 테스트는 사용자가 정의한 깊이 함수를 사용하여 렌더링된 픽셀 깊이 버퍼의 값을 비교
		- 성공하면 렌더링, 실패하면 걸러짐

	Stencil
		- 깊이 버퍼와 함께 사용되는 2D 이미지 버퍼
		- 각 픽셀에 대해 스텐실 값을 저장하며, 이 값은 렌더링 중에 테스트 및 업데이트
		- 다양한 렌더링 기술에서 사용 ex) 그림자 볼륨, 클리핑 평면 등등

	Stencil Test
		- 렌더링된 픽셀의 스텐실 값을 검사하여 렌더링 여부를 결정하는데 사용
		- 사용자가 정의한 스텐실 함수를 사용하여 렌더링된 픽셀의 스텐실 값과 스텐실 버퍼의 값을 비교
		- 스텐실 테스트에 성공하면 픽셀이 렌더링, 실패하면 걸러짐

	Blending
		- 렌더링된 픽셀의 색상을 결정하는 방법 중 하나
		- 렌더링된 픽셀의 색상과 렌더 타겟의 현재 색상을 결합하는 과정

	Alpha To Coverage
		- 멀티샘플링인 안티 엘리어싱(MSAA)을 사용할때 알파값을 커버리지 마스크로 변환하여 투명도를 구현하는 기술
		- 투명한 객체의 가장자리를 더 부드럽게 처리할 수 있음
*/