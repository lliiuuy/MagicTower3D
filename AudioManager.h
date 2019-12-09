#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class AudioManager
{
private:
	static AudioManager* instance;
	AudioManager();
public:
	static AudioManager* getInstance() { return instance; }
	static void playSound(char* fileName);
};

