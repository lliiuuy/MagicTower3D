#include "TheOrbOfTheHero.h"

std::string TheOrbOfTheHero::save()
{
	std::string jsonString;
	Json::Value value;
	value["enable"] = this->enable;
	value["canUse"] = this->canUse;
	jsonString = value.toStyledString();
	return jsonString;
}

void TheOrbOfTheHero::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		this->canUse = data["canUse"].asBool();
		this->enable = data["enable"].asBool();
	}
}

TheOrbOfTheHero::TheOrbOfTheHero(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of the hero";
	this->index = 0;
}
