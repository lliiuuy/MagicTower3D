#pragma once
#include "Obstacle.h"
class Wall :
	public Obstacle
{
private:
	bool loadTexture();

public:
	Wall(Vector2* positionInMap);
	void destroy(); // ǽ������ĳЩ���ߴݻ�
	void appear(); // ��Щǽ�����صģ�����ȥ�����
	void collide();
};

