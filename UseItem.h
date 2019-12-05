#pragma once
#include "Object.h"
class UseItem :
	public Object
{
protected:
	bool loadTexture();
public:
	virtual void useItem() = 0;
	void draw2D();
	void draw3D();
	void collide();
	bool init();
	UseItem(Vector2* positionInMap);
};
