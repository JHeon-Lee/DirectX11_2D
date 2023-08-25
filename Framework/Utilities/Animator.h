#pragma once
// renders -> resoures -> texture2d ���Ϻ��� ����� ����
// ���� DirectXTEX ���� _Libraries�� �߰�

class AnimationClip // Ŭ�� ������ ����
{
public:
	friend class Animator;
	AnimationClip(wstring clipName, Texture2D* srvTex, UINT frameCount,
		 		  Vector2 startPos, Vector2 endPos, float playRate,
				  bool bReversed = false);

protected:
	wstring clipName = L"";
	vector<Vector2> keyFrames; // ���� uv ��ǥ, 3D������ �ٸ� �ǹ̷� ����(������ ����)
	uint frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	float playRate = 0.0f;
	bool bReversed = false;
	// bool bOneTime = -> �״� ��ǰ��� �ѹ� �����Ҷ� �� ������ ��
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