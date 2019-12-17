#pragma once
#include "Object.h"
class UseItem :
	public Object
{
protected:
	bool loadTexture();
	unsigned short index = 0;
	
	bool enable = false;

	float spinY = 0; // Ðý×ª

public:
	virtual void useItem() = 0;
	void draw2D(int width, int height);
	void draw3D();
	void collide();
	void display(Vector3 *position);
	
	virtual void save() = 0;
	virtual void load() = 0;

	bool isEnable() { return enable; }

	void enableItem() { this->enable = true; }
	void disableItem() { this->enable = false; }

	GLuint getTexture() { return texture[0]; }

	unsigned short getIndex() { return index; }

	UseItem(Vector2* positionInMap);
};

