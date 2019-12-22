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

public:

	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }
	unsigned int getMoney() { return money; }

	Creature(Vector2* positionInMap);
};

