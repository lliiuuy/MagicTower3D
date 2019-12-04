#pragma once
#include "Object.h"
class NPC :
	public Object
{
protected:
	std::vector<char*> messages; // ������ĶԻ�

	unsigned short index = 0; // ��¼�Ի����е��ڼ���

	float spinY = 0; // NPC��ת�ĽǶ�

	virtual void talk() = 0; // ������Ի�
	void spin(); // NPC���������ת

public:
	void collide();
	void draw();
	bool init();

	NPC(Vector2* positionInMap);
};

