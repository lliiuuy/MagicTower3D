#include "Thief.h"

Thief::Thief(Vector2* positionInMap): NPC(positionInMap)
{
	this->name = "Thief";
}

std::string Thief::save()
{
	std::string jsonString;
	Json::Value value;
	value["index"] = this->indexOfMessages;
	value["number"] = this->numberofMessages;
	for (int i = 0; i < numberofMessages; i++)
	{
		value["messages"][i]["sentence"] = messages->at(i)->getSentence();
		value["messages"][i]["messsage"] = messages->at(i)->getMessage();
		value["messages"][i]["toNote"] = messages->at(i)->isToNote();
		value["messages"][i]["choose"] = messages->at(i)->isChoose();
		value["messages"][i]["action"] = messages->at(i)->isAction();
	}
	value["floor"] = this->floorNumber;
	value["brokenWall"]["x"] = brokenWallPosition->x;
	value["brokenWall"]["y"] = brokenWallPosition->y;
	jsonString = value.toStyledString();
	return jsonString;
}

void Thief::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		this->indexOfMessages = data["index"].asInt();
		this->numberofMessages = data["number"].asInt();
		Message* message;
		for (int i = 0; i < numberofMessages; i++)
		{
			if (data["messages"][i]["message"].isNull())
				message = new Message(data["messages"][i]["sentence"].asCString(), "", data["messages"][i]["choose"].asBool(), data["messages"][i]["toNote"].asBool(), data["messages"][i]["action"].asBool());
			else
				message = new Message(data["messages"][i]["sentence"].asCString(), data["messages"][i]["message"].asCString(), data["messages"][i]["choose"].asBool(), data["messages"][i]["toNote"].asBool(), data["messages"][i]["action"].asBool());
			messages->push_back(message);
		}
		this->floorNumber = data["floor"].asInt();
		this->brokenWallPosition = new Vector2((float)data["brokenWall"][(Json::UInt)0]["x"].asDouble(), (float)data["brokenWall"][(Json::UInt)0]["y"].asDouble());
	}
}

void Thief::display(Vector3* position)
{
	if (this->moving)
	{
		if (fabs(positionInMap->x - node[indexOfMove]->x) < moveSpeed && fabs(positionInMap->y - node[indexOfMove]->y) < moveSpeed)
		{
			this->indexOfMove++;
			if (this->indexOfMove == this->numberOfNode)
			{
				this->moving = false;
				this->dir->x = 0;
				this->dir->y = 0;
				this->positionInMap->x = node[indexOfMove - 1]->x;
				this->positionInMap->y = node[indexOfMove - 1]->y;
				if (floorNumber == 2 && (int)floor(positionInMap->x + 0.5f) == 9)
				{
					AudioManager::playSound("Data/Audio/get.wav");
					this->destroy = true;
				}
			}
		}
		else
		{
			this->dir->x = 0;
			this->dir->y = 0;
			if (positionInMap->x < node[indexOfMove]->x)
				this->dir->x = 1;
			else if (positionInMap->x > node[indexOfMove]->x)
				this->dir->x = -1;
			if (positionInMap->y < node[indexOfMove]->y)
				this->dir->y = 1;
			else if (positionInMap->y > node[indexOfMove]->y)
				this->dir->y = -1;
		}
		this->positionInMap->x += moveSpeed * dir->x;
		this->positionInMap->y += moveSpeed * dir->y;
		this->position->x = this->positionInMap->y * lx;
		this->position->z = this->positionInMap->x * lz;
	}
	// 经过测试没问题
	Vector3* direction = new Vector3(position->x - this->position->x, position->y - this->position->y, position->z - this->position->z);
	if (direction->x < 0)
		spinY = -acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->z, 2))) * 180 / (float)M_PI;
	else
		spinY = acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->z, 2))) * 180 / (float)M_PI;

}
