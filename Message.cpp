#include "Message.h"

Message::Message(char* message, bool choose, bool toNote)
{
	this->message = message;
	this->choose = choose;
	this->toNote = toNote;
}