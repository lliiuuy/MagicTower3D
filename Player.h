#pragma once
#include "Creature.h"
#include "Sword.h"
#include "Shield.h"
#include "UseItem.h"
#include "Monster.h"
#include "Objects.h"

class Player :
	public Creature
{
private:
	unsigned short yellowKeyNumber; // 黄钥匙的数量
	unsigned short blueKeyNumber; // 蓝钥匙的数量
	unsigned short redKeyNumber; // 红钥匙的数量

	Monster* monster;

	Object* npc;

	GLuint swordTexture;
	char swordName[100] = "";

	GLuint shieldTexture;
	char shieldName[100] = "";

	int index = 0; // 人物移动的index

	float spinY; // 玩家的朝向
	float spinYTo; // 玩家需要转向的位置
	float spinSpeed; // 玩家的转向速度

	Vector2* direction; // 玩家的朝向(左(0,1), 右(0,-1), 前(1,0), 后(-1,0))

	Vector2* positionMoveTo; // 玩家需要移动到的位置
	float moveSpeed; // 玩家的移动速度

	bool loadTexture(); // 读取人物的纹理

	UseItem* useItems[15]; // 玩家的使用型物品列表

	GLuint left[4] = { 0 }; // 人物朝左移动的纹理
	GLuint right[4] = { 0 }; // 人物朝右移动的纹理
	GLuint up[4] = { 0 }; // 人物朝前移动的纹理
	GLuint down[4] = { 0 }; // 人物朝后移动的纹理

	GLuint battleTexture[1] = { 0 };

	PlayerStatus status;

	unsigned short floor = 1; // 人物所在层数
	unsigned short maxFloor = 1; // 人物去过最高的层数

	void finishBattle() { status = PlayerStatus::idle; }
public:
	void move(bool isUp);
	void spin(bool isLeft);

	void display();

	void draw3D() { ; } // 不在3D中绘制
	void draw2D(int width, int height);
	void collide() { ; } // 不会碰撞
	void display(Vector3* position) { ; }

	unsigned short getYellowKeyNumber() { return yellowKeyNumber; }
	unsigned short getBlueKeyNumber() { return blueKeyNumber; }
	unsigned short getRedKeyNumber() { return redKeyNumber; }

	unsigned short getFloor() { return floor; }
	unsigned short getMaxFloor() { return maxFloor; }

	void upStairs(Vector2* position, Vector2* direction);
	void downStairs(Vector2* position, Vector2* direction);
	void finishUsingStairs() { this->status = PlayerStatus::idle; }

	float getSpinY() { return spinY; }

	GLuint getSwordTexture() { return swordTexture; }
	char* getSwordName() { return swordName; }
	GLuint getShieldTexture() { return shieldTexture; }
	char* getShieldName() { return shieldName; }

	PlayerStatus getStatus() { return status; }

	void reciveItems(ConsumbleItem* consumbleItem); // 获取消耗物品
	void reciveUseItems(UseItem* useItem); // 获取使用型物体

	Vector2* getDirection() { return direction; }
	void SetDirection(Vector2* direction);

	void purchase(int money) { this->money -= money; }

	void openDoor(int tag);
	void battle(Monster* monster);
	void talk(NPC* npc);
	void talk(Boss* boss);

	void action(); // 和NPC互动获得道具

	Object* getNPC() { return npc; }

	void endTalk() { this->npc = NULL; this->status = PlayerStatus::idle; }

	Player(Vector2* positionInMap);

	UseItem** getUseItems() { return useItems; }

	void action3F() 
	{
		// 没收道具
		sprintf_s(this->swordName, "");
		this->swordTexture = 0;
		sprintf_s(this->shieldName, "");
		this->shieldTexture = 0;
		this->health = 400;
		this->attack = 10;
		this->defence = 10;
		AudioManager::playSound("Data/Audio/battle.wav");
		this->status = PlayerStatus::animating;
	}

	void load();
	void save();
};

