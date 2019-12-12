#pragma once
#include "Obstacle.h"
class Door :
	public Obstacle
{
private:
	bool loadTexture();

public:
	void draw();
	void open(); // ©╙це
	void collide();

	Door(Vector2* positionInMap);
};

