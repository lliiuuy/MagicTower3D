#pragma once
#include "Object.h"
class Altar : // ��̳�����ڻ�Ǯ��������
	public Object
{
private:
	unsigned int cost = 0; // ���ѵĽ�Ǯ��
	unsigned int health = 0; // ���ӵ�Ѫ��
	unsigned int attack = 0; // ���ӵĹ�����
	unsigned int defence = 0; // ���ӵķ�����

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

