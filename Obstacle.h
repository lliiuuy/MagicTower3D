#pragma once
#include "Object.h"
class Obstacle :
	public Object
{
public:
	void draw2D();
	void draw3D();

	Obstacle(Vector2* positionInMap);
};

