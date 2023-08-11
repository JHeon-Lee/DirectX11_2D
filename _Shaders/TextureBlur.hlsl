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

cbuffer BlurBuffer : register(b1)
{
	float2 _imageSize;
	int _blurCount;
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
	float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
	
	// 주변 픽셀 불러오기
	float2 arr[8] =
	{
		float2(-1, +1), float2(+0, +1), float2(+1, +1),
		float2(-1, +0),					float2(+1, +0),
		float2(-1, -1), float2(+0, -1), float2(+1, -1),
	};

	// blurCount 받은만큼 평균값 계산
	for (int blur = 1; blur < _blurCount; blur++)
	{
		for (int i = 0; i < 8;i++)
		{
			// 주변 좌표 계산
			float x = arr[i].x * (float) blur / _imageSize.x;
			float y = arr[i].y * (float) blur / _imageSize.y;

			// 주변 uv 좌표 계산
			float2 uv = input.uv + float2(x, y);

			// 최종 연산
			color += _sourceTex.Sample(_samp, uv);
		}
	}

	int blurInterations = _blurCount - 1;
	int offsetCount = 8;
	int totalSamples = blurInterations * offsetCount + 1;
	
	return color /= totalSamples;
}