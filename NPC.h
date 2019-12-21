#pragma once
#include "Object.h"
#include "Message.h"

class NPC :
	public Object
{
protected:
	std::vector<Message*> *messages; // ������ĶԻ�

	unsigned short numberofMessages = 0; // ��¼һ���м����Ի�
	unsigned short indexOfMessages = 0; // ��¼�Ի����е��ڼ���
	unsigned short index = 0; // ��¼���صڼ���texture

	float spinY = 0; // NPC��ת�ĽǶ�

	virtual void talk() = 0; // ������Ի�

	bool loadTexture();

	bool talking = false;
	bool endTalking = false;

	char endSentence[100] = "";

public:
	void collide();
	void draw3D();
	void draw2D(int width, int height);
	void display(Vector3* position); // NPC���������ת

	virtual std::string save() = 0;
	virtual void load(std::string jsonString) = 0;

	virtual void nextSentence() 
	{
		if (indexOfMessages + 1 >= numberofMessages)
		{
			talking = false;
			endTalking = true;
		}
		else
			indexOfMessages++;
	}

	char* getEndSentence() { return endSentence; }

	virtual char* getSentence() { return messages->at(indexOfMessages)->getSentence(); }
	char* getMessage() { return messages->at(indexOfMessages)->getMessage(); }
	bool isChoose() { return messages->at(indexOfMessages)->isChoose(); }
	bool isAction() { return messages->at(indexOfMessages)->isAction(); }
	bool isToNote() { return messages->at(indexOfMessages)->isToNote(); }
	bool isEndTalking() { return endTalking; }
	bool isTalking() { return talking; }

	NPC(Vector2* positionInMap);
};

