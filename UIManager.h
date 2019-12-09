#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

class UIManager
{
private:
	GLuint left[1] = {0}; // 左边的UI
	GLuint right[1] = {0}; // 右边的UI

	AUX_RGBImageRec* loadBMP(char* fileName); // 读取bitmap文件

	bool loadTexture(); // 将bitmap转成纹理

	bool init();

	UIManager();

	static UIManager* instance;
public:
	static void update(); // 更新UI
	static UIManager* getInstance() { return instance; }
	void loadMonster(Monster& monster); // 加载Monster的数据
};

