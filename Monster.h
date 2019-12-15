#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
protected: 
	float spinY = 0;

	void lookAt(Vector3* position); // 朝着人物所在方向旋转

	bool loadTexture(); // 怪物固定是两帧

public:
	Monster(Vector2* positionInMap);
	void collide();
	void draw2D(int width, int height);
	void draw3D();

	GLuint getTexture() { return texture[0]; }
};

