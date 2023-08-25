#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bReversed)
	:clipname(clipName), frameCount(frameCount), playRate(playRate), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	Vector2 clipSize = endPos - startPos;

	Vector2 frameSize; // 그림 하나의 사이즈 --> 이렇게 설정하면 축을 잘 맞춰줘야함
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y / frameCount;

	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageWidth;

	Vector2 texelStartPos; // texel : 텍스처 안의 픽셀
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageWidth;

	Vector2 keyframe;

	for (uint i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i); // 가로로 움직임 -> texelFrameSize.x 하나씩 증가
		keyframe.y = texelStartPos.y; // 한줄짜리로 만들거라 그대로 뒀음 - 가로로 움직임 생성할거라

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
	if (deltaTime > currentClip->playRate) // deltaTime : 누적시간
	{
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++;

			if (currentFrameIndex == currentClip->frameCount) // 끝까지 도달했을 경우
				currentFrameIndex = 0; // 한번만 출력하려면 bool형 에 and연산 엮어서 0으로 안가게 만들면 됨

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
	if (currentClip == nullptr && CheckExist(clipName) == true) // 클립은 없고 애니메이션만 있음
		currentClip = animClips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipname == clipName) // 클립이 있고, 업데이트된 clipname이 같다면
		return; // 이 구문 없으면 첫 프레임에서 안움직임

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		deltaTime = 0.0f; // 다음 프레임으로 넘어갔을때 초기화시켜야함

		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
