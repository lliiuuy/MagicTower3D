#include "OldMan.h"

OldMan::OldMan(Vector2* positionInMap): NPC(positionInMap)
{
	this->name = "Old Man";
	sprintf_s(this->endSentence, "I have done what I can. Good luck!");
}

void OldMan::talk()
{
	this->talking = true;
}

std::string OldMan::save()
{
	std::string jsonString;
	return jsonString;
}

void OldMan::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data)) 
	{
		this->indexOfMessages = data["index"].asInt();
		this->numberofMessages = data["number"].asInt();
		this->indexOfUseItems = data["indexOfUseItem"].asInt();
		this->endTalking = data["endTalking"].asBool();
		Message* message;
		for (int i = 0; i < numberofMessages; i++)
		{
			if (data["messages"][i]["message"].isNull())
				message = new Message(data["messages"][i]["sentence"].asCString(), "", data["messages"][i]["choose"].asBool(), data["messages"][i]["toNote"].asBool(), data["messages"][i]["action"].asBool());
			else
				message = new Message(data["messages"][i]["sentence"].asCString(), data["messages"][i]["message"].asCString(), data["messages"][i]["choose"].asBool(), data["messages"][i]["toNote"].asBool(), data["messages"][i]["action"].asBool());
			messages->push_back(message);
		}
	}
}
