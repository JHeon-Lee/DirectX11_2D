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
	void TCollisionMove(); // È­¸é top ¿¡ ºÎµúÇûÀ» °æ¿ì
	void BCollisionMove(); // È­¸é bottom ¿¡ ºÎµúÇûÀ» °æ¿ì
	void LCollisionMove(); // È­¸é left ¿¡ ºÎµúÇûÀ» °æ¿ì
	void RCollisionMove(); // È­¸é right ¿¡ ºÎµúÇûÀ» °æ¿ì

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