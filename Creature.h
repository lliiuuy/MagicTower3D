#pragma once
#include "Object.h"
class Creature :
	public Object
{
protected:
	unsigned int health = 0; // Ѫ��
	unsigned int attack = 0; // ������
	unsigned int defence = 0; // ������
	unsigned int money = 0; // ӵ�е�Ǯ

	virtual bool loadTexture() = 0; // ��ȡ����

public:
	virtual void collide() = 0;
	virtual void draw2D() = 0;
	virtual void draw3D() = 0;
	virtual bool init() = 0;

	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }
	unsigned int getMoney() { return money; }
	char* getName() { return name; }

	Creature(Vector2* positionInMap);
};

