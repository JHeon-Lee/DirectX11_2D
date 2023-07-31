#pragma once

#include "IShader.h"

class PixelShader : public IShader
{
public:
	~PixelShader();

	virtual void Create(const wstring path, const string entryName) override;
	virtual void Clear() override;
	virtual void SetShader() override;

	ID3DBlob* GetBlob() { return blob; }
	ID3D11PixelShader* GetShader() { return shader; }

private:
	ID3D11PixelShader* shader = nullptr;
	ID3DBlob* blob = nullptr;
};