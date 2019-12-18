#include "Prison.h"

Prison::Prison(Vector2* positionInMap) : Door(positionInMap)
{
	this->tag = Tag::prison;
	this->name = "Prison";
	this->guardPosition = new Vector2(0, 0);
	this->otherGuardPosition = new Vector2(0, 0);
}

void Prison::draw2D(int width, int height)
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, texture[index]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
	glDisable(GL_BLEND);
}

void Prison::draw3D()
{
	if (open)
	{
		glEnable(GL_BLEND);
		counter++;
		if (counter == 10)
		{
			counter = 0;
			index++;
			if (index == 3)
				destroy = true;
		}
	}
	glEnable(GL_BLEND);
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

	glDisable(GL_BLEND);
}

void Prison::load(std::string jsonString)
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
