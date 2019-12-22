#pragma once
#include "Object.h"
class Creature :
	public Object
{
protected:
	unsigned int health = 0; // 血量
	unsigned int attack = 0; // 攻击力
	unsigned int defence = 0; // 防御力
	unsigned int money = 0; // 拥有的钱

public:

	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }
	unsigned int getMoney() { return money; }

	Creature(Vector2* positionInMap);
};

