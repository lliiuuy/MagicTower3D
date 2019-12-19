#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
protected: 
	float spinY = 0;

	void display(Vector3* position); // 朝着人物所在方向旋转

	bool loadTexture(); // 怪物固定是两帧

	bool moving = false;
	Vector2** node = NULL;
	int numberOfNode = 0;

	Vector2* dir = new Vector2(0, 0);

public:
	Monster(Vector2* positionInMap);
	void collide();
	void draw2D(int width, int height);
	void draw3D();
	void receiveDamage(unsigned int damage);

	void move(Vector2** node, unsigned short numberOfNode) { moving = true, this->node = node, this->numberOfNode = numberOfNode; };

	GLuint getTexture() { return texture[0]; }
};

