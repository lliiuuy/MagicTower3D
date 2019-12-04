#pragma once
#include "Object.h"
class Wall :
	public Object
{
private:
	unsigned short status; // ǽ��״̬

	bool loadTexture();

public:
	Wall(unsigned short status, Vector2* positionInMap);
	void destroy(); // ǽ������ĳЩ���ߴݻ�
	void appear(); // ��Щǽ�����صģ�����ȥ�����
	void collide();
	void draw();
	bool init();
};

