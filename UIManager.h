#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

class UIManager
{
private:
	GLuint left[1]; // 左边的UI
	GLuint right[1]; // 右边的UI

	AUX_RGBImageRec* loadBMP(char* fileName); // 读取bitmap文件

	bool loadTexture(); // 将bitmap转成纹理
public:
	bool init();
	void update(); // 更新UI
	void loadMonster(Monster& monster); // 加载Monster的数据

	UIManager();
};

