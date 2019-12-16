#include "AudioManager.h"

void AudioManager::playSound(char* fileName)
{
	PlaySound(TEXT(fileName), NULL, SND_FILENAME | SND_ASYNC);
}

void AudioManager::playSoundLoop(char* fileName)
{
	PlaySound(TEXT(fileName), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void AudioManager::stop()
{
	PlaySound(NULL, NULL, SND_FILENAME);
}


AudioManager::AudioManager()
{
}
