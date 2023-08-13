#include "stdafx.h"
#include "QuarteredDemo.h"

#include "Geometries/QuarteredTexture.h"

void QuarteredDemo::Init()
{
	Vector3 pos = { WinMaxWidth / 2, WinMaxHeight / 2, 0 };
	Vector3 size = { 300,300,0 };
	qt = new QuarteredTexture(pos, size, 0.0f, TexturePath + L"image.PNG");
}

void QuarteredDemo::Destroy()
{
	SAFE_DELETE(qt);
}

void QuarteredDemo::Update()
{
	qt->Update();
}

void QuarteredDemo::Render()
{
	qt->Render();
}

void QuarteredDemo::PostRender()
{
}

void QuarteredDemo::GUI()
{
}
