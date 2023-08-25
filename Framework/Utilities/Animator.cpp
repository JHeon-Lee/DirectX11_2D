#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bReversed)
	:clipname(clipName), frameCount(frameCount), playRate(playRate), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	Vector2 clipSize = endPos - startPos;

	Vector2 frameSize; // �׸� �ϳ��� ������ --> �̷��� �����ϸ� ���� �� ���������
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y / frameCount;

	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageWidth;

	Vector2 texelStartPos; // texel : �ؽ�ó ���� �ȼ�
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageWidth;

	Vector2 keyframe;

	for (uint i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i); // ���η� ������ -> texelFrameSize.x �ϳ��� ����
		keyframe.y = texelStartPos.y; // ����¥���� ����Ŷ� �״�� ���� - ���η� ������ �����ҰŶ�

		keyFrames.push_back(keyframe);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
		SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (deltaTime > currentClip->playRate) // deltaTime : �����ð�
	{
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++;

			if (currentFrameIndex == currentClip->frameCount) // ������ �������� ���
				currentFrameIndex = 0; // �ѹ��� ����Ϸ��� bool�� �� and���� ��� 0���� �Ȱ��� ����� ��

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else
		{
			currentFrameIndex--;

			if (currentFrameIndex == -1)
				currentFrameIndex = currentClip->frameCount - 1;
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}
	else
		deltaTime += Time::Delta();
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipname, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip == nullptr && CheckExist(clipName) == true) // Ŭ���� ���� �ִϸ��̼Ǹ� ����
		currentClip = animClips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipname == clipName) // Ŭ���� �ְ�, ������Ʈ�� clipname�� ���ٸ�
		return; // �� ���� ������ ù �����ӿ��� �ȿ�����

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		deltaTime = 0.0f; // ���� ���������� �Ѿ���� �ʱ�ȭ���Ѿ���

		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
