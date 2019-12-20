#pragma once
#include "AudioManager.h"
#include "MapCreator.h"
#include "BattleController.h"
#include "UIManager.h"
#include "Player.h"

class GameManager
{
private:
	MapCreator* mapCreator;
	BattleController* battleController;
	UIManager* uiManager;
	Player* player;

	int width, height; // ��Ļ����

	bool usingStairs = false;
	bool finishUsingStairs = false;

	bool isUpStairs = false;

	bool talking = false;

	bool is3FAnimated = false;

	unsigned short counter = 0;

	void detectCollision();
public:
	GameManager(int width, int height);
	void init();
	void load(); // ������Json
	void save(); // ��ȡ����Json
	void drawScene();
	void setWindow(int width, int height);
	void upStairs(); // ��¥
	void downStairs(); // ��¥
	void movePlayer(bool isUp); // �ƶ����
	void spinPlayer(bool isLeft);
	void mouseButtonClick(int x, int y);
};

