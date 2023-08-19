#pragma once

// JumpGameDemo�� �ʿ��� ���� ����

class JumpGameDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class JGChar* c1 = nullptr;
	class JGRect* f1 = nullptr;
	class JGRect* f2 = nullptr;
	class JGRect* f3 = nullptr;
	class JGRect* f4 = nullptr;
	class Rect* r1 = nullptr;
	class TextureRect* g1 = nullptr;
};