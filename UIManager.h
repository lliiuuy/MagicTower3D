#pragma once
#include "Config.h"
#include "Monster.h"
#include "Player.h"
#include "AudioManager.h"

class UIManager
{
private:
	GLuint left[1] = { 0 }; // 左边的UI
	GLuint right[1] = { 0 }; // 右边的UI
	GLuint bottom[1] = { 0 }; // 下面的UI

	GLuint font[1] = { 0 }; // 字符串UI

	GLuint key[3] = { 0 }; // 钥匙UI

	GLuint usingStairs = 0; // 上下楼过场所用图片
	GLuint dialogTexture = 0; // 对话框图片

	int	base = 0; // 用于print文字的渲染列表序号
	int width, height; // 窗口的大小

	AUX_RGBImageRec* loadBMP(char* fileName); // 读取bitmap文件

	void BuildFont(); // 创建字体渲染序列

	void glPrint(int x, int y, char* string, float scale); // 输出字符串

	bool loadTexture(); // 将bitmap转成纹理
	Monster* monster; // 用于显示怪物

	bool dialogDrawing = false;
	char sentence[1000] = "";
	bool isChoose = false;
	
	bool messaging = false;
	char message[100] = "";

	bool map[7][7];
	Vector2* position;
	Vector2* direction;

	bool isUsingStairs = false;
	bool isFinishUsingStairs = false;

	bool isAnimation = false;
public:

	void draw(Player* player); // 绘画UI
	void loadMonster(Monster* monster); // 加载Monster的数据
	bool init();
	UIManager(int width, int height);
	void setWindow(int width, int height);
	void dialogDraw(char* message, bool isChoose);
	void messageDraw(char* message);

	Monster* getMonster() { return monster; }

	void closeDialog() { this->dialogDrawing = false; }
	void deleteMessage() { this->messaging = false; }

	bool isDrawingDialog() { return this->dialogDrawing; }

	void useStairs() 
	{ 
		isUsingStairs = true; 
		AudioManager::playSound("Data/Audio/usingStairs.wav");
	}

	void finishUsingStaris() 
	{ 
		isFinishUsingStairs = true; 
		AudioManager::playSound("Data/Audio/usingStairs.wav");
	}

	bool getIsUsingStairs() { return isUsingStairs; }
	bool getIsFinishUsingStairs() { return isFinishUsingStairs; }
};

