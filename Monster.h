#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
protected: 
	float spinY = 0; // Y����ת��

	void spin(); // �����������ڷ�����ת

	bool loadTexture(); // ����̶�����֡

public:
	Monster(Vector2* positionInMap);
	void collide();
	void draw2D();
	void draw3D();
	bool init();
};

