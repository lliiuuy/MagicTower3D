#pragma once
class Message
{
private:
	char* message;
	bool action;
public:
	Message(char* message, bool action);
	char* getMessage() { return message; }
	bool getAction() { return action; }
};

