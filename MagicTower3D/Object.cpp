#include "Object.h"

AUX_RGBImageRec Object::loadBMP(char* fileName)
{
	return AUX_RGBImageRec();
}

bool Object::loadTexture()
{
	return false;
}

Tag Object::getTag()
{
	return Tag();
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
