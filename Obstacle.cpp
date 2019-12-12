#include "Obstacle.h"

void Obstacle::draw2D()
{
}

void Obstacle::draw3D()
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	// »­ÕýÃæ
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
	// »­±³Ãæ
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
	// »­¶¥Ãæ
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
	// »­µ×Ãæ
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
	// »­ÓÒ²àÃæ
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
	// »­×ó²àÃæ
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));

	glEnd();
	glPopMatrix();
}

Obstacle::Obstacle(Vector2* positionInMap) : Object(positionInMap)
{
}
