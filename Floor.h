#pragma once
#include "Obstacle.h"
class Floor :
	public Obstacle
{
private:
	bool loadTexture();
public:
	Floor(Vector2* positionInMap, bool isFloor);
	void collide() {} // �ذ�û����ײ��Ӧ
	void draw3D();
};

