#pragma once
#include "ConsumbleItem.h"
class Sword :
	public ConsumbleItem
{
protected:
	char* uiName; // 显示在UI上的名字和真正的名字不同
	bool loadTexture();

public:
	Sword(Vector2* positionInMap);
	GLuint getTexture() { return texture[0]; }
	char* getUIName() { return uiName; }
};

