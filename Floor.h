#pragma once
#include "Obstacle.h"
class Floor :
	public Obstacle
{
private:
	bool loadTexture();
public:
	Floor(Vector2* positionInMap, bool isFloor);
	void collide() {} // 地板没有碰撞反应
	void draw3D();
};

