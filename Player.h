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

	Vector3* spin; // ��ҵĳ���
	float spinSpeed; // ��ҵ�ת���ٶ�

	Vector3* positionNow; // �������������λ��
	float moveSpeed; // ��ҵ��ƶ��ٶ�

	std::vector<UseItem*> *useItems; // ��ҵ�ʹ������Ʒ�б�

public:
	void move(Vector2* direction);
	// void spin(bool isLeft); ��߻��ڿ���Ҫ��Ҫ����ת���ӽ�

	unsigned short getYellowKeyNumber() { return yellowKeyNumber; }
	unsigned short getBlueKeyNumber() { return blueKeyNumber; }
	unsigned short getRedKeyNumber() { return redKeyNumber; }

	Sword* getSword() { return sword; }
	Shield* getShield() { return shield; }

	void reciveItems(ConsumbleItem* consumbleItem); // ��ȡ������Ʒ
	void reciveUseItems(UseItem* useItem); // ��ȡʹ��������

	Player(Vector2* positionInMap);

};

