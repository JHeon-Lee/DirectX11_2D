#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox(Vector3 position, Vector3 size, float rotation, Color color, Pivot pivot)
{
	edge = new RectEdge;

	SetVertices();

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	ib = new IndexBuffer();
	indices = { 0,1,2,0,3,1 };
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"CollisionShader.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"CollisionShader.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

	wb = new WorldBuffer();
}

BoundingBox::~BoundingBox()
{
	SAFE_DELETE(wb);
	SAFE_DELETE(il);
	SAFE_DELETE(ps);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
	SAFE_DELETE(edge);
}

void BoundingBox::Update(Vector3 position, Vector3 size, float rotation)
{
	this->position = position;
	this->size = size;
	this->rotation = rotation;

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	wb->SetWorld(world);

	UpdateCollisionData();
}

void BoundingBox::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();

	wb->SetVSBuffer(0);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	return false;
}

void BoundingBox::SetVertices()
{
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
		// 기본 사각형
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
		vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
	}

	for (auto& v : vertices)
		v.color = color;
}

void BoundingBox::UpdateCollisionData()
{
	D3DXVec3TransformCoord(&edge->LT, &vertices[3].position, &world);
	D3DXVec3TransformCoord(&edge->LB, &vertices[0].position, &world);
	D3DXVec3TransformCoord(&edge->RT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&edge->RB, &vertices[2].position, &world);
}
