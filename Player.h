#pragma once
#include "Creature.h"
#include "Sword.h"
#include "Shield.h"
#include "UseItem.h"

class Player :
	public Creature
{
private:
	unsigned short yellowKeyNumber; // 黄钥匙的数量
	unsigned short blueKeyNumber; // 蓝钥匙的数量
	unsigned short redKeyNumber; // 红钥匙的数量

	Sword* sword; // 玩家所持有的剑
	Shield* shield; // 玩家持有的盾

	Vector3* spin; // 玩家的朝向
	float spinSpeed; // 玩家的转向速度

	Vector3* positionNow; // 玩家现在所处的位置
	float moveSpeed; // 玩家的移动速度

	std::vector<UseItem*> *useItems; // 玩家的使用型物品列表

public:
	void move(Vector2* direction);
	// void spin(bool isLeft); 这边还在考虑要不要自由转动视角

	unsigned short getYellowKeyNumber() { return yellowKeyNumber; }
	unsigned short getBlueKeyNumber() { return blueKeyNumber; }
	unsigned short getRedKeyNumber() { return redKeyNumber; }

	Sword* getSword() { return sword; }
	Shield* getShield() { return shield; }

	void reciveItems(ConsumbleItem* consumbleItem); // 获取消耗物品
	void reciveUseItems(UseItem* useItem); // 获取使用型物体

	Player(Vector2* positionInMap);

};

