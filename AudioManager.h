#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class AudioManager
{
public:
	void playSound(char* fileName);
	void playSoundLoop(char* fileName);
	void stop();
	AudioManager();
};

