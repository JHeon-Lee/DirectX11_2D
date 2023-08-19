#pragma once

class JGChar
{
public:
	JGChar(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot = CENTER);
	~JGChar();

	void Update();
	void Render();

	void Move();
	void CollisionMove();
	void TCollisionMove(); // ȭ�� top �� �ε����� ���
	void BCollisionMove(); // ȭ�� bottom �� �ε����� ���
	void LCollisionMove(); // ȭ�� left �� �ε����� ���
	void RCollisionMove(); // ȭ�� right �� �ε����� ���

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