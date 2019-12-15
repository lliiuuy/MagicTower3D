#pragma once
#include "Door.h"
class Prison :
	public Door
{
public:
	Prison(Vector2* positionInMap);
	void draw2D(int width, int height);
	void draw3D();
};

