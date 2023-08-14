#include "Framework.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture()
{
    // Texture2D
    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
    
    textureDesc.Width = WinMaxWidth;
    textureDesc.Height = WinMaxHeight;
    
    textureDesc.MipLevels = 1; // 3D에서 거리에 따라 보이는 텍스처들을 몇단계로 나눌지 정함
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.MiscFlags = 0;
    
    HRESULT hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &texture);
    CHECK(hr);

    // RTV
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
    ZeroMemory(&rtvDesc, sizeof(rtvDesc));
    
    rtvDesc.Format = textureDesc.Format;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtvDesc.Texture2D.MipSlice = 0;

    hr = DEVICE->CreateRenderTargetView(texture, &rtvDesc, &rtv);

    // SRV
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));

    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    hr = DEVICE->CreateShaderResourceView(texture, &srvDesc, &srv);
    CHECK(hr);
}

RenderTexture::~RenderTexture()
{
    SAFE_RELEASE(rtv);
    SAFE_RELEASE(texture);
}

void RenderTexture::RenderToTexture()
{
    DC->OMSetRenderTargets(1, &rtv, nullptr);
    DC->ClearRenderTargetView(rtv, Values::ClearColor);
}

/*
    Texture2D
        - 그래픽카드에서 사용하는 텍스처 데이터를 저장하는 객체
        - 주로 이미지, 비디오, 노이즈, 라이트맵 등을 저장
        - 크기, 포맷, 밉맵, 멀티 샘플링 등 다양한 속성을 가질 수 있다

    Shader Resource View
        - 텍스처를 셰이더에서 읽기 위한 뷰
        - 셰이더는 텍스처를 읽어서 픽셀값 등을 계산
        - SRV를 사용하여 셰이더가 텍스처 데이터에 엑세스 할 수 있다

    Render Target View
        - 렌더 타겟에 대한 뷰
        - 셰이더 결과를 저장하는 버퍼
        - 해당 버퍼에 대한 읽기/쓰기 엑세스를 제공
        - 셰이더 결과를 렌더 타겟에 저장할 수 있다

    View
        - 리소스의 특정 부분이나 특정 방식으로 해석된 데이터를 참조하는 객체

    Mipmap
        - DirectX에서 아래의 목적을 위해서 텍스처의 여러 해상도 버전을 포함하는 이미지 컬렉션으로,
          각각의 해상도 버전은 배열로 저장
        - 텍스처 매핑이 더욱 효율적으로 이루어짐
            - 3D 공간에서 객체가 화면에 가까울수록 크게 보이고, 멀리 있을수록 작게 보인다
            - 가까운 객체에는 높은 해상도의 텍스처를 매핑하고, 멀리 있는 객체에는 낮은 해상도의 텍스처를 매핑한다.
                --> 자원 사용량이 줄어들고 렌더링 속도가 빨라짐
*/