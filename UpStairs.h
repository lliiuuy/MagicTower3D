#pragma once
#include "Obstacle.h"
class UpStairs :
	public Obstacle
{
public:
	UpStairs(Vector2* positionInMap);
	void collide();
	void draw3D();
};

