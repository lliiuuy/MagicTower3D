#pragma once
#include "Obstacle.h"
class Wall :
	public Obstacle
{
private:
	bool loadTexture();

public:
	Wall(Vector2* positionInMap);
	void destroy(); // 墙可以用某些道具摧毁
	void appear(); // 有些墙是隐藏的，走上去会出现
	void collide();
};

