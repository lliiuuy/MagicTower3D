#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

class UIManager
{
private:
	GLuint left[1] = { 0 }; // ��ߵ�UI
	GLuint right[1] = { 0 }; // �ұߵ�UI
	GLuint bottom[1] = { 0 }; // �����UI

	GLuint font[1] = { 0 }; // �ַ���UI

	GLuint key[3] = { 0 }; // Կ��UI

	GLuint usingStairs = 0; // ����¥��������ͼƬ
	GLuint dialogTexture = 0; // �Ի���ͼƬ

	int	base = 0; // ����print���ֵ���Ⱦ�б����
	int width, height; // ���ڵĴ�С

	AUX_RGBImageRec* loadBMP(char* fileName); // ��ȡbitmap�ļ�

	void BuildFont(); // ����������Ⱦ����

	void glPrint(int x, int y, char* string, float scale); // ����ַ���

	bool loadTexture(); // ��bitmapת������
	Monster* monster; // ������ʾ����

	bool dialogDrawing = false;
	char setence[1000] = "";
	bool isChoose = false;
	
	bool messaging = false;
	char message[100] = "";

	bool map[7][7];
	Vector2* position;
	Vector2* direction;

	bool isUsingStairs = false;
	bool isFinishUsingStairs = false;
public:

	void draw(Player* player); // �滭UI
	void loadMonster(Monster* monster); // ����Monster������
	bool init();
	UIManager(int width, int height);
	void setWindow(int width, int height);
	void dialogDraw(char* message, bool isChoose);
	void messageDraw(char* message);

	Monster* getMonster() { return monster; }

	void closeDialog() { this->dialogDrawing = false; }
	void deleteMessage() { this->messaging = false; }

	bool isDrawingDialog() { return this->dialogDrawing; }

	void useStairs() { isUsingStairs = true; }
	void finishUsingStaris() { isFinishUsingStairs = true; }

	bool getIsUsingStairs() { return isUsingStairs; }
	bool getIsFinishUsingStairs() { return isFinishUsingStairs; }
};

