#include "Altar.h"

bool Altar::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[4];

	memset(textureImage, 0, sizeof(void*) * 4);

	char fileName[100];
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(fileName, "Data/NPC/%s/%s_%d.bmp", this->name, this->name, i + 1);

		if (textureImage[i] = loadBMP(fileName))
		{
			status = true;
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[i]->sizeX, textureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[i]->data);
		}

		if (textureImage[i])
		{
			if (textureImage[i]->data)
			{
				free(textureImage[i]->data);
			}
			free(textureImage[i]);
		}
	}

	return status;
}

void Altar::draw2D(int width, int height)
{
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, texture[index]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
	// 画神坛的左侧
	glBindTexture(GL_TEXTURE_2D, texture[2]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 48) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 48) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
	// 画神坛的右侧
	glBindTexture(GL_TEXTURE_2D, texture[3]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 48) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 48) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
}

void Altar::draw3D()
{
	counter++;
	if (counter >= 10)
	{
		index = index == 1 ? 0 : 1;
		counter = 0;
	}
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glBindTexture(GL_TEXTURE_2D, texture[index]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // 朝向正面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lx / 2, ly / 2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lx / 2, ly / 2, 0);
	glEnd();
	// 画商店的左边
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // 朝向正面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lx * 3 / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-lx / 2, ly / 2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lx * 3 / 2, ly / 2, 0);
	glEnd();
	// 画商店的右边
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // 朝向正面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lx * 3 / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lx * 3 / 2, ly / 2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(lx / 2, ly / 2, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

std::string Altar::save()
{
	std::string jsonString;
	Json::Value value;
	value["index"] = this->indexOfMessages;
	value["number"] = this->numberofMessages;
	value["health"] = this->health;
	value["attack"] = this->attack;
	value["defence"] = this->defence;
	value["cost"] = this->cost;
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

void Altar::load(std::string jsonString)
{
	Json::Value data;
	Json::Reader reader;
	if (reader.parse(jsonString, data))
	{
		this->indexOfMessages = data["index"].asInt();
		this->numberofMessages = data["number"].asInt();
		this->health = data["health"].asInt();
		this->attack = data["attack"].asInt();
		this->defence = data["defence"].asInt();
		this->cost = data["cost"].asInt();

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

Altar::Altar(Vector2* positionInMap): NPC(positionInMap)
{
	this->name = "Altar";
	this->index = 0;
	this->messages = new std::vector<Message*>();
}
