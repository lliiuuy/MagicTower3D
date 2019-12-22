#include "IronDoor.h"

IronDoor::IronDoor(Vector2* positionInMap): Door(positionInMap)
{
	this->tag = Tag::ironDoor;
	this->name = "Iron Door";
	this->guardPosition = new Vector2(0, 0);
	this->otherGuardPosition = new Vector2(0, 0);
}

void IronDoor::openDoor(bool destroy)
{
	this->toDestroy = destroy;
	AudioManager::playSound("Data/Audio/open.wav");
	this->open = true;
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

std::string IronDoor::save()
{
	std::string jsonString;
	Json::Value value;
	value["position"][(Json::UInt)0]["x"] = guardPosition->x;
	value["position"][(Json::UInt)0]["y"] = guardPosition->y;
	value["position"][(Json::UInt)1]["x"] = otherGuardPosition->x;
	value["position"][(Json::UInt)1]["y"] = otherGuardPosition->y;
	jsonString = value.toStyledString();
	return jsonString;
}

void IronDoor::draw2D(int width, int height)
{
	if (!close || open)
	{
		if (open)
			glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D); // 开启2D纹理
		glBindTexture(GL_TEXTURE_2D, texture[index]);		// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
		glEnd();
		if (open)
			glDisable(GL_BLEND);
	}
}

void IronDoor::draw3D()
{
	if (open)
	{
		glEnable(GL_BLEND);
		counter++;
		if (counter == 10)
		{
			if (!close)
			{
				counter = 0;
				index++;
				if (index == 3)
				{
					if (toDestroy)
						destroy = true;
					setClose(true);
					open = false;
				}
			}
			else
			{
				counter = 0;
				index--;
				if (index == 0)
				{
					close = false;
					open = false;
				}
			}
		}
	}

	if (!close || open)
	{
		glPushMatrix();
		glTranslatef(position->x, position->y, position->z);
		glRotatef(spinY, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, texture[index]);
		glBegin(GL_QUADS);
		// 画正面
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
		glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
		glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
		// 画背面
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));
		glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
		glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
		glEnd();
		glPopMatrix();
	}

	if (open)
		glDisable(GL_BLEND);
}
