#pragma once
#include "Object.h"
class Floor :
	public Object
{
private:
	bool loadTexture();
public:
	Floor(Vector2* positionInMap);
	void collide() {} // 地板没有碰撞反应
	void draw2D();
	void draw3D();
};

