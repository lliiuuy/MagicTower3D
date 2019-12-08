#include "Player.h"

void Player::move(Vector2* direction)
{
}

void Player::reciveItems(ConsumbleItem* consumbleItem)
{
	if (consumbleItem->getTag() == Tag::sword)
		this->sword = (Sword*)consumbleItem;
	else if (consumbleItem->getTag() == Tag::shield)
		this->shield = (Shield*)consumbleItem;
	// 将消耗物品的属性加到人物身上
	this->health += consumbleItem->getHealth();
	this->attack += consumbleItem->getAttack();
	this->defence += consumbleItem->getDefence();
	this->yellowKeyNumber += consumbleItem->getYellowKeyNumber();
	this->blueKeyNumber += consumbleItem->getBlueKeyNumber();
	this->redKeyNumber += consumbleItem->getRedKeyNumber();

	// 更新UI界面
	// UIManager.update();
}

void Player::reciveUseItems(UseItem* useItem)
{
	// 将UI界面上的UseItem图标激活
	// unsigned short index = useItem->get
	// UIManager.enableUseItem(index)
	// UIManager.update();
	// 将物体插入指定位置
	// useItems->insert(index, useItem);
}

Player::Player(Vector2* positionInMap): Creature(positionInMap)
{
	yellowKeyNumber = 0;
	blueKeyNumber = 0;
	redKeyNumber = 0;
	moveSpeed = 0.0f;
	positionNow = position;
	shield = NULL;
	sword = NULL;
	spin = new Vector3(0, 0, 0);
	spinSpeed = 0.0f;
	useItems = new std::vector<UseItem*>();
}
