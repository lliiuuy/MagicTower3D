#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class AudioManager
{
public:
	static void playSound(char* fileName);
	AudioManager();
};

