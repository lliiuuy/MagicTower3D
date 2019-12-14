#pragma once
#include "ConsumbleItem.h"
class Shield :
	public ConsumbleItem
{
protected:
	char* uiName; // 显示在UI上面的名字和真正的名字不同
	bool loadTexture();

public:
	Shield(Vector2* positionInMap);
	GLuint getTexture() { return texture[0]; }
	char* getUIName() { return uiName; }
};

