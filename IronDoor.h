#pragma once
#include "Door.h"
class IronDoor :
	public Door
{
private:
	Vector2* guardPosition;
	Vector2* otherGuardPosition;

public:
	IronDoor(Vector2* positionInMap);
	void load(std::string jsonString);

	Vector2* getGuardPosition() { return guardPosition; }
	Vector2* getOtherGuardPosition() { return otherGuardPosition; }
};

