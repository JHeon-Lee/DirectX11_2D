#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
// Blob : 메모리블롭
{
	if (!descs | !count | !blob)
		CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,
		count,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout);
}
