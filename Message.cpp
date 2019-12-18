#include "Message.h"

Message::Message(const char* sentence, const char* message, bool choose, bool toNote, bool action)
{
	sprintf_s(this->sentence, sentence);
	sprintf_s(this->message, message);
	this->choose = choose;
	this->toNote = toNote;
	this->action = action;
}