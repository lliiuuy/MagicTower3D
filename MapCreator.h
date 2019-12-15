#pragma once
#include "Vector2.h"
#include "Object.h"
#include "Objects.h"
#include "Config.h"
#include <string.h>

#include "json/reader.h"
#include "json/writer.h"
#include "json/json.h"
#include <fstream>
#include <iostream>

#pragma comment(lib, "json_vc71_libmtd.lib")

class MapCreator
{
private:
	Object* objects[13][13] = {0}; // 存储地图中的各个物体

	Floor* floors[13][13] = {0}; // 存储地图中的地板
	Floor* cells[13][13] = {0}; // 存储地图中的天花板
	
	const unsigned short mapWidth = 13; // 地图的长度
	const unsigned short mapHeight = 13; // 地图的宽度

	Vector2* upPosition; // 从该层上楼后人物所在的位置
	char upDirection[10]; // 从该层上楼以后人物的朝向
	Vector2* downPosition; // 从该层下楼后人物所在的位置
	char downDirection[10]; // 从该层下楼后人物的朝向

	Player* player; // 可能是用来测试的

	void display(); // 物体的移动，转向处理函数

public:
	bool loadMap(); // 从文件中读取json
	bool createMap2D(int width, int height); // 创建2D地图
	bool createMap3D(); // 创建3D地图
	void upStairs(); // 上楼
	void downStairs(); // 下楼

	MapCreator(Player* player);
};

