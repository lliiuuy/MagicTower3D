#include "TheOrbOfWisdom.h"

std::string TheOrbOfWisdom::save()
{
	std::string jsonString;
	Json::Value value;
	value["index"] = this->indexOfMessages;
	value["number"] = this->messages->size();
	value["enable"] = this->enable;
	value["canUse"] = this->canUse;
	for (int i = 0; i < messages->size(); i++)
	{
		char message[1000];
		sprintf_s(message, messages->at(i));
		value["messages"][i] = message;
	}
	jsonString = value.toStyledString();
	return jsonString;
}

void TheOrbOfWisdom::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		this->indexOfMessages = data["index"].asInt();
		int numberOfMessages = data["number"].asInt();
		this->canUse = data["canUse"].asBool();
		this->enable = data["enable"].asBool();
		for (int i = 0; i < numberOfMessages; i++)
		{
			char message[1000];
			sprintf_s(message, data["messages"][i].asCString());
			this->messages->push_back(message);
		}
	}
}

TheOrbOfWisdom::TheOrbOfWisdom(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of wisdom";
	this->messages = new std::vector<char*>();
	this->index = 2;
}
