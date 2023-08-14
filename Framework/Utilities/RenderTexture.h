#pragma once

class RenderTexture
{
public:
	RenderTexture();
	~RenderTexture();

	void RenderToTexture();
	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	ID3D11Texture2D* texture = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;
};

// ī�޶� ���� ������ �����ϴ� �ʸ����� ������ ��
// texture2d = �ʸ� -> ī�޶� ���� ������ ����Ǵ� ��
// rtv = �ʸ��� ī�޶� ���� -> rtv�� ����ϸ� ������ ����� �ش� rtv�� �����ϴ� �ؽ�ó�� ����
// srv = �ʸ��� ��ȭ�⿡ ���� -> srv�� ����ϸ� ���̴����� �ش� srv�� �����ϴ� �ؽ�ó�� �����͸� ���� �� ����