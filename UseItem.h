#pragma once
#include "Object.h"
class UseItem :
	public Object
{
protected:
	bool loadTexture();
	unsigned short index;
public:
	virtual void useItem() = 0;
	void draw2D();
	void draw3D();
	void collide();
	bool init();

	unsigned short getIndex() { return index; }

	UseItem(Vector2* positionInMap);
};

