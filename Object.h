#pragma once
#include "Config.h"

class Object
{
protected:
	Vector2* positionInMap; // 小地图中物体的位置
	Vector3* position; // 3D世界中物体的位置
	
	Tag tag; // 物体的种类
	
	GLuint texture[4] = {0, 0, 0, 0}; // 物体的纹理，最多四帧

	char* name; // 物体名字

	AUX_RGBImageRec* loadBMP(char* fileName); // 读取bitmap文件

	virtual bool loadTexture() = 0; // 将bitmap转成纹理

public:
	virtual void draw2D() = 0; // 2D绘制用函数
	virtual void draw3D() = 0; // 3D绘制用函数
	virtual void collide() = 0; // 物体接触函数
	virtual bool init(); // 初始化函数

	Tag getTag(); // 获取物体种类
	Vector2* getPostionInMap(); // 获取物体在小地图中的位置
	Vector3* getPositon(); // 获取物体在3D世界中的位置

	Object(Vector2* positionInMap);
};

