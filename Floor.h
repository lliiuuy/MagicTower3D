#pragma once
#include "Object.h"
class Floor :
	public Object
{
private:
	bool loadTexture();
public:
	Floor(Vector2* positionInMap);
	void collide() {} // �ذ�û����ײ��Ӧ
	void draw2D();
	void draw3D();
};

