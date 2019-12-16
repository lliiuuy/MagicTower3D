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

