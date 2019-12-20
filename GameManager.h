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

	int width, height; // 屏幕长宽

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
	void load(); // 存人物Json
	void save(); // 读取人物Json
	void drawScene();
	void setWindow(int width, int height);
	void upStairs(); // 上楼
	void downStairs(); // 下楼
	void movePlayer(bool isUp); // 移动玩家
	void spinPlayer(bool isLeft);
	void mouseButtonClick(int x, int y);
};

