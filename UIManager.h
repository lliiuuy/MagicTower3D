#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"

class UIManager
{
private:
	GLuint left[1] = { 0 }; // 左边的UI
	GLuint right[1] = { 0 }; // 右边的UI
	GLuint bottom[1] = { 0 }; // 下面的UI

	GLuint font[1] = { 0 }; // 字符串UI

	GLuint key[3] = { 0 }; // 钥匙UI

	int	base = 0; // 用于print文字的渲染列表序号
	int width, height; // 窗口的大小

	AUX_RGBImageRec* loadBMP(char* fileName); // 读取bitmap文件

	void BuildFont(); // 创建字体渲染序列

	void glPrint(int x, int y, char* string, float scale); // 输出字符串

	bool loadTexture(); // 将bitmap转成纹理

	Player* player; // 用于显示人物属性
	Monster* monster; // 用于显示怪物
public:

	void draw(); // 绘画UI
	void loadMonster(Monster* monster); // 加载Monster的数据
	bool init();
	UIManager(int width, int height, Player* player);
	void setWindow(int width, int height);
};

