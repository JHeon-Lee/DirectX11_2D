#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
{
	Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
}

void Textures::Delete()
{
}

// 이미지 파일로부터 텍스처 데이터와 셰이더 리소스 뷰를 가지게 됨
ID3D11ShaderResourceView* Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// Path cpp 파일 생성후 다시 작성

	return nullptr;
}
