#pragma once
#include "Object.h"
class ConsumbleItem :
	public Object
{
protected:
	unsigned int health = 0; // 拿到道具后增加的血量
	unsigned int attack = 0; // 拿到道具后增加的攻击
	unsigned int defence = 0; // 拿到道具后增加的防御
	unsigned short redKeyNumber = 0; // 拿到道具后增加的红钥匙数量
	unsigned short blueKeyNumber = 0; // 拿到道具后增加的蓝钥匙数量
	unsigned short yellowKeyNumber = 0; // 拿到道具后增加的黄钥匙数量

	float spinY = 0; // 道具在3D场景中旋转

	void display(Vector3* position);

	bool loadTexture(); // 读取纹理

public:
	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }
	unsigned short getRedKeyNumber() { return redKeyNumber; }
	unsigned short getBlueKeyNumber() { return blueKeyNumber; }
	unsigned short getYellowKeyNumber() { return yellowKeyNumber; }
	void draw2D(int width, int height);
	void draw3D();
	void collide();

	ConsumbleItem(Vector2* positionInMap);
};

