#pragma once
#include "ConsumbleItem.h"
class Shield :
	public ConsumbleItem
{
protected:
	char* uiName; // ��ʾ��UI��������ֺ����������ֲ�ͬ
	bool loadTexture();

public:
	Shield(Vector2* positionInMap);
	GLuint getTexture() { return texture[0]; }
	char* getUIName() { return uiName; }
};

