#pragma once
// renders -> resoures -> texture2d 파일부터 만들고 진행
// 그후 DirectXTEX 폴더 _Libraries에 추가

class AnimationClip // 클립 단위로 만듬
{
public:
	friend class Animator;
	AnimationClip(wstring clipName, Texture2D* srvTex, UINT frameCount,
		 		  Vector2 startPos, Vector2 endPos, float playRate,
				  bool bReversed = false);

protected:
	wstring clipName = L"";
	vector<Vector2> keyFrames; // 장면당 uv 좌표, 3D에서는 다른 의미로 쓰임(움직임 관련)
	uint frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	float playRate = 0.0f;
	bool bReversed = false;
	// bool bOneTime = -> 죽는 모션같이 한번 실행할때 더 넣으면 됨
};

class Animator
{
public:
	Animator();
	~Animator();

	void Update();

	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

	void AddAnimClip(AnimationClip* animClip);
	void SetCurrentAnimClip(wstring clipName);

private:
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }

private:
	unordered_map<wstring, AnimationClip*> animClips;

	AnimationClip* currentClip = nullptr;
	uint currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.0f;
};