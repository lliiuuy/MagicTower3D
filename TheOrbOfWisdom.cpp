#include "TheOrbOfWisdom.h"

std::string TheOrbOfWisdom::save()
{
	std::string jsonString;
	Json::Value value;
	value["index"] = this->indexOfMessages;
	value["number"] = this->messages->size();
	value["enable"] = this->enable;
	for (int i = 0; i < (int)messages->size(); i++)
	{
		char message[1000];
		sprintf_s(message, messages->at(i)->getSentence());
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
		this->enable = data["enable"].asBool();
		for (int i = 0; i < numberOfMessages; i++)
		{
			char sentence[1000] = "";
			sprintf_s(sentence, data["messages"][i].asCString());
			Message* message = new Message(sentence, "", false, false, false);
			this->messages->push_back(message);
		}
	}
}

void TheOrbOfWisdom::addMessage(char* message)
{
	bool add = true;
	for (unsigned int i = 0; i < this->messages->size(); i++)
	{
		if (strcmp(message, this->messages->at(i)->getSentence()) == 0)
			add = false;
	}
	if (add)
	{
		Message* messageClass = new Message(message, "", false, false, false);
		messages->push_back(messageClass);
	}
}

TheOrbOfWisdom::TheOrbOfWisdom(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of wisdom";
	this->messages = new std::vector<Message*>();
	this->index = 1;
}
