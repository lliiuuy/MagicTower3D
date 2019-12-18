#include "Merchant.h"

Merchant::Merchant(Vector2* positionInMap): NPC(positionInMap)
{
	this->name = "Merchant";
	sprintf_s(this->endSentence, "Be careful. I have noting more to say.");
}

std::string Merchant::save()
{
	std::string jsonString;
	return jsonString;
}

void Merchant::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		this->indexOfMessages = data["index"].asInt();
		this->numberofMessages = data["number"].asInt();
		this->yellowKeyNumber = data["yellowKeyNumber"].asInt();
		this->blueKeyNumber = data["blueKeyNumber"].asInt();
		this->redKeyNumber = data["redKeyNumber"].asInt();
		this->endTalking = data["endTalking"].asBool();
		Message* message;
		for (int i = 0; i < numberofMessages; i++)
		{
			if(data["messages"][i]["message"].isNull())
				message = new Message(data["messages"][i]["sentence"].asCString(), "", data["messages"][i]["choose"].asBool(), data["messages"][i]["toNote"].asBool(), data["messages"][i]["action"].asBool());
			else
				message = new Message(data["messages"][i]["sentence"].asCString(), data["messages"][i]["message"].asCString(), data["messages"][i]["choose"].asBool(), data["messages"][i]["toNote"].asBool(), data["messages"][i]["action"].asBool());
			messages->push_back(message);
		}
	}
}
