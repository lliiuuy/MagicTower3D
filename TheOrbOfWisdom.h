#pragma once
#include "Message.h"
#include "UseItem.h"

class TheOrbOfWisdom :
	public UseItem
{
private:
	std::vector<Message*>* messages;
	int indexOfMessages = 0; // 当前查看对话的index
public:

	std::string save();
	void load(std::string jsonString);

	void useItem() { this->isUsing = true;}
	void closeItem() { this->isUsing = false; }

	void nextMessage() 
	{ 
		if(indexOfMessages < (int)messages->size() - 1)
			indexOfMessages++; 
	}
	void previousMessage() 
	{ 
		if(indexOfMessages > 0)
			indexOfMessages--; 
	}

	char* getMessage() 
	{ 
		if (messages->size() > 0)
			return this->messages->at(this->indexOfMessages)->getSentence();
		else
			return NULL;
	}
	void addMessage(char* message);

	TheOrbOfWisdom(Vector2* positionInMap);
};

