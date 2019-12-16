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

	std::vector<char*> messages;

	bool loadTexture();

public:
	unsigned int getCost() { return cost; }
	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }

	void draw2D(int width, int height);
	void draw3D();
	void save();
	void load();
	void collide();
	void display(Vector3* position) {}

	Altar(Vector2* positionInMap);
};

