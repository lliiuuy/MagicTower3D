#include "SkeletonA.h"

void SkeletonA::display(Vector3* position)
{
	if (this->moving)
	{
		if (fabs(positionInMap->x - node[indexOfMove]->x) < moveSpeed && fabs(positionInMap->y - node[indexOfMove]->y) < moveSpeed)
		{
			this->indexOfMove++;
			if (this->indexOfMove == this->numberOfNode)
			{
				this->dir->x = 0;
				this->dir->y = 0;
				this->positionInMap->x = node[indexOfMove - 1]->x;
				this->positionInMap->y = node[indexOfMove - 1]->y;
				this->moving = false;
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

	if (this->appearMonster)
	{
		if (appear)
		{
			counterOfAppear++;
			if (counterOfAppear == 40)
			{
				appear = false;
				appearMonster = false;
			}
			this->position->y += ly / 40;
		}
	}

	if (this->health == 0)
	{
		if (indexOfMessages + 1 > numberofMessages)
			destroyThis();
	}

	// 经过测试没问题
	Vector3* direction = new Vector3(position->x - this->position->x, position->y - this->position->y, position->z - this->position->z);
	if (direction->x < 0)
		spinY = -acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->z, 2))) * 180 / (float)M_PI;
	else
		spinY = acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->z, 2))) * 180 / (float)M_PI;

}

SkeletonA::SkeletonA(Vector2* positionInMap): Boss(positionInMap)
{
	this->name = "SkeletonA";
	this->health = 100;
	this->attack = 65;
	this->defence = 15;
	this->money = 30;
}

void SkeletonA::draw2D(int width, int height)
{
	if (!appearMonster && this->health > 0)
	{
		glEnable(GL_TEXTURE_2D); // 开启2D纹理
		glBindTexture(GL_TEXTURE_2D, texture[index]);		// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
		glEnd();
	}
}

void SkeletonA::load(std::string jsonString)
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
	}
}

std::string SkeletonA::save()
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
	jsonString = value.toStyledString();
	return jsonString;
}
