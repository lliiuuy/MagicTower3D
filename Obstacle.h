#pragma once
#include "Object.h"
class Obstacle :
	public Object
{
public:
	void draw2D(int width, int height);
	void draw3D();
	void lookAt(Vector3* position) {}

	Obstacle(Vector2* positionInMap);
};

