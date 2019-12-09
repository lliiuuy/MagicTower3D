#pragma once
#include "Vector2.h"
#include "Object.h"
#include <string.h>
#include "json/reader.h"
#include "json/writer.h"
#include "json/json.h"
#include <fstream>
#include <iostream>

class MapCreator
{
private:
	unsigned short map[11][11] = {0}; // 存储地图中各个位置的物体
	Object* objects[11][11]; // 存储地图中的各个物体
	const unsigned short mapWidth = 11; // 地图的长度
	const unsigned short mapHeight = 11; // 地图的宽度
	
	unsigned short floor; // 人物所在层数

	Vector2* upPosition; // 从该层上楼后人物所在的位置
	char upDirection[10]; // 从该层上楼以后人物的朝向
	Vector2* downPosition; // 从该层下楼后人物所在的位置
	char downDirection[10]; // 从该层下楼后人物的朝向

	MapCreator();
	
	static MapCreator* instance;

public:
	bool loadMap(); // 从文件中读取json
	bool createMap2D(); // 创建2D地图
	bool createMap3D(); // 创建3D地图
	void upStairs(); // 上楼
	void downStairs(); // 下楼

	static MapCreator* getInstance() { return instance; }
};

