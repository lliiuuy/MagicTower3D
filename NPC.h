#pragma once
#include "Object.h"
#include "Message.h"

class NPC :
	public Object
{
protected:
	std::vector<Message*> *messages; // ������ĶԻ�

	unsigned short numberofMessages = 0; // ��¼һ���м����Ի�
	unsigned short indexOfMessages = 0; // ��¼�Ի����е��ڼ���
	unsigned short index = 0; // ��¼���صڼ���texture

	float spinY = 0; // NPC��ת�ĽǶ�

	virtual void talk() = 0; // ������Ի�

	bool loadTexture();

	bool choosing = false;

public:
	void collide();
	void draw3D();
	void draw2D(int width, int height);
	void display(Vector3* position); // NPC���������ת

	virtual void save() = 0;
	virtual void load() = 0;

	NPC(Vector2* positionInMap);
};

