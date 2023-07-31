#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	vertices.assign(4, VertexColor());

	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
	vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);

	for (auto v : vertices)
		v.color = color;

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices = { 0,1,2,0,3,1 };
	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");

	il = new InputLayout();
	il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

	ps = new PixelShader();
	ps->Create(ShaderPath + L"VertexCoor.hlsl", "PS");

	wb = new WorldBuffer();
}
// homework : DX 용어 정리

Rect::~Rect()
{
}

void Rect::Update()
{
}

void Rect::Render()
{
}
