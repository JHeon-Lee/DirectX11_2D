#include "Framework.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	: TextureRect(position, size, 0.0f)
{
	//SetShader(ShaderPath + L"Animation.hlsl");

	animator = new Animator;
	
	// Animation 추가 방법 --> 포트폴리오 만들땐 Demo에서 만드는게 좋음
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

	// Sampler
	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}
}

AnimationRect::~AnimationRect()
{
}

void AnimationRect::Update()
{
	animator->Update();

	MapVertexBuffer();
	{
		Vector2 frame = animator->GetCurrentFrame();
		Vector2 texelSize = animator->GetTexelFrameSize();
		vertices[0].uv.x = frame.x;
		vertices[0].uv.y = frame.y + texelSize.y;

		vertices[1].uv.x = frame.x + texelSize.x;
		vertices[1].uv.y = frame.y;

		vertices[2].uv.x = frame.x + texelSize.x;
		vertices[2].uv.y = frame.y + texelSize.y;

		vertices[3].uv.x = frame.x;
		vertices[3].uv.y = frame.y;
	}
	UnmapVertexBuffer();

	__super::Update();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

void AnimationRect::Move()
{
	auto* keyboard = Keyboard::Get();
	float delta = Time::Delta();

	if (keyboard->Press('W'))
	{
		position.y += 100 * delta;
	}

	if (keyboard->Press('S'))
	{
		position.y -= 100 * delta;
	}
	if (keyboard->Press('A'))
	{
		position.x -= 100 * delta;
		animator->SetCurrentAnimClip(L"Run_L");
	}
	if (keyboard->Press('D'))
	{
		position.x += 100 * delta;
		animator->SetCurrentAnimClip(L"Run_R");
	}
}
