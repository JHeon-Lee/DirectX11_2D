#include "Framework.h"
#include "VertexType.h"

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
    {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
    {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
    {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
    {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
};

/*
    Vertex : position, color, uv좌표 등등 여러 정보를 담을 수 있다, 시계방향으로 그려짐

    D3D11_INPUT_ELEMENT_DESC 요소 설명(Vertex 요소)

    SemanticName            : 정점 데이터의 의미를 나타내는 문구
    SemanticIndex           : 위 이름이 중복되는 경우 구분하기 위한 인덱스 값
    Format                  : 데이터의 형식
    InputSlot               : 입력 슬롯의 인덱스
    AlignedByteOffset       : 정점 데이터의 바이트 단위 오프셋
    InputSlotClass          : 사용되는 데이터 형식 지정
    InstanceDataStepRate    : 인스턴스마다 데이터를 읽어들이는데 사용할 스텝 레이트 값

    D3D11_APPEND_ALIGNED_ELEMENT -> 오프셋 자동 계산
    R32G32B32_FLOAT -> 32바이트, float 형식

    출력 객체를 만드는 과정
    VertexType에 구조체 생성 -> Geometries에 cpp,h 파일 생성 후 작성 --> UnitTest의 데모 폴더에 데모 생성
*/