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
	unsigned short map[11][11] = {0}; // �洢��ͼ�и���λ�õ�����
	Object* objects[11][11]; // �洢��ͼ�еĸ�������
	const unsigned short mapWidth = 11; // ��ͼ�ĳ���
	const unsigned short mapHeight = 11; // ��ͼ�Ŀ��
	
	unsigned short floor; // �������ڲ���

	Vector2* upPosition; // �Ӹò���¥���������ڵ�λ��
	char upDirection[10]; // �Ӹò���¥�Ժ�����ĳ���
	Vector2* downPosition; // �Ӹò���¥���������ڵ�λ��
	char downDirection[10]; // �Ӹò���¥������ĳ���

	MapCreator();
	
	static MapCreator* instance;

public:
	bool loadMap(); // ���ļ��ж�ȡjson
	bool createMap2D(); // ����2D��ͼ
	bool createMap3D(); // ����3D��ͼ
	void upStairs(); // ��¥
	void downStairs(); // ��¥

	static MapCreator* getInstance() { return instance; }
};

