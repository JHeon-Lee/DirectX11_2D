#include "stdafx.h"
#include "01_RectDemo.h"

#include "Geometries/Rect.h"

void RectDemo::Init() // »ý¼ºÀÚ¸¦ ´ë½ÅÇØÁÜ
{
	rect = new Rect(Vector3(500, 200, 0), Vector3(100, 100, 0), 0.0f);
}

void RectDemo::Destroy() // ¼Ò¸êÀÚ¸¦ ´ë½ÅÇØÁÜ
{
	SAFE_DELETE(rect);
}

void RectDemo::Update()
{
	rect->Update();
}

void RectDemo::Render()
{
	rect->Render();
}

void RectDemo::PostRender()
{
}

void RectDemo::GUI()
{
	rect->GUI();
}
