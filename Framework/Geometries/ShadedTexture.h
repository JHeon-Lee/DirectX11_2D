#pragma once

#include "TextureRect.h"

// GPU, CPU
// hlsl, cpp

class ShadedBuffer : public ShaderBuffer
{
public:
	ShadedBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.Selection = 1;
	}

	int* GetSelectionPtr() { return &data.Selection; }

	// *padding
	// 16byte로 자르는 이유 : 제일 빠름
	struct Data
	{
		int Selection; // 4byte
		Vector3 dummy; // 12byte(float 3개)
	};

private:
	Data data;
};

class ShadedTexture : public TextureRect
{
public:
	ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~ShadedTexture();

	void Render();
	void GUI();

private:
	ShadedBuffer* sb = nullptr;
};