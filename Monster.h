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
	unsigned short numberOfNode = 0;
	unsigned short indexOfMove = 0;

	float moveSpeed = 0.05f;

	int counterOfAppear = 0;

	bool appearMonster = false;
	bool appear = false;

	Vector2* dir = new Vector2(0, 0);

public:
	Monster(Vector2* positionInMap);
	void collide();
	void draw2D(int width, int height);
	void draw3D();
	void receiveDamage(unsigned int damage);

	void setAppear() 
	{
		this->appearMonster = true; 
		this->position->y -= ly;
	}

	void toAppear()
	{
		appear = true;
		counterOfAppear = 0;
	}

	bool isAppearMonster() { return this->appearMonster; }

	void move(Vector2** node, unsigned short numberOfNode) 
	{
		moving = true, this->node = node, this->numberOfNode = numberOfNode;
		this->dir->x = 0;
		this->dir->y = 0;
		if ((int)floor(positionInMap->x + 0.5f) < (int)floor(node[indexOfMove]->x + 0.5f))
			this->dir->x = 1;
		else if ((int)floor(positionInMap->x + 0.5f) > (int)floor(node[indexOfMove]->x + 0.5f))
			this->dir->x = -1;
		if ((int)floor(positionInMap->y + 0.5f) < (int)floor(node[indexOfMove]->y + 0.5f))
			this->dir->y = 1;
		else if ((int)floor(positionInMap->y + 0.5f) > (int)floor(node[indexOfMove]->y + 0.5f))
			this->dir->y = -1;
	};

	GLuint getTexture() { return texture[0]; }
};

