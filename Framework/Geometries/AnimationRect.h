#pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

class AnimationRect : public TextureRect
{
public:
	AnimationRect(Vector3 position, Vector3 size);
	~AnimationRect();

	void Update();
	void Render();

	void SetAnimation(Animator* animator) { this->animator = animator; }

private:
	class Animator* animator = nullptr;

	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];
};