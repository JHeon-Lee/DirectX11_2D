#include "Framework.h"
#include "ShadedTexture.h"

ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	: TextureRect(position, size, rotation, path)
{
	sb = new ShadedBuffer();

	ps->Clear();
	ps->Create(ShaderPath + L"TextureFilter.hlsl", "PS");
}

ShadedTexture::~ShadedTexture()
{
	SAFE_DELETE(sb);
}

void ShadedTexture::Render()
{
	sb->SetPSBuffer(0);
	TextureRect::Render();
}

void ShadedTexture::GUI()
{
	using namespace ImGui;
	Begin("Shaded");
	{
		RadioButton("Normal",	 sb->GetSelectionPtr(), 1);
		RadioButton("AM",		 sb->GetSelectionPtr(), 2);
		RadioButton("Sepia",	 sb->GetSelectionPtr(), 3);
		RadioButton("Negative",	 sb->GetSelectionPtr(), 4);
		RadioButton("Posterize", sb->GetSelectionPtr(), 5);
	}
	End();
}
