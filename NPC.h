#pragma once
#include "Object.h"
class NPC :
	public Object
{
protected:
	std::vector<char*> messages; // 与人物的对话

	unsigned short index = 0; // 记录对话进行到第几句

	float spinY = 0; // NPC旋转的角度

	virtual void talk() = 0; // 与人物对话
	void spin(); // NPC朝着玩家旋转

public:
	void collide();
	void draw();
	bool init();

	NPC(Vector2* positionInMap);
};

