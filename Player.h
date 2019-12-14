#pragma once
#include "Creature.h"
#include "Sword.h"
#include "Shield.h"
#include "UseItem.h"

class Player :
	public Creature
{
private:
	unsigned short yellowKeyNumber; // ��Կ�׵�����
	unsigned short blueKeyNumber; // ��Կ�׵�����
	unsigned short redKeyNumber; // ��Կ�׵�����

	Sword* sword; // ��������еĽ�
	Shield* shield; // ��ҳ��еĶ�

	float spinY; // ��ҵĳ���
	float spinYTo; // �����Ҫת���λ��
	float spinSpeed; // ��ҵ�ת���ٶ�

	Vector2* direction; // ��ҵĳ���(��(-1,0), ��(1,0), ǰ(0,-1), ��(0,1))

	Vector2* positionMoveTo; // �����Ҫ�ƶ�����λ��
	float moveSpeed; // ��ҵ��ƶ��ٶ�

	bool loadTexture(); // ��ȡ���������

	std::vector<UseItem*> *useItems; // ��ҵ�ʹ������Ʒ�б�

	GLuint left[4] = { 0 }; // ���ﳯ���ƶ�������
	GLuint right[4] = { 0 }; // ���ﳯ���ƶ�������
	GLuint up[4] = { 0 }; // ���ﳯǰ�ƶ�������
	GLuint down[4] = { 0 }; // ���ﳯ���ƶ�������

	PlayerStatus status;

	unsigned short floor = 1; // �������ڲ���
public:
	void move(bool isUp);
	void spin(bool isLeft);

	void display();

	void draw3D() { ; } // ����3D�л���
	void draw2D();
	void collide() { ; } // ������ײ
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

	void reciveItems(ConsumbleItem* consumbleItem); // ��ȡ������Ʒ
	void reciveUseItems(UseItem* useItem); // ��ȡʹ��������

	Player(Vector2* positionInMap);

	std::vector<UseItem*>* getUseItem() { return useItems; }
};

