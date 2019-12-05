#pragma once
#include "Vector2.h"

class MapCreator
{
private:
	unsigned short map[11][11] = {0}; // �洢��ͼ�и���λ�õ�����
	const unsigned short mapWidth = 11; // ��ͼ�ĳ���
	const unsigned short mapHeight = 11; // ��ͼ�Ŀ��
	
	unsigned short floor; // �������ڲ���

	Vector2* upPosition; // �Ӹò���¥���������ڵ�λ��
	Vector2* downPosition; // �Ӹò���¥���������ڵ�λ��

public:
	bool loadMap(char* fileName); // ���ļ��ж�ȡjson
	bool createMap(); // ������ͼ
	void upStairs(); // ��¥
	void downStairs(); // ��¥

	MapCreator();
};

