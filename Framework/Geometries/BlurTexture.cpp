#include "Framework.h"
#include "BlurTexture.h"

BlurTexture::BlurTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	: TextureRect(position, size, rotation, path)
{
	bb = new BlurBuffer();
	bb->SetTextureSize({ size.x, size.y });
	SetShader(L"TextureBlur.hlsl");
}

BlurTexture::~BlurTexture()
{
	SAFE_DELETE(bb);
}

void BlurTexture::Update()
{
	__super::Update(); // __super : 부모 클래스의 함수 호출
}

void BlurTexture::Render()
{
	bb->SetPSBuffer(1);
	__super::Render();
}

void BlurTexture::GUI()
{
	using namespace ImGui;
	Begin("Blur Counter");
	{
		SliderInt("BlurCounter", bb->GetBlurCountPtr(), 1, 50);
	}
	End();
}
