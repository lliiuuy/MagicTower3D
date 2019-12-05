#pragma once
#include "Object.h"
class ConsumbleItem :
	public Object
{
protected:
	unsigned int health = 0; // �õ����ߺ����ӵ�Ѫ��
	unsigned int attack = 0; // �õ����ߺ����ӵĹ���
	unsigned int defence = 0; // �õ����ߺ����ӵķ���
	unsigned short redKeyNumber = 0; // �õ����ߺ����ӵĺ�Կ������
	unsigned short blueKeyNumber = 0; // �õ����ߺ����ӵ���Կ������
	unsigned short yellowKeyNumber = 0; // �õ����ߺ����ӵĻ�Կ������

	float spinY = 0; // ������3D��������ת

	bool loadTexture(); // ��ȡ����

public:
	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }
	unsigned short getRedKeyNumber() { return redKeyNumber; }
	unsigned short getBlueKeyNumber() { return blueKeyNumber; }
	unsigned short getYellowKeyNumber() { return yellowKeyNumber; }
	void draw();
	virtual void collide() = 0;
	virtual bool init() = 0;

	ConsumbleItem(Vector2* positionInMap);
};

