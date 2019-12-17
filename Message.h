#pragma once
class Message
{
private:
	char* message;
	bool choose;
	bool toNote;
public:
	Message(char* message, bool choose, bool toNote);
	char* getMessage() { return message; }
	bool isChoose() { return choose; }
	bool isToNote() { return toNote; }
};

