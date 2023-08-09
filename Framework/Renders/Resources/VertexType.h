#pragma once

struct VertexColor
{
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0){}

	VertexColor(Vector3 position, Color color)
		: position(position), color(color){}

	Vector3 position;
	Color color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2; // 위의 원소 개수
};

struct VertexTexture
{
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}

	Vector3 position;
	Vector2 uv;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2; // 위의 원소 개수
};