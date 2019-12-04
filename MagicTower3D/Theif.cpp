#include "Theif.h"

Theif::Theif(Vector2* positionInMap) : NPC(positionInMap)
{
	this->tag = Tag::theif;
	this->name = "Theif";
}

void Theif::talk()
{
}
