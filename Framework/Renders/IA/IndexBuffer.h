#pragma once
// IndexBuffer : vertex들 이어서 프리미티브를 만들때 정점에 주어지는 번호를 정렬해놓은것

class IndexBuffer
{
public:
	~IndexBuffer();

	void Create(const vector<uint>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride = 0;
	uint offset = 0;
	uint count = 0;
};