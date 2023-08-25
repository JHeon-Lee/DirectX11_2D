#pragma once

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot = CENTER);
	TextureRect(Vector3 position, Vector3 size, float rotation);
	virtual ~TextureRect();

	void Update();

	void Render();
	void GUI();

	void SetShader(wstring shaderPath);
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	virtual void Move();

private:
	void SetVertices();
	void UpdateWorld();

protected: // 나중에 animationrect 만들때 상속시키기 위해 protected를 사용
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
	float rotation;

	Pivot pivot = CENTER;

	ID3D11ShaderResourceView* srv = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;
};