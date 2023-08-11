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

	for (auto& v : vertices)
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
	ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");

	wb = new WorldBuffer();
}
// homework : DX 용어 정리 ~ 7/31
//8/7 ~ 
Rect::~Rect()
{
	SAFE_DELETE(wb);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb); // 생성된 순서의 역순
}

void Rect::Update()
{
	// Size
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	// Rotation
	D3DXMatrixRotationZ(&R, rotation);
	// translation (position)
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	
	world = S * R * T;
	wb->SetWorld(world);
}

void Rect::Render()
{
	// IA
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 어떤 방식으로 프리미티브 만들지

	// VS
	vs->SetShader();
	wb->SetVSBuffer(0);

	// PS
	ps->SetShader();

	// OM
	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::GUI() // 포트폴리오 만들 때 실시간으로 값의 변경을 확인할 때에도 사용 가능
{
	using namespace ImGui;
	Begin("Rect"); // 회색 상자 구현
	{
		// 정의할 내용들
		InputFloat3("Pos", position, 2); // 정해줄 이름, 변경할 값, 나타낼 소수점 자릿수
		InputFloat3("Size", size, 2);
		SliderAngle("Rot", &rotation, 0, 360.0f); // 정해줄 이름, 변경할 값, 최소값, 최대값

		if (ColorPicker4("Color", color))
			UpdateColor();
	}
	End();
}

void Rect::UpdateColor()
{
	// vertex의 정보 변경해야함 --> 버퍼 안의 내용은 맘대로 수정이 안됨
	// --> Mapping이라는 작업을 수행해야함 --> subresource를 만들어줌 --> mapping --> unmapping
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (auto& v : vertices)
			v.color = color;

		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);
}
