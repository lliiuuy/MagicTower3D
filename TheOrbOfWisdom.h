#pragma once
#include "UseItem.h"
class TheOrbOfWisdom :
	public UseItem
{
private:
	std::vector<char*>* messages;
	int indexOfMessages = 0; // 当前查看对话的index
public:

	std::string save();
	void load(std::string jsonString);

	void useItem() { this->isUsing = true;}
	void closeItem() { this->isUsing = true; }

	void nextMessage() 
	{ 
		if(indexOfMessages < messages->size() - 1)
			indexOfMessages++; 
	}
	void previousMessage() 
	{ 
		if(indexOfMessages > 0)
			indexOfMessages--; 
	}

	char* getMessage() { return this->messages->at(this->indexOfMessages); }

	TheOrbOfWisdom(Vector2* positionInMap);
};

