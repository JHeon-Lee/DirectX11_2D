#include "Framework.h"
#include "JGRect.h"

JGRect::JGRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot)
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

	box = new BoundingBox(position, size, rotation, Color(1, 0, 0, 1), CENTER);

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	CHECK(hr);
}

JGRect::~JGRect()
{
	SAFE_DELETE(wb);
	SAFE_DELETE(il);
	SAFE_DELETE(ps);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void JGRect::Update()
{
	UpdateWorld();
}

void JGRect::Render()
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

void JGRect::SetVertices()
{
	vertices.assign(4, VertexTexture());

	switch (pivot)
	{
	case LEFT:
		vertices[0].position = Vector3(0.0f, -0.5f, 0.0f);
		vertices[1].position = Vector3(+1.0f, +0.5f, 0.0f);
		vertices[2].position = Vector3(+1.0f, -0.5f, 0.0f);
		vertices[3].position = Vector3(0.0f, +0.5f, 0.0f);
		break;
	case RIGHT:
		vertices[0].position = Vector3(-1.0f, -0.5f, 0.0f);
		vertices[1].position = Vector3(0.0f, +0.5f, 0.0f);
		vertices[2].position = Vector3(0.0f, -0.5f, 0.0f);
		vertices[3].position = Vector3(-1.0f, +0.5f, 0.0f);
		break;
	case UPPER:
		vertices[0].position = Vector3(-0.5f, -1.0f, 0.0f);
		vertices[1].position = Vector3(+0.5f, 0.0f, 0.0f);
		vertices[2].position = Vector3(+0.5f, -1.0f, 0.0f);
		vertices[3].position = Vector3(-0.5f, 0.0f, 0.0f);
		break;
	case LOWER:
		vertices[0].position = Vector3(-0.5f, 0.0f, 0.0f);
		vertices[1].position = Vector3(+0.5f, +1.0f, 0.0f);
		vertices[2].position = Vector3(+0.5f, 0.0f, 0.0f);
		vertices[3].position = Vector3(-0.5f, +1.0f, 0.0f);
		break;
	case CENTER:
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

void JGRect::UpdateWorld()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);

	box->Update(position, size, rotation);
}

void JGRect::Move()
{
	auto key = Keyboard::Get();
	float delta = Time::Delta();

	position.y -= 150 * delta;
}

void JGRect::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();
	vs->Create(ShaderPath + shaderPath, "VS");
	ps->Create(ShaderPath + shaderPath, "PS");
}
