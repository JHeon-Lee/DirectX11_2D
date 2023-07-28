#pragma once
#include "Framework.h"

class ShaderBuffer
{
public:
	void SetVSBuffer(uint slot)
	{
		MapData();
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(uint slot)
	{
		MapData();
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	ShaderBuffer(void* data, uint dataSize)
		: data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = dataSize;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // 정의에서 버퍼 종류 확인 가능
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	} // 버퍼의 사용 용도 기입

private:
	void MapData() // Map : 데이터에 접근하기위한 과정
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		HRESULT hr = DC->Map
		(
			buffer, // 무엇을 열람할거냐
			0, // 어디서부터
			D3D11_MAP_WRITE_DISCARD,
			0,
			&subResource // 어디에 복사할거냐
		);
		CHECK(hr);

		memcpy(subResource.pData, data, dataSize);
		DC->Unmap(buffer, 0);
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr;
	uint dataSize = 0;
};