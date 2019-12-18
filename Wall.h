#pragma once
#include "Obstacle.h"
#include "AudioManager.h"

class Wall :
	public Obstacle
{
private:
	bool loadTexture();

	bool brokenWall = false;
	bool appearWall = false;
	bool action = false;

public:
	Wall(Vector2* positionInMap);
	void display(Vector3* position);
	void collide();

	void draw2D(int width, int height);

	bool isBrokenWall() { return brokenWall; }
	bool isAppearWall() { return appearWall; }

	void setBrokenWall() { brokenWall = true; this->index = 0; }
	void setAppearWall() { appearWall = true; this->position->y -= ly; this->index = 3; }
};

