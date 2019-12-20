#pragma once
#include "Monster.h"
#include "Message.h"

class Boss :
	public Monster
{
protected:
	std::vector<Message*>* messages;

	unsigned short numberofMessages = 0; // ��¼һ���м����Ի�
	unsigned short indexOfMessages = 0; // ��¼�Ի����е��ڼ���

	bool talking = false;

public:
	virtual void nextSentence() = 0;
	char* getSentence() { return messages->at(indexOfMessages)->getSentence(); }
	char* getMessage() { return messages->at(indexOfMessages)->getMessage(); }
	bool isChoose() { return messages->at(indexOfMessages)->isChoose(); }
	bool isAction() { return messages->at(indexOfMessages)->isAction(); }
	bool isTalking() { return talking; }

	unsigned short getIndexOfMessage() { return this->indexOfMessages; }

	void talk() { this->talking = true; }

	Boss(Vector2* positionInMap);
	virtual void load(std::string jsonString) = 0;
	virtual std::string save() = 0;
};

