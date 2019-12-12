#pragma once
#include "Object.h"
class Wall :
	public Object
{
private:
	bool loadTexture();

public:
	Wall(Vector2* positionInMap);
	void destroy(); // 墙可以用某些道具摧毁
	void appear(); // 有些墙是隐藏的，走上去会出现
	void collide();
	void draw2D();
	void draw3D();
};

