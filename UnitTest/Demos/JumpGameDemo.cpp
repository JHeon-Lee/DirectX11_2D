#include "stdafx.h"
#include "JumpGameDemo.h"

#include "Geometries/Rect.h"
#include "Geometries/TextureRect.h"
#include "Geometries/JGChar.h"
#include "Geometries/JGRect.h"

void JumpGameDemo::Init()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(80, WinMaxWidth - 80);

	//g1 = new TextureRect(Vector3(WinMaxHeight / 2, WinMaxHeight / 2, 0),
	//	Vector3(852, 480, 0),
	//	0,
	//	TexturePath + L"gameover.jpeg");

	r1 = new Rect(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0),
		Vector3(WinMaxWidth, WinMaxHeight, 0),
		0.0f);

	f1 = new JGRect(Vector3(dis(gen), WinMaxHeight / 4, 0),
		Vector3(160, 18, 0),
		0.0f,
		TexturePath + L"floor.png");

	f2 = new JGRect(Vector3(dis(gen), WinMaxHeight / 2, 0),
		Vector3(160, 18, 0),
		0.0f,
		TexturePath + L"floor.png");

	f3 = new JGRect(Vector3(dis(gen), WinMaxHeight * 3 / 4, 0),
		Vector3(160, 18, 0),
		0.0f,
		TexturePath + L"floor.png");

	f4 = new JGRect(Vector3(dis(gen), WinMaxHeight, 0),
		Vector3(160, 18, 0),
		0.0f,
		TexturePath + L"floor.png");

	c1 = new JGChar(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0),
		Vector3(100, 100, 0),
		0.0f,
		TexturePath + L"character.png");
}

void JumpGameDemo::Destroy()
{
	SAFE_DELETE(c1);
	SAFE_DELETE(f4);
	SAFE_DELETE(f3);
	SAFE_DELETE(f2);
	SAFE_DELETE(f1);
	SAFE_DELETE(r1);
	//SAFE_DELETE(g1);
}

void JumpGameDemo::Update()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(80, WinMaxWidth - 80);

	if (BoundingBox::TBC(c1->GetBox(), r1->GetBox())) // 모서리에서 하나만 적용됨
		c1->TCollisionMove();
	else if (BoundingBox::BBC(c1->GetBox(), r1->GetBox()))
		c1->BCollisionMove();
	//{
	//
	//	SAFE_DELETE(c1);
	//	SAFE_DELETE(f4);
	//	SAFE_DELETE(f3);
	//	SAFE_DELETE(f2);
	//	SAFE_DELETE(f1);
	//	SAFE_DELETE(r1);
	//}
	else if (BoundingBox::LBC(c1->GetBox(), r1->GetBox()))
		c1->LCollisionMove();
	else if (BoundingBox::RBC(c1->GetBox(), r1->GetBox()))
		c1->RCollisionMove();
	else if (BoundingBox::AABB(c1->GetBox(), f1->GetBox()) ||
		BoundingBox::AABB(c1->GetBox(), f2->GetBox()) ||
		BoundingBox::AABB(c1->GetBox(), f3->GetBox()) ||
		BoundingBox::AABB(c1->GetBox(), f4->GetBox()))
		c1->CollisionMove();
	else
		c1->Move();
	
	f1->Move();
	f2->Move();
	f3->Move();
	f4->Move();

	c1->Update();
	f1->Update();
	f2->Update();
	f3->Update();
	f4->Update();
	r1->Update();
	//g1->Update();

	if (BoundingBox::BBC(f1->GetBox(), r1->GetBox()))
	{
		SAFE_DELETE(f1);
		f1 = new JGRect(Vector3(dis(gen), WinMaxHeight, 0),
			Vector3(160, 18, 0),
			0.0f,
			TexturePath + L"floor.png");
	}
	if (BoundingBox::BBC(f2->GetBox(), r1->GetBox()))
	{
		SAFE_DELETE(f2);
		f2 = new JGRect(Vector3(dis(gen), WinMaxHeight, 0),
			Vector3(160, 18, 0),
			0.0f,
			TexturePath + L"floor.png");
	}
	if (BoundingBox::BBC(f3->GetBox(), r1->GetBox()))
	{
		SAFE_DELETE(f3);
		f3 = new JGRect(Vector3(dis(gen), WinMaxHeight, 0),
			Vector3(160, 18, 0),
			0.0f,
			TexturePath + L"floor.png");
	}
	if (BoundingBox::BBC(f4->GetBox(), r1->GetBox()))
	{
		SAFE_DELETE(f4);
		f4 = new JGRect(Vector3(dis(gen), WinMaxHeight, 0),
			Vector3(160, 18, 0),
			0.0f,
			TexturePath + L"floor.png");
	}
}

void JumpGameDemo::Render()
{
	r1->Render();
	f1->Render();
	f2->Render();
	f3->Render();
	f4->Render();
	c1->Render();
	//g1->Render();
}

void JumpGameDemo::PostRender()
{
}

void JumpGameDemo::GUI()
{
}
