#pragma once
class GameManager
{
private:
	static GameManager* instance;
	GameManager();
public:
	static GameManager* getInstance() { return instance; }
};

