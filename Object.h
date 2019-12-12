#pragma once
#include "Config.h"

class Object
{
protected:
	Vector2* positionInMap; // С��ͼ�������λ��
	Vector3* position; // 3D�����������λ��
	
	float lx, ly, lz; // ����Ĵ�С������ߣ�

	Tag tag; // ���������
	
	GLuint texture[4] = {0, 0, 0, 0}; // ��������������֡(����Player)

	char* name; // ��������

	AUX_RGBImageRec* loadBMP(char* fileName); // ��ȡbitmap�ļ�

	virtual bool loadTexture() = 0; // ��bitmapת������

public:
	virtual void draw2D() = 0; // 2D�����ú���
	virtual void draw3D() = 0; // 3D�����ú���
	virtual void collide() = 0; // ����Ӵ�����
	virtual bool init(); // ��ʼ������

	Tag getTag(); // ��ȡ��������
	Vector2* getPostionInMap(); // ��ȡ������С��ͼ�е�λ��
	Vector3* getPositon(); // ��ȡ������3D�����е�λ��

	Object(Vector2* positionInMap);
};

