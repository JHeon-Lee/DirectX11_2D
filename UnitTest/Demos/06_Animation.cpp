#include "stdafx.h"
#include "06_Animation.h"

#include "Geometries/AnimationRect.h"

void AnimationDemo::Init()
{
	ar = new AnimationRect({ 720,360,0 }, { 200,200,0 });
}

void AnimationDemo::Destroy()
{
	SAFE_DELETE(ar);
}

void AnimationDemo::Update()
{
	ar->Update();
}

void AnimationDemo::Render()
{
	ar->Render();
}

void AnimationDemo::PostRender()
{
}

void AnimationDemo::GUI()
{
}
