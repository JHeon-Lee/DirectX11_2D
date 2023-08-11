#include "stdafx.h"
#include "03_ShadedDemo.h"

#include "Geometries/ShadedTexture.h"
#include "Geometries/BlurTexture.h"

void ShadedDemo::Init()
{
	Vector3 pos = { WinMaxWidth / 2, WinMaxHeight / 2, 0 };
	Vector3 size = { 300,300,0 };
	// st = new ShadedTexture(pos, size, 0.0f, TexturePath + L"image.PNG");
	bt = new BlurTexture(pos, size, 0.0f, TexturePath + L"image.PNG");
}

void ShadedDemo::Destroy()
{
	// SAFE_DELETE(st);
	SAFE_DELETE(bt);
}

void ShadedDemo::Update()
{
	// st->Update();
	bt->Update();

}

void ShadedDemo::Render()
{
	// st->Render();
	bt->Render();
}

void ShadedDemo::PostRender()
{
}

void ShadedDemo::GUI()
{
	// st->GUI();
	bt->GUI();
}
