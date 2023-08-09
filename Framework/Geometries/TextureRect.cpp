#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot)
	: position(position), size(size), rotation(rotation), pivot(pivot)
{
	SetVertices();

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices = { 0,1,2,0,3,1 };
	ib = new IndexBuffer;
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader;
	vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

	ps = new PixelShader;
	ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

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
}

TextureRect::~TextureRect()
{
	SAFE_DELETE(srv);
	SAFE_DELETE(wb);
	SAFE_DELETE(il);
	SAFE_DELETE(ps);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void TextureRect::Update()
{
	UpdateWorld();
}

void TextureRect::UpdateWorld()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);
}

void TextureRect::Render()
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

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
}

void TextureRect::SetVertices()
{
	vertices.assign(4, VertexTexture());

	switch (pivot)
	{
	case left:
		vertices[0].position = Vector3(0.0f, -0.5f, 0.0f);
		vertices[1].position = Vector3(+1.0f, +0.5f, 0.0f);
		vertices[2].position = Vector3(+1.0f, -0.5f, 0.0f);
		vertices[3].position = Vector3(0.0f, +0.5f, 0.0f);
		break;
	case right:
		vertices[0].position = Vector3(-1.0f, -0.5f, 0.0f);
		vertices[1].position = Vector3(0.0f, +0.5f, 0.0f);
		vertices[2].position = Vector3(0.0f, -0.5f, 0.0f);
		vertices[3].position = Vector3(-1.0f, +0.5f, 0.0f);
		break;
	case upper:
		vertices[0].position = Vector3(-0.5f, -1.0f, 0.0f);
		vertices[1].position = Vector3(+0.5f, 0.0f, 0.0f);
		vertices[2].position = Vector3(+0.5f, -1.0f, 0.0f);
		vertices[3].position = Vector3(-0.5f, 0.0f, 0.0f);
		break;
	case lower:
		vertices[0].position = Vector3(-0.5f, 0.0f, 0.0f);
		vertices[1].position = Vector3(+0.5f, +1.0f, 0.0f);
		vertices[2].position = Vector3(+0.5f, 0.0f, 0.0f);
		vertices[3].position = Vector3(-0.5f, +1.0f, 0.0f);
		break;
	case center:
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
		vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
		break;
	}

	vertices[0].uv = Vector2(0.0f, +1.0f);
	vertices[1].uv = Vector2(+1.0f, 0.0f);
	vertices[2].uv = Vector2(+1.0f, +1.0f);
	vertices[3].uv = Vector2(0.0f, 0.0f);
}
