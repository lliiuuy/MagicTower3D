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

bool Object::init()
{
	bool status = true;
	status = loadTexture();
	return status;
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
	this->tag = Tag::object;
	this->name = "";
	this->lx = 30;
	this->ly = 30;
	this->lz = 30;
	this->counter = 0;
	this->position = new Vector3(positionInMap->y * lx, ly / 2, positionInMap->x * lz); // 在3D世界中的位置可以按照2DMap中的位置计算
}
