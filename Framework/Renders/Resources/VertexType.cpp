#include "Framework.h"
#include "VertexType.h"

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
    {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
    {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
};

/*
    Vertex : position, color, uv��ǥ ��� ���� ������ ���� �� �ִ�, �ð�������� �׷���

    D3D11_INPUT_ELEMENT_DESC ��� ����(Vertex ���)

    SemanticName            : ���� �������� �ǹ̸� ��Ÿ���� ����
    SemanticIndex           : �� �̸��� �ߺ��Ǵ� ��� �����ϱ� ���� �ε��� ��
    Format                  : �������� ����
    InputSlot               : �Է� ������ �ε���
    AlignedByteOffset       : ���� �������� ����Ʈ ���� ������
    InputSlotClass          : ���Ǵ� ������ ���� ����
    InstanceDataStepRate    : �ν��Ͻ����� �����͸� �о���̴µ� ����� ���� ����Ʈ ��

    D3D11_APPEND_ALIGNED_ELEMENT -> ������ �ڵ� ���
    R32G32B32_FLOAT -> 32����Ʈ, float ����
*/