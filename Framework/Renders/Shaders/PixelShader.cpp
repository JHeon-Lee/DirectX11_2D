#include "Framework.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
	Clear();
}

void PixelShader::Create(const wstring path, const string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "ps_5_0", &blob); // PS 5.0 버전 사용
	// 여기서 blob : nullptr이라면서 터지는 경우 : Rect.cpp 에서 오타났을 가능성 높음

	HRESULT hr = DEVICE->CreatePixelShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	CHECK(hr);
}

void PixelShader::Clear()
{
	SAFE_RELEASE(blob);
	SAFE_RELEASE(shader);
}

void PixelShader::SetShader()
{
	DC->PSSetShader(shader, nullptr, 0);
}
