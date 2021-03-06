#pragma once
enum class Tag : unsigned short
{
	object,
	wall,
	floor,
	door,
	ironDoor,
	prison,
	downStairs,
	upStairs,
	consumbleItem,
	sword,
	shield,
	useItem,
	monster,
	magician,
	boss,
	NPC,
};

enum class PlayerStatus : unsigned short
{
	moving,
	usingStairs,
	spining,
	battling,
	talking,
	animating,
	usingItem,
	idle,
};