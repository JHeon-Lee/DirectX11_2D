#include "Framework.h"
#include "States.h"

// static �������� ������ ���� Ȯ���ص־���
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
	rsDesc.FillMode = D3D11_FILL_SOLID; // �ٰ����� ä��� ���
	rsDesc.CullMode = D3D11_CULL_BACK; // �ĸ� �ø� ��� ����
	rsDesc.FrontCounterClockwise = false; // ���� ���� ������ �ð�������� ����
	rsDesc.DepthBias = 0; // ���� ���̾ ��
	rsDesc.DepthBiasClamp = 0.0f; // ���� ���̾ Ŭ���� ��
	rsDesc.SlopeScaledDepthBias = 0.0f; // ��絵�� ���� ���� ���̾ ��
	rsDesc.ScissorEnable = false; // ���� �׽�Ʈ ��� ����(������ ����� Ư�� ������ ������ �ϴµ� ���)
	rsDesc.MultisampleEnable = false; // ��Ƽ ���ø� ��� ����
	rsDesc.AntialiasedLineEnable = false; // �� ��Ƽ�ٸ���� ��� ����
}

void States::CreateDepthStencilDesc()
{
	ZERO(dsDesc);

	dsDesc.DepthEnable = true; // ���� �׽�Ʈ ��� ����
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ���� ������ ��� ��Ʈ�� ���� ���� �۾� ���
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS; // ���� �׽�Ʈ �Լ� LESS�� ����
	dsDesc.StencilEnable = true; // ���ٽ� �׽�Ʈ ��� ����
	dsDesc.StencilReadMask = 0xFF; // ���ٽ� ���ۿ��� ���� �� �̾� ��Ʈ ����ũ ����
	dsDesc.StencilWriteMask = 0xFF; // ���ٽ� �׽�Ʈ ��� ����

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; // ���� ���� ���ٽ� ���� �۾� ����
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR; // ���� ���� ���ٽ� ���� ���� �۾� ����
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; // ���� ���� ���ٽ� �н� �۾� ����
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // ���� ���� ���ٽ� �Լ� ����

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
}

void States::CreateSamplerDesc()
{
	ZERO(spDesc);

	spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // ���� ���͸��� ����Ͽ� �ؽ�ó�� ���ø�
	spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // u ��ǥ�� ���� �ؽ�ó ��ǥ�� ����
	spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; // v ��ǥ�� ���� �ؽ�ó ��ǥ�� ����
	spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; // w ��ǥ�� ���� �ؽ�ó ��ǥ�� ����
	spDesc.MaxAnisotropy = 1; // �ƴϼ�Ʈ���� ���͸��� ��� (���⼭�� ��� ����)
	spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS; // �� ���ø��� ��� (���⼭�� ��� ����)
	spDesc.MinLOD = FLT_MIN; // �ؽ�ó�� �ּ� LOD ���� ���� (LOD : level of detail -> �Ÿ��� ���� ���е�)
	spDesc.MaxLOD = FLT_MAX; // �ؽ�ó�� �ִ� LOD ���� ����
}

void States::CreateBlendDesc()
{
	ZERO(blDesc);
	
	blDesc.AlphaToCoverageEnable = false; // alpha to coverage ��� ����
	blDesc.IndependentBlendEnable = false; // �������� ���� ��� ����

	blDesc.RenderTarget[0].BlendEnable = false; // ���� Ÿ�ٿ� ���� ���� ��� ����
	blDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // �ҽ� ���� ���� ���� �μ��� ����
	blDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // ������ ���� ���� ���� �μ��� ����
	blDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // ���� ���� ���� ������ ����

	blDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO; // ������ ���Ŀ� ���� ���� �μ��� ����
	blDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE; // �ҽ� ���Ŀ� ���� ���� �μ��� ����
	blDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // ���Ŀ� ���� ���� ������ ����

	blDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // ��� ���� ä���� ���� Ÿ�ٿ� ���
}

/*
	Depth : 3D �׷��ȿ��� �ȼ��� ���̸� ��Ÿ���� ��
		- ���� ���� ���۶�� 2D �̹��� ���ۿ� ����
		- ���� ���۴� �� �ȼ��� ���� ���� ���� ����, �� ���� ������ �߿� �׽�Ʈ �� ������Ʈ
		- ���� ���۸� ����ϸ� 3D ��鿡�� ��ü���� �ùٸ� ������ ���������� �� �� ����

	Depth Test
		- �������� �ȼ��� ���� ���� �˻��Ͽ� ������ ���θ� �����ϴµ� ���
		- ���� �׽�Ʈ�� ����ڰ� ������ ���� �Լ��� ����Ͽ� �������� �ȼ� ���� ������ ���� ��
		- �����ϸ� ������, �����ϸ� �ɷ���

	Stencil
		- ���� ���ۿ� �Բ� ���Ǵ� 2D �̹��� ����
		- �� �ȼ��� ���� ���ٽ� ���� �����ϸ�, �� ���� ������ �߿� �׽�Ʈ �� ������Ʈ
		- �پ��� ������ ������� ��� ex) �׸��� ����, Ŭ���� ��� ���

	Stencil Test
		- �������� �ȼ��� ���ٽ� ���� �˻��Ͽ� ������ ���θ� �����ϴµ� ���
		- ����ڰ� ������ ���ٽ� �Լ��� ����Ͽ� �������� �ȼ��� ���ٽ� ���� ���ٽ� ������ ���� ��
		- ���ٽ� �׽�Ʈ�� �����ϸ� �ȼ��� ������, �����ϸ� �ɷ���

	Blending
		- �������� �ȼ��� ������ �����ϴ� ��� �� �ϳ�
		- �������� �ȼ��� ����� ���� Ÿ���� ���� ������ �����ϴ� ����

	Alpha To Coverage
		- ��Ƽ���ø��� ��Ƽ �������(MSAA)�� ����Ҷ� ���İ��� Ŀ������ ����ũ�� ��ȯ�Ͽ� ������ �����ϴ� ���
		- ������ ��ü�� �����ڸ��� �� �ε巴�� ó���� �� ����
*/