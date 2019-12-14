#pragma once
#include "Obstacle.h"
class Door :
	public Obstacle
{
private:
	bool loadTexture();
	float move;
	float spinY;

public:
	void open(); // ©╙це
	void collide();
	void draw3D();
	void lookAt(Vector3* position);

	Door(Vector2* positionInMap);
};

