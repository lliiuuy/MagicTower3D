#pragma once
#include "Object.h"
class UseItem :
	public Object
{
protected:
	bool loadTexture();
	unsigned short index = 0;
	
	bool enable = false;
	bool isUsing = false;
	bool canUse = false;

	float spinY = 0; // Ðý×ª

public:
	virtual std::string save() = 0;
	virtual void load(std::string jsonString) = 0;

	virtual void useItem() = 0;
	virtual void closeItem() = 0;

	void draw2D(int width, int height);
	void draw3D();
	void collide();
	void display(Vector3 *position);

	bool isEnable() { return enable; }
	bool ifIsUsing() { return isUsing; }
	bool isCanUse() { return canUse; }
	bool setCanUse() { return canUse; }

	void enableItem() { this->enable = true; }
	void disableItem() { this->enable = false; }

	GLuint getTexture() { return texture[0]; }

	unsigned short getIndex() { return index; }

	UseItem(Vector2* positionInMap);
};

