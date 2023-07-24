#pragma once

class IObject
{
public:
	virtual void Init()			= 0; 
	virtual void Destroy()		= 0;	// �Ҹ��� ��ü

	virtual void Update()		= 0; 
	
	virtual void Render()		= 0;
	virtual void PostRender()	= 0;	// ��ó���� �ʿ��� �ڵ带 ó��
	
	virtual void GUI()			= 0;	// �ܺ� ���̺귯��
};