#pragma once
#include "Object.h"
class Door :
	public Object
{
private:
	bool loadTexture();

public:
	void draw();
	void open(); // ©╙це
	void collide();

	bool init();

	Door(Vector2* positionInMap);
};

