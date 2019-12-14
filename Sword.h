#pragma once
#include "ConsumbleItem.h"
class Sword :
	public ConsumbleItem
{
protected:
	char* uiName; // ��ʾ��UI�ϵ����ֺ����������ֲ�ͬ
	bool loadTexture();

public:
	Sword(Vector2* positionInMap);
	GLuint getTexture() { return texture[0]; }
	char* getUIName() { return uiName; }
};

