#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

class UIManager
{
private:
	GLuint left[1] = {0}; // ��ߵ�UI
	GLuint right[1] = {0}; // �ұߵ�UI

	AUX_RGBImageRec* loadBMP(char* fileName); // ��ȡbitmap�ļ�

	bool loadTexture(); // ��bitmapת������

	bool init();

	UIManager();

	static UIManager* instance;
public:
	static void update(); // ����UI
	static UIManager* getInstance() { return instance; }
	void loadMonster(Monster& monster); // ����Monster������
};

