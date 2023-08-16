#include "stdafx.h"
#include "04_RTVDemo.h"

#include "Geometries/Rect.h"
#include "Geometries/TextureRect.h"
#include "Utilities/RenderTexture.h"

void RTVDemo::Init()
{
	rt = new RenderTexture;

	Vector3 pos = { WinMaxWidth - (WinMaxWidth / 4), WinMaxHeight - (WinMaxHeight / 4), 0 };
	Vector3 size = { WinMaxWidth / 2, WinMaxHeight / 2, 0 };
	
	Vector3 rsize = { 100,100,0 };

	r1 = new Rect({ 200,200,0 }, rsize, 0);
	r2 = new Rect({ 500,400,0 }, rsize, 0);
	r3 = new Rect({ 700,100,0 }, rsize, 0);

	tr1 = new TextureRect({ 100,100,0 }, { 500,500,0 }, 0, TexturePath + L"image.PNG");
	tr2 = new TextureRect(pos, size, 0);

	tr2->SetShader(ShaderPath + L"TextureFilter_Task.hlsl");
}

void RTVDemo::Destroy()
{
	SAFE_DELETE(tr2);
	SAFE_DELETE(tr1);
	SAFE_DELETE(r3);
	SAFE_DELETE(r2);
	SAFE_DELETE(r1);
	SAFE_DELETE(rt);
}

void RTVDemo::Update()
{
	r1->Update();
	r2->Update();
	r3->Update();
	tr1->Update();
	tr2->Update();
}

void RTVDemo::Render()
{
	r1->Render();
	r2->Render();
	r3->Render();

	tr1->Render();

	tr2->SetSRV(rt->GetSRV());
	tr2->Render();
}

void RTVDemo::PostRender()
{
	Graphics::Get()->InitViewport();

	rt->RenderToTexture();
	{
		r1->Render();
		r2->Render();

		tr1->Render();
	}
}

void RTVDemo::GUI()
{
}
