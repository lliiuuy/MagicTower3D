#include "TheOrbOfFlying.h"

void TheOrbOfFlying::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		this->canUse = data["canUse"].asBool();
		this->enable = data["enable"].asBool();
		this->maxFloor = data["floor"].asInt();
	}
}

std::string TheOrbOfFlying::save()
{
	std::string jsonString;
	Json::Value value;
	value["enable"] = this->enable;
	value["canUse"] = this->canUse;
	value["floor"] = this->maxFloor;
	jsonString = value.toStyledString();
	return jsonString;
}

TheOrbOfFlying::TheOrbOfFlying(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of flying";
	this->index = 1;
}
