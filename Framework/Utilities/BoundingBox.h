#pragma once

struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};

class BoundingBox
{
public:
	BoundingBox(Vector3 position, Vector3 size, float rotation, Color color, Pivot pivot);
	~BoundingBox();
	
	void Update(Vector3 position = Vector3(0, 0, 0), Vector3 size = { 100,100,1 }, float rotation = 0);
	void Render();

	static bool AABB(BoundingBox* a, BoundingBox* b);

private:
	void SetVertices();
	void UpdateCollisionData();

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	WorldBuffer* wb = nullptr;
	Matrix world, S, R, T;

	Vector3 position;
	Vector3 size;
	float rotation;
	Color color;
	Pivot pivot = CENTER;

	RectEdge* edge = nullptr;
};