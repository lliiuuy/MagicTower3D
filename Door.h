#pragma once
#include "Object.h"
class Door :
	public Object
{
private:
	bool loadTexture();

public:
	void draw();
	void open(); // ����
	void collide();

	Door(Vector2* positionInMap);
};

