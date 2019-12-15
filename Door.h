#pragma once
#include "Obstacle.h"
class Door :
	public Obstacle
{
private:
	bool loadTexture();
	float move;
	float spinY;
	bool open;

public:
	void openDoor(); // ©╙це
	void collide();
	void draw3D();
	void draw2D(int width, int height);
	void lookAt(Vector3* position);

	Door(Vector2* positionInMap);
};

