#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	: filePath(filePath)
{
	Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	texture->GetDesc(&srcDesc);

	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(destDesc));

	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srcDesc.Format;
	destDesc.SampleDesc = srcDesc.SampleDesc;
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
	CHECK(hr);
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	uint* colors = new uint[destDesc.Width * destDesc.Height]; // 픽셀 컬러 계산

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
	{
		memcpy(colors, subResource.pData, sizeof(uint) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	int pixelNum = destDesc.Width * destDesc.Height;

	uint* alpha = new uint[pixelNum];
	uint* red = new uint[pixelNum];
	uint* green = new uint[pixelNum];
	uint* blue = new uint[pixelNum];

	for (int i = 0; i < pixelNum; i++)
	{
		alpha[i] = (colors[i] & 0xFF000000);
		red[i] = (colors[i] & 0x00FF0000);
		green[i] = (colors[i] & 0x0000FF00);
		blue[i] = (colors[i] & 0x000000FF);

		red[i] = colors[i] >> 16;
		blue[i] = colors[i] << 16; // texture는 rgb순서가 반대로 저장되서 바꿔줌

		colors[i] = alpha[i] | red[i] | green[i] | blue[i];
	}

	pixels->assign(&colors[0], &colors[pixelNum - 1]);

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(destTex);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_DELETE(desc.srv);
}

// 이미지 파일로부터 텍스처 데이터와 셰이더 리소스 뷰를 가지게 됨
ID3D11ShaderResourceView* Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// Path cpp 파일 생성후 작성
	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	uint width = metaData.width;
	uint height = metaData.height;

	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	// 중복되는지 검사
	TextureDesc exist;
	bool bExist = false;
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	if (bExist == true)
	{
		texture->srv = exist.srv;
		texture->metaData = metaData;
	}
	else
	{
		ScratchImage image;
		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);

		return srv;
	}
}
