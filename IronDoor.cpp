#include "IronDoor.h"

IronDoor::IronDoor(Vector2* positionInMap): Door(positionInMap)
{
	this->tag = Tag::ironDoor;
	this->name = "Iron Door";
	this->guardPosition = new Vector2(0, 0);
	this->otherGuardPosition = new Vector2(0, 0);
}

void IronDoor::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		guardPosition->x = (float)data["position"][(Json::UInt)0]["x"].asDouble();
		guardPosition->y = (float)data["position"][(Json::UInt)0]["y"].asDouble();
		otherGuardPosition->x = (float)data["position"][(Json::UInt)1]["x"].asDouble();
		otherGuardPosition->y = (float)data["position"][(Json::UInt)1]["y"].asDouble();
	}
}
