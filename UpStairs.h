#pragma once
#include "Obstacle.h"
class UpStairs :
	public Obstacle
{
private:
	float spinY = 0;
	bool loadTexture();
public:
	UpStairs(Vector2* positionInMap);
	void draw3D();
	void display(Vector3* position);
	void collide();
};

