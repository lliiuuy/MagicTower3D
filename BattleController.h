#pragma once

#include "Monster.h"
#include "Player.h"

class BattleController
{
private:
	static BattleController* instance;
	BattleController();
public:
	static void battle(Monster* monster); // Õ½¶·¿ØÖÆ
	static BattleController* getInstance() { return instance; }
};

