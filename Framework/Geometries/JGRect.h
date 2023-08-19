#pragma once

class JGRect
{
public:
	JGRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot = CENTER);
	~JGRect();

	void Update();
	void Render();

	void Move();

	void SetShader(wstring shaderPath);
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

	BoundingBox* GetBox() { return box; }

private:
	void SetVertices();
	void UpdateWorld();

private:
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world, S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation = 0.0f;

	Pivot pivot = CENTER;

	ID3D11ShaderResourceView* srv = nullptr;

	BoundingBox* box = nullptr;
};