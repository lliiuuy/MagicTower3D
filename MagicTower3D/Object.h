#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Tag.h"

#include<windows.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#include <vector>

#include<GL\GL.h>
#include<GL\GLAUX.H>
#include<GL\GLU.h>
#include<GLFW\glfw3.h>

class Object
{
protected:
	Vector2* positionInMap; // С��ͼ�������λ��
	Vector3* position; // 3D�����������λ��
	
	Tag tag; // ���������
	
	GLuint texture[4] = {0, 0, 0, 0}; // ��������������֡

	char* name; // ��������

	AUX_RGBImageRec loadBMP(char* fileName); // ��ȡbitmap�ļ�

	virtual bool loadTexture() = 0; // ��bitmapת������

public:
	virtual void draw() = 0; // �����ú���
	virtual void collide() = 0; // ����Ӵ�����
	virtual bool init() = 0; // ��ʼ������

	Tag getTag(); // ��ȡ��������
	Vector2* getPostionInMap(); // ��ȡ������С��ͼ�е�λ��
	Vector3* getPositon(); // ��ȡ������3D�����е�λ��

	Object(Vector2* positionInMap);
};

