#pragma once
#include "Object.h"
class Wall :
	public Object
{
private:
	bool loadTexture();

public:
	Wall(Vector2* positionInMap);
	void destroy(); // ǽ������ĳЩ���ߴݻ�
	void appear(); // ��Щǽ�����صģ�����ȥ�����
	void collide();
	void draw2D();
	void draw3D();
};

