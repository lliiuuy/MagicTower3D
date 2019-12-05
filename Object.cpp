#include "Object.h"

AUX_RGBImageRec* Object::loadBMP(char* fileName)
{
	FILE* file = NULL;
	if (!fileName)
		return NULL;

	fopen_s(&file, fileName, "r");
	if (file)
	{
		fclose(file);
		return auxDIBImageLoad(fileName);
	}

	return NULL;
}

Tag Object::getTag()
{
	return tag;
}

Vector2* Object::getPostionInMap()
{
	return positionInMap;
}

Vector3* Object::getPositon()
{
	return position;
}

Object::Object(Vector2* positionInMap)
{
	this->positionInMap = positionInMap;
	this->position = new Vector3(0, 0, 0); // ��3D�����е�λ�ÿ��԰���2DMap�е�λ�ü���
	this->tag = Tag::object;
	this->name = " ";
}
