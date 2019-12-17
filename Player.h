#pragma once
#include "Creature.h"
#include "Sword.h"
#include "Shield.h"
#include "UseItem.h"
#include "Monster.h"
#include "Objects.h"

#include "json/reader.h"
#include "json/writer.h"
#include "json/json.h"
#include <fstream>
#include <iostream>

#pragma comment(lib, "json_vc71_libmtd.lib")

class Player :
	public Creature
{
private:
	unsigned short yellowKeyNumber; // ��Կ�׵�����
	unsigned short blueKeyNumber; // ��Կ�׵�����
	unsigned short redKeyNumber; // ��Կ�׵�����

	Monster* monster;

	GLuint swordTexture;
	char* swordName;

	GLuint shieldTexture;
	char* shieldName;

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

	Player(Vector2* positionInMap);

	UseItem** getUseItems() { return useItems; }

	void load();
	void save();

	void setTalking() { this->status = PlayerStatus::talking; }
	void finishTalking() { this->status = PlayerStatus::idle; }
};

