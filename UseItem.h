#pragma once
#include "Object.h"
class UseItem :
	public Object
{
protected:
	bool loadTexture();
	unsigned short index = 0;
	
	bool enable = false;

public:
	virtual void useItem() = 0;
	void draw2D(int width, int height);
	void draw3D();
	void collide();
	bool init();

	GLuint getTexture() { return texture[0]; }

	unsigned short getIndex() { return index; }

	UseItem(Vector2* positionInMap);
};

