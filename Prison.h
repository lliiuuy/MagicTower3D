#pragma once
#include "Door.h"
class Prison :
	public Door
{
private:
	Vector2* guardPosition;
	Vector2* otherGuardPosition;
public:
	Prison(Vector2* positionInMap);
	void draw2D(int width, int height);
	void draw3D();

	void load(std::string jsonString);
	std::string save();

	Vector2* getGuardPosition() { return guardPosition; }
	Vector2* getOtherGuardPosition() { return otherGuardPosition; }
};

