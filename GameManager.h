#pragma once
#include "AudioManager.h"
#include "MapCreator.h"
#include "UIManager.h"
#include "Player.h"

class GameManager
{
private:
	MapCreator* mapCreator;
	UIManager* uiManager;
	Player* player;

	int width, height; // ��Ļ����
	int originWidth, originHeight;

	bool usingStairs = false;
	bool finishUsingStairs = false;

	bool isUpStairs = false;

	bool talking = false;

	bool isAnimated = false;

	bool gameOver = false;
	bool restart = false;

	unsigned short counter = 0;

	void detectCollision();
public:
	GameManager(int width, int height, int originWidth, int originHeight);
	void init();
	void load(); // ������Json
	void save(); // ��ȡ����Json
	void drawScene();
	void setWindow(int width, int height, int originWidth, int originHeight);
	void upStairs(); // ��¥
	void downStairs(); // ��¥
	void movePlayer(bool isUp); // �ƶ����
	void spinPlayer(bool isLeft);
	void mouseButtonClick(int x, int y);
	void newGame();

	bool isGameOver() { return this->gameOver; }
};

