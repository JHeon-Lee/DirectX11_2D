#include "Framework.h"
#include "QuarteredTexture.h"

QuarteredTexture::QuarteredTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	: position(position), size(size), rotation(rotation)
{
	SetVertices();

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices = { 0,1,2,0,3,1 };
	ib = new IndexBuffer;
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader;
	vs->Create(ShaderPath + L"QuarteredFilter.hlsl", "VS");

	ps = new PixelShader;
	ps->Create(ShaderPath + L"QuarteredFilter.hlsl", "PS");

	il = new InputLayout;
	il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

	wb = new WorldBuffer;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	CHECK(hr); // 여기서 터지면 path 문제 --> 파일명 확인 등등
	
	D3D11_SAMPLER_DESC sDesc =
	{
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		1,
		1,
		D3D11_COMPARISON_NEVER,
		1,
		-3.402823466e+38F,
		+3.402823466e+38F
	};

	DEVICE->CreateSamplerState(&sDesc, &ss);
}

QuarteredTexture::~QuarteredTexture()
{
	SAFE_DELETE(wb);
	SAFE_DELETE(il);
	SAFE_DELETE(ps);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void QuarteredTexture::Update()
{
	UpdateWorld();
}

void QuarteredTexture::Render()
{
	// IA
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VS
	vs->SetShader();
	wb->SetVSBuffer(0);

	// PS
	ps->SetShader();

	// OM
	DC->PSSetShaderResources(0, 1, &srv);
	DC->PSSetSamplers(0, 1, &ss);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void QuarteredTexture::GUI()
{
}

void QuarteredTexture::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();
	vs->Create(ShaderPath + shaderPath, "VS");
	ps->Create(ShaderPath + shaderPath, "PS");
}

void QuarteredTexture::SetVertices()
{
	vertices.assign(4, VertexTexture());
	// 좌측 하단부터 시계방향으로 indicies 생성
	
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
	vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);

	vertices[0].uv = Vector2(0.0f, +2.0f);
	vertices[1].uv = Vector2(+2.0f, 0.0f);
	vertices[2].uv = Vector2(+2.0f, +2.0f);
	vertices[3].uv = Vector2(0.0f, 0.0f);
}

void QuarteredTexture::UpdateWorld()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);
}
