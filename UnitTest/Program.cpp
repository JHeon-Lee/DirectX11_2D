#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/01_RectDemo.h"
#include "Demos/02_TextureDemo.h"
#include "Demos/03_ShadedDemo.h"
#include "Demos/QuarteredDemo.h"
#include "Demos/04_RTVDemo.h"
#include "Demos/05_CollisionDemo.h"

void Program::Init()
{
	{
		vpb = new VPBuffer();

		D3DXMatrixLookAtLH // LH : ¿Þ¼Õ ÁÂÇ¥°è
		(
			&view,
			&Vector3(0, 0, 0),
			&Vector3(0, 0, 1),
			&Vector3(0, 1, 0)
		);

		D3DXMatrixOrthoOffCenterLH // Á÷±³ Åõ¿µ
		(
			&proj,
			0.0f,
			(float)WinMaxWidth,
			0.0f,
			(float)WinMaxHeight,
			0,
			1
		);

		vpb->SetView(view);
		vpb->SetProjection(proj);
	}

	//Push(new RectDemo);
	//Push(new TextureDemo);
	//Push(new ShadedDemo);
	//Push(new QuarteredDemo);
	//Push(new RTVDemo);
	Push(new CollisionDemo);
}

void Program::Destroy()
{
	SAFE_DELETE(vpb);

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
