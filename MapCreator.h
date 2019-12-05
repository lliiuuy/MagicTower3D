#pragma once
#include "Vector2.h"

class MapCreator
{
private:
	unsigned short map[11][11] = {0}; // 存储地图中各个位置的物体
	const unsigned short mapWidth = 11; // 地图的长度
	const unsigned short mapHeight = 11; // 地图的宽度
	
	unsigned short floor; // 人物所在层数

	Vector2* upPosition; // 从该层上楼后人物所在的位置
	Vector2* downPosition; // 从该层下楼后人物所在的位置

public:
	bool loadMap(char* fileName); // 从文件中读取json
	bool createMap(); // 创建地图
	void upStairs(); // 上楼
	void downStairs(); // 下楼

	MapCreator();
};

