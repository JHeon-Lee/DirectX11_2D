#include "Framework.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	: TextureRect(position, size, 0.0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");

	animator = new Animator;
	
	// Animation 추가 방법
	Texture2D* srcTex = new Texture2D(TexturePath + L"player.png");
	AnimationClip* Run_R = new AnimationClip
	(
		L"Run_R", srcTex, 10,
		Values::ZeroVec2, Vector2(srcTex->GetWidth(), srcTex->GetHeight() * 0.5f),
		1.0f / 15.0f
	);
	AnimationClip* Run_L = new AnimationClip
	(
		L"Run_L", srcTex, 10,
		Vector2(0.0f, srcTex->GetHeight() * 0.5f), Vector2(srcTex->GetWidth(), srcTex->GetHeight()),
		1.0f / 15.0f, true
	); // 역재생이라 마지막에 true

	animator->AddAnimClip(Run_R);
	animator->AddAnimClip(Run_L);
	animator->SetCurrentAnimClip(L"Run_R");

	SAFE_DELETE(srcTex);
}

AnimationRect::~AnimationRect()
{
}

void AnimationRect::Update()
{
}

void AnimationRect::Render()
{
}
