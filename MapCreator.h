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
	Object* objects[13][13] = {0}; // �洢��ͼ�еĸ�������

	Floor* floors[13][13] = {0}; // �洢��ͼ�еĵذ�
	Floor* cells[13][13] = {0}; // �洢��ͼ�е��컨��
	
	const unsigned short mapWidth = 13; // ��ͼ�ĳ���
	const unsigned short mapHeight = 13; // ��ͼ�Ŀ��

	Vector2* upPosition; // �Ӹò���¥���������ڵ�λ��
	char upDirection[10]; // �Ӹò���¥�Ժ�����ĳ���

	Vector2* downPosition; // �Ӹò���¥���������ڵ�λ��
	char downDirection[10]; // �Ӹò���¥������ĳ���

public:
	void loadMap(int floor); // ���ļ��ж�ȡjson
	void saveMap(int floor); // ����ǰ���json�����ļ���
	void createMap2D(int width, int height); // ����2D��ͼ
	void createMap3D(); // ����3D��ͼ
	void display(Vector3* position); // ������ƶ���ת������

	Vector2* getUpPosition() { return upPosition; }
	Vector2* getDownPosition() { return downPosition; }

	Vector2* getUpDirection();
	Vector2* getDownDirection();

	Object* getObject(int x, int y) { return objects[x][y]; }

	MapCreator();
};

