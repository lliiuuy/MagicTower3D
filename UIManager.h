#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

// ����
#include "GreenSlime.h"

class UIManager
{
private:
	GLuint left[1] = { 0 }; // ��ߵ�UI
	GLuint right[1] = { 0 }; // �ұߵ�UI
	GLuint bottom[1] = { 0 }; // �����UI

	GLuint font[1] = { 0 }; // �ַ���UI

	GLuint key[3] = { 0 }; // Կ��UI

	int	base = 0; // ����print���ֵ���Ⱦ�б����
	int width, height; // ���ڵĴ�С

	AUX_RGBImageRec* loadBMP(char* fileName); // ��ȡbitmap�ļ�

	void BuildFont(); // ����������Ⱦ����

	void glPrint(int x, int y, char* string, float scale); // ����ַ���

	bool loadTexture(); // ��bitmapת������
	Monster* monster; // ������ʾ����

public:

	void draw(Player* player); // �滭UI
	void loadMonster(Monster* monster); // ����Monster������
	bool init();
	UIManager(int width, int height);
	void setWindow(int width, int height);
};

