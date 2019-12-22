#pragma once
#include "NPC.h"
#include "AudioManager.h"

class Thief :
	public NPC
{
private:
	float moveSpeed = 0.05f;
	Vector2* dir = new Vector2(0, 0);
	
	unsigned short indexOfMove = 0;
	unsigned short numberOfNode = 0;
	Vector2** node = NULL;

	Vector2* brokenWallPosition = new Vector2(0, 0);

	bool moving = false;

	unsigned short floorNumber = 2;

	void talk() { this->talking = true; }

public:
	Thief(Vector2* positionInMap);
	std::string save();
	void load(std::string jsonString);

	void move(Vector2** node, unsigned short numberOfNode)
	{
		indexOfMove = 0;
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
	}

	bool isMoving() { return this->moving; }
	void display(Vector3* position);

	void nextSentence()
	{
		if (floorNumber == 2)
		{
			if (indexOfMessages == 4)
			{
				talking = false;
				indexOfMessages++;
				Vector2** nodes = new Vector2 * [2]();
				nodes[0] = new Vector2(6, 0);
				nodes[1] = new Vector2(7, 0);
				move(nodes, 2);
			}
			else if (indexOfMessages + 1 >= numberofMessages)
			{
				talking = false;
				Vector2** nodes = new Vector2 * [1]();
				nodes[0] = new Vector2(9, 0);
				move(nodes, 1);
			}
			else
				indexOfMessages++;
		}
	}

	Vector2* getBrokenWallPosition() { return this->brokenWallPosition; }

	unsigned short getIndexOfMessage() { return this->indexOfMessages; }
	unsigned short getFloor() { return this->floorNumber; }
};

