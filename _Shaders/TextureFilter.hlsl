struct VertexInput // vertex가 입력받을 구조체
{
	float4 position : POSITION0; // 정점 위치
	float2 uv : TEXCOORD0; // 정점 색상
};

struct PixelInput // pixel에 대해 입력받는 구조체
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
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

cbuffer ShadedBuffer : register(b0)
{
	int _selection;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;

	// WVP 변환 과정
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _projection);

	output.uv = input.uv;

	return output;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	float4 resultColor = 0;

	if (_selection == 1)
	{
		return color;
	}
	else if (_selection == 2)
	{
		// AM
		float3 temp = dot(color.rgb, float3(0.299f, 0.587f, 0.114f)); // dot : 내적
		resultColor = float4(temp, color.a);
	}
	else if (_selection == 3)
	{
		// Sepia
		float3 sepia = float3(0.393f, 0.769f, 0.189f);
		float3 temp = dot(color.rgb, sepia);
		temp.r += 0.2;
		temp.g += 0.1;
		resultColor = float4(temp, color.a);
	}
	else if (_selection == 4)
	{
		// Negative
		float3 negative = 1 - abs(color.rgb);
		resultColor = float4(negative, color.a);
	}
	else if (_selection == 5)
	{
		// Posterize
		float3 value = float3(4.0f, 4.0f, 4.0f);
		float3 posterize = round(color.rgb * value) / value;
		resultColor = float4(posterize, color.a);
	}
	else
		resultColor = color;

	return resultColor;
}