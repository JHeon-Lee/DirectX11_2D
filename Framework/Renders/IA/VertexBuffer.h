#pragma once

class VertexBuffer
{
public:
	~VertexBuffer();

	template<typename T> // ���� ������ VertexType�� ��� ó���� �� �ְ� ���ø� ���
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride = 0;
	uint offset = 0;
	uint count = 0; // vertex�� ����
};

// VertexType�� ���� ó���ϱ����� ���ø����� ����
template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);
	count = vertices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = stride * count;

	switch (usage)
	{
		// homework : USAGE_ �� �ǹ� ����
	case D3D11_USAGE_DEFAULT:
	case D3D11_USAGE_IMMUTABLE:
		break;

	case D3D11_USAGE_DYNAMIC:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;

	case D3D11_USAGE_STAGING:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		break;
	}

	// 7/31

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

	subData.pSysMem = vertices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
	CHECK(hr);
}
