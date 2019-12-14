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

	float spinY; // 玩家的朝向
	float spinYTo; // 玩家需要转向的位置
	float spinSpeed; // 玩家的转向速度

	Vector2* direction; // 玩家的朝向(左(-1,0), 右(1,0), 前(0,-1), 后(0,1))

	Vector2* positionMoveTo; // 玩家需要移动到的位置
	float moveSpeed; // 玩家的移动速度

	bool loadTexture(); // 读取人物的纹理

	std::vector<UseItem*> *useItems; // 玩家的使用型物品列表

	GLuint left[4] = { 0 }; // 人物朝左移动的纹理
	GLuint right[4] = { 0 }; // 人物朝右移动的纹理
	GLuint up[4] = { 0 }; // 人物朝前移动的纹理
	GLuint down[4] = { 0 }; // 人物朝后移动的纹理

	PlayerStatus status;

	unsigned short floor = 1; // 人物所在层数
public:
	void move(bool isUp);
	void spin(bool isLeft);

	void display();

	void draw3D() { ; } // 不在3D中绘制
	void draw2D();
	void collide() { ; } // 不会碰撞
	void lookAt(Vector3* position) { ; }

	unsigned short getYellowKeyNumber() { return yellowKeyNumber; }
	unsigned short getBlueKeyNumber() { return blueKeyNumber; }
	unsigned short getRedKeyNumber() { return redKeyNumber; }

	unsigned short getFloor() { return floor; }

	void upStairs() { floor++; }
	void downStairs() { floor--; }

	float getSpinY() { return spinY; }

	PlayerStatus getStatus() { return status; }

	Sword* getSword() { return sword; }
	Shield* getShield() { return shield; }

	void reciveItems(ConsumbleItem* consumbleItem); // 获取消耗物品
	void reciveUseItems(UseItem* useItem); // 获取使用型物体

	Player(Vector2* positionInMap);

	std::vector<UseItem*>* getUseItem() { return useItems; }
};

