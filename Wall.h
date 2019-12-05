#pragma once
#include "Object.h"
class Wall :
	public Object
{
private:
	unsigned short status; // 墙的状态

	bool loadTexture();

public:
	Wall(unsigned short status, Vector2* positionInMap);
	void destroy(); // 墙可以用某些道具摧毁
	void appear(); // 有些墙是隐藏的，走上去会出现
	void collide();
	void draw();
	bool init();
};

