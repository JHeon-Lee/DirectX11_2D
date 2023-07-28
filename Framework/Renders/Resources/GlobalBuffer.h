#pragma once
#include "Framework.h"

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.World); // 행렬 초기화
	}

	void SetWorld(Matrix world)
	{
		D3DXMatrixTranspose(&data.World, &world); // 전치행렬 -> 가운데 기준으로 변환
	}

	struct Data
	{
		Matrix World;
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer // 2D라 View, Projection을 묶어서 만듬
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