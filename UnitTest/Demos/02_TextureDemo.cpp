#include "stdafx.h"
#include "02_TextureDemo.h"

#include "Geometries/TextureRect.h"

void TextureDemo::Init()
{
	tr = new TextureRect(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(200, 200, 0), 0, TexturePath + L"image.PNG");
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(tr);
}

void TextureDemo::Update()
{
	tr->Update();
}

void TextureDemo::Render()
{
	tr->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
