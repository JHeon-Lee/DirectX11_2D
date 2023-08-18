#include "stdafx.h"
#include "05_CollisionDemo.h"

#include "Geometries/Rect.h"

void CollisionDemo::Init()
{
	r1 = new Rect(Vector3(100, 100, 0), Vector3(100, 100, 0), 0.0f);
	r2 = new Rect(Vector3(200, 200, 0), Vector3(100, 100, 0), 0.0f);
}

void CollisionDemo::Destroy()
{
	SAFE_DELETE(r1);
	SAFE_DELETE(r2);
}

void CollisionDemo::Update()
{
	r1->Move();

	r1->Update();
	r2->Update();

	//if (BoundingBox::AABB(r1->GetBox(), r2->GetBox()))
	if (BoundingBox::OBB(r1->GetBox(), r2->GetBox()))
	{
		r1->SetColor(Values::Green);
		r2->SetColor(Values::Green);
	}
	else
	{
		r1->SetColor(Values::Red);
		r2->SetColor(Values::Red);
	}
}

void CollisionDemo::Render()
{
	r1->Render();
	r2->Render();
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI()
{
	r1->GUI();
}
