struct VertexInput
{
	float4 position : POSITION0;
	float2 uv		: TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv		: TEXCOORD0;
};

cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
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
	float4 color;
	float3 grayScale = 0;
	
	if (input.uv.x < 0.5f && input.uv.y < 0.5f)
	{
		color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.0, input.uv.y * 2.0f));
		grayScale = dot(color.rgb, float3(.299f, .587f, .114f));
		
		color = float4(grayScale, 1);
	}
	else if (input.uv.x >= 0.5 && input.uv.y < 0.5f)
	{
		color = _sourceTex.Sample(_samp, float2((input.uv.x - 0.5f) * 2.0f, input.uv.y * 2.0f));
		float r, g, b;
		r = dot(color.rgb, float3(.393f, .769f, .189f));
		g = dot(color.rgb, float3(.349f, .686f, .168f));
		b = dot(color.rgb, float3(.272f, .534f, .131f));

		grayScale = float3(r, g, b);
		color = float4(grayScale, 1);
	}
	else if (input.uv.x < 0.5f && input.uv.y >= 0.5f)
	{
		color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.0f, (input.uv.y - 0.5f) * 2.0f));
	}
	else if (input.uv.x >= 0.5f && input.uv.y >= 0.5f)
	{
		color = _sourceTex.Sample(_samp, float2((input.uv.x - 0.5f) * 2.0f, (input.uv.y - 0.5f) * 2.0f));
	}
	
	
		return color;
	}

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����
- �ֿ� ����
	1) ��� ���� ����
	- ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� ������ �� �ִ�
	- ��� ���� ������ register(b#)�� ����Ͽ� ����
	
	2) �ؽ�ó ����
	- �̹��� �����͸� �����ϴµ� ���
	- �ؽ�ó ���� ������ register(t#)�� ����Ͽ� ����

	3) ���÷� ����
	- �ؽ�ó�� ���ø� �ϴµ� ���
	- ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� �ִ�
- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�

Sampler : ���÷�
- �ؽ�ó���� �ȼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ�ó ���ø��� �ؽ�ó �̹����� ���� �ؼ� ���� ����ϴ� �۾�
  (�ؼ� = �ؽ�ó�� �ȼ� ��)
*/