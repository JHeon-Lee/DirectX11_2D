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

// �̹��� ���Ϸκ��� �ؽ�ó �����Ϳ� ���̴� ���ҽ� �並 ������ ��
ID3D11ShaderResourceView* Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// Path cpp ���� ������ �ٽ� �ۼ�

	return nullptr;
}
