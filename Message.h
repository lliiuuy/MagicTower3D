#pragma once
#include<stdio.h>

class Message
{
private:
	char sentence[1000] = "";
	char message[1000] = "";
	bool choose;
	bool toNote;
	bool action;
public:
	Message(const char* sentence, const char* message, bool choose, bool toNote, bool action);
	char* getSentence() { return sentence; }
	char* getMessage() { return message; }
	bool isChoose() { return choose; }
	bool isToNote() { return toNote; }
	bool isAction() { return action; }
};

