#pragma once
#include "Object.h"
class Altar : // 祭坛：用于花钱增加属性
	public Object
{
private:
	unsigned int cost = 0; // 花费的金钱量
	unsigned int health = 0; // 增加的血量
	unsigned int attack = 0; // 增加的攻击力
	unsigned int defence = 0; // 增加的防御力

	std::vector<char* > messages;

	bool loadTexture();

public:
	unsigned int getCost() { return cost; }
	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }

	bool init();
	void draw();
	void collide();

	Altar(Vector2* positionInMap);
};

