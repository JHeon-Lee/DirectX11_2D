#pragma once
#include "Framework.h"

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.World); // ��� �ʱ�ȭ
	}

	void SetWorld(Matrix world)
	{
		D3DXMatrixTranspose(&data.World, &world); // ��ġ��� -> ��� �������� ��ȯ
	}

	struct Data
	{
		Matrix World;
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer // 2D�� View, Projection�� ��� ����
{
public:
	VPBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.View);
		D3DXMatrixIdentity(&data.Projection);
	}

	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.View, &view);
	}

	void SetProjection(Matrix projection)
	{
		D3DXMatrixTranspose(&data.Projection, &projection);
	}

	struct Data
	{
		Matrix View;
		Matrix Projection;
	};
private:
	Data data;
};