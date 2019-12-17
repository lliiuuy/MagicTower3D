#pragma once
#include "UseItem.h"
class TheOrbOfWisdom :
	public UseItem
{
private:
	int numberOfMessages = 0;
	std::vector<char*>* messages;
	int index = 0; // 当前查看对话的index
public:
	void save();
	void load();
	void useItem();

	void nextMessage() { index++; }
	void previousMessage() { index--; }

	TheOrbOfWisdom(Vector2* positionInMap);
};

