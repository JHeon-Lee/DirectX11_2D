struct VertexInput
{
	float4 position : POSITION0; // 정점 위치
	float4 color : COLOR0; // 정점 색상
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

cbuffer WorldBuffer : register(b0) // c : 상수, b0 : 버퍼 슬롯 숫자
{
	matrix _world;
}

cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _projection);

	output.color = input.color;

	return output;
}

float4 PS(PixelInput input) : SV_Target
{
	return input.color;
}