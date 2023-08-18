#pragma once

class CollisionDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class Rect* r1 = nullptr;
	class Rect* r2 = nullptr;
};