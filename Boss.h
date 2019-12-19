#pragma once
#include "Monster.h"
#include "Message.h"

class Boss :
	public Monster
{
private:
	std::vector<Message*>* messages;

	unsigned short numberofMessages = 0; // 记录一共有几条对话
	unsigned short indexOfMessages = 0; // 记录对话进行到第几句

	bool talking = false;

public:
	virtual void nextSentence();
	char* getSentence() { return messages->at(indexOfMessages)->getSentence(); }
	char* getMessage() { return messages->at(indexOfMessages)->getMessage(); }
	bool isChoose() { return messages->at(indexOfMessages)->isChoose(); }
	bool isAction() { return messages->at(indexOfMessages)->isAction(); }
	bool isTalking() { return talking; }

	void talk() { this->talking = true; }

	Boss(Vector2* positionInMap);
	void load(std::string jsonString);
};

