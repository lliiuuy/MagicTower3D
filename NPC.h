#pragma once
#include "Object.h"
class NPC :
	public Object
{
protected:
	std::vector<char*> messages; // 与人物的对话

	unsigned short indexOfMessage = 0; // 记录对话进行到第几句
	unsigned short indexOfTexture = 0; // 记录加载第几张texture

	float spinY = 0; // NPC旋转的角度

	virtual void talk() = 0; // 与人物对话

	bool loadTexture();

public:
	void collide();
	void draw3D();
	void draw2D(int width, int height);
	void lookAt(Vector3* position); // NPC朝着玩家旋转

	NPC(Vector2* positionInMap);
};

