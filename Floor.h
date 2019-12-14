#pragma once
#include "Obstacle.h"
class Floor :
	public Obstacle
{
private:
	bool loadTexture();
public:
	Floor(Vector2* positionInMap, bool isFloor);
	void collide() {}
	void draw3D();
};

