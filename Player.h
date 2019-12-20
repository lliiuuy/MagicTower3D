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
	unsigned short yellowKeyNumber; // ��Կ�׵�����
	unsigned short blueKeyNumber; // ��Կ�׵�����
	unsigned short redKeyNumber; // ��Կ�׵�����

	Monster* monster;

	Object* npc;

	GLuint swordTexture;
	char swordName[100] = "";

	GLuint shieldTexture;
	char shieldName[100] = "";

	int index = 0; // �����ƶ���index

	float spinY; // ��ҵĳ���
	float spinYTo; // �����Ҫת���λ��
	float spinSpeed; // ��ҵ�ת���ٶ�

	Vector2* direction; // ��ҵĳ���(��(0,1), ��(0,-1), ǰ(1,0), ��(-1,0))

	Vector2* positionMoveTo; // �����Ҫ�ƶ�����λ��
	float moveSpeed; // ��ҵ��ƶ��ٶ�

	bool loadTexture(); // ��ȡ���������

	UseItem* useItems[15]; // ��ҵ�ʹ������Ʒ�б�

	GLuint left[4] = { 0 }; // ���ﳯ���ƶ�������
	GLuint right[4] = { 0 }; // ���ﳯ���ƶ�������
	GLuint up[4] = { 0 }; // ���ﳯǰ�ƶ�������
	GLuint down[4] = { 0 }; // ���ﳯ���ƶ�������

	GLuint battleTexture[1] = { 0 };

	PlayerStatus status;

	unsigned short floor = 1; // �������ڲ���
	unsigned short maxFloor = 1; // ����ȥ����ߵĲ���

	void finishBattle() { status = PlayerStatus::idle; }
public:
	void move(bool isUp);
	void spin(bool isLeft);

	void display();

	void draw3D() { ; } // ����3D�л���
	void draw2D(int width, int height);
	void collide() { ; } // ������ײ
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

	void reciveItems(ConsumbleItem* consumbleItem); // ��ȡ������Ʒ
	void reciveUseItems(UseItem* useItem); // ��ȡʹ��������

	Vector2* getDirection() { return direction; }
	void SetDirection(Vector2* direction);

	void purchase(int money) { this->money -= money; }

	void openDoor(int tag);
	void battle(Monster* monster);
	void talk(NPC* npc);
	void talk(Boss* boss);

	void action(); // ��NPC������õ���

	Object* getNPC() { return npc; }

	void endTalk() { this->npc = NULL; this->status = PlayerStatus::idle; }

	Player(Vector2* positionInMap);

	UseItem** getUseItems() { return useItems; }

	void action3F() 
	{
		// û�յ���
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

