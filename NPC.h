#pragma once
#include "Object.h"
class NPC :
	public Object
{
protected:
	std::vector<char*> messages; // ������ĶԻ�

	unsigned short indexOfMessage = 0; // ��¼�Ի����е��ڼ���
	unsigned short index = 0; // ��¼���صڼ���texture

	float spinY = 0; // NPC��ת�ĽǶ�

	virtual void talk() = 0; // ������Ի�

	bool loadTexture();

public:
	void collide();
	void draw3D();
	void draw2D(int width, int height);
	void display(Vector3* position); // NPC���������ת

	virtual void save() = 0;
	virtual void load() = 0;

	NPC(Vector2* positionInMap);
};

