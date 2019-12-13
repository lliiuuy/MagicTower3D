#pragma once
enum class Tag : unsigned short
{
	object,
	wall,
	floor,
	door,
	ironDoor,
	prison,
	consumbleItem,
	sword,
	shield,
	useItem,
	monster,
	magician,
	NPC,
};

enum class PlayerStatus : unsigned short
{
	moving,
	spining,
	battling,
	idle,
};