#pragma once
#include "Config.h"

class Object
{
protected:
	Vector2* positionInMap; // 小地图中物体的位置
	Vector3* position; // 3D世界中物体的位置
	
	float lx, ly, lz; // 物体的大小（长宽高）

	unsigned int counter; // 计时器，用于物体自己变换

	Tag tag; // 物体的种类

	int index = 0;
	GLuint texture[4] = {0, 0, 0, 0}; // 物体的纹理，最多四帧(除了Player)

	char* name; // 物体名字

	bool destroy = false;

	AUX_RGBImageRec* loadBMP(char* fileName); // 读取bitmap文件

	virtual bool loadTexture() = 0; // 将bitmap转成纹理

public:
	virtual void draw2D(int width, int height) = 0; // 2D绘制用函数
	virtual void draw3D() = 0; // 3D绘制用函数
	virtual void collide() = 0; // 物体接触函数
	virtual bool init(); // 初始化函数

	virtual void lookAt(Vector3* position) = 0; // 看向玩家的函数(通用包括根据自身位置而改变的物体)

	Tag getTag(); // 获取物体种类
	Vector2* getPostionInMap(); // 获取物体在小地图中的位置
	Vector3* getPositon(); // 获取物体在3D世界中的位置

	char* getName() { return name; }

	bool isDestroy() { return destroy; }

	Object(Vector2* positionInMap);
};

