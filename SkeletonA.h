#pragma once
#include "Boss.h"
class SkeletonA :
	public Boss
{
public:
	SkeletonA(Vector2* positionInMap);
	void load(std::string jsonString);
	std::string save();
	void nextSentence() 
	{
		if (indexOfMessages + 1 >= numberofMessages)
			talking = false;
		else
			indexOfMessages++;
	}
};

