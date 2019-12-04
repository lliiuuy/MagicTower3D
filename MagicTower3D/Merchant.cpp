#include "Merchant.h"

Merchant::Merchant(Vector2* positionInMap): NPC(positionInMap)
{
	this->tag = Tag::merchant;
	this->name = "Merchant";
}
