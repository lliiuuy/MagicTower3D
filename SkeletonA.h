#pragma once
#include "Boss.h"
class SkeletonA :
	public Boss
{
public:
	void display(Vector3 *position);

	SkeletonA(Vector2* positionInMap);
	void load(std::string jsonString);
	std::string save();
	void nextSentence() 
	{
		if (indexOfMessages + 1 >= numberofMessages)
		{
			talking = false;
			indexOfMessages++;
		}
		else if (indexOfMessages == 0)
		{
			talking = false;
			indexOfMessages++;
		}
		else if (indexOfMessages == 1)
		{
			talking = false;
			indexOfMessages++;
		}
		else
			indexOfMessages++;
	}

	void draw2D(int width, int height);
};

