#include "Framework.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(const wstring path, const string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "vs_5_0", &blob); // VS 5.0 버전 사용

	HRESULT hr = DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	CHECK(hr);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(blob);
	SAFE_RELEASE(shader);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
