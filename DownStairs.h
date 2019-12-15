#pragma once
#include "Obstacle.h"
class DownStairs :
	public Obstacle
{
private:
	float spinY = 0; // Ðý×ª
	bool loadTexture();
public:
	DownStairs(Vector2* positionInMap);
	void draw3D();
	void display(Vector3* position);
	void collide();
};

