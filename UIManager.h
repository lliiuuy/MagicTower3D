#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

class UIManager
{
private:
	GLuint left[1]; // ��ߵ�UI
	GLuint right[1]; // �ұߵ�UI

	AUX_RGBImageRec* loadBMP(char* fileName); // ��ȡbitmap�ļ�

	bool loadTexture(); // ��bitmapת������
public:
	bool init();
	void update(); // ����UI
	void loadMonster(Monster& monster); // ����Monster������

	UIManager();
};

