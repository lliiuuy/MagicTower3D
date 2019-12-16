#pragma once
#include "Obstacle.h"
class Door :
	public Obstacle
{
protected:
	bool loadTexture();
	float spinY;
	bool open;

public:
	void openDoor(); // ¿ªÃÅ
	void collide();
	void draw3D();
	void draw2D(int width, int height);
	void display(Vector3* position);

	bool isOpen() { return open; }

	Door(Vector2* positionInMap);
};

