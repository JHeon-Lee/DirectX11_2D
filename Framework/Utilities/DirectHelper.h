#pragma once

#include "Framework.h"

class Values
{
public:
	const static Vector3 ZeroVec3;
	const static Vector3 OneVec3;
	const static Vector3 LeftVec;
	const static Vector3 RightVec;
	const static Vector3 UpVec;
	const static Vector3 DownVec;
	const static Vector3 FwdVec;
	const static Vector3 ScreenSize;

	const static Vector2 ZeroVec2;
	const static Vector2 OneVec2;
	const static Vector2 uvLT;
	const static Vector2 uvLB;
	const static Vector2 uvRT;
	const static Vector2 uvRB;

	const static Color Red;
	const static Color Green;
	const static Color Blue;
	const static Color Magenta;
	const static Color Black;
	const static Color White;
	const static Color ClearColor;

	const static Matrix Identity;
};