struct VertexInput // vertex�� �Է¹��� ����ü(vertextype���� vertexcolor �Ѱ��� �� position, color �ΰ� �Ѱ��ִ���)
{
	float4 position : POSITION0; // ���� ��ġ
	float4 color : COLOR0; // ���� ����
};

struct PixelInput // pixel�� ���� �Է¹޴� ����ü
{
	float4 position : SV_POSITION0; // ���� position�� �ٸ����� ���� world��ǥ������, ���� pixel ��ǥ�� �����
	float4 color : COLOR0;
};

cbuffer WorldBuffer : register(b0) // c : ���, b0 : ���� ���� ����
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

	// WVP ��ȯ ����
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
		- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����
		- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�

	���� : 16byte ������ ����Ե�
	���� : ������ 16byte�� ä��� ���� ������ �κ��� ä��� �뵵

	HLSL : high level shader language --> GPU�� ���� ���
		: DirectX ���� GPU����Ǵ� ���̴��� �ۼ��ϴµ� ����ϴ� ���
*/