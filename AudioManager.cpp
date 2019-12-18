#include "AudioManager.h"

void AudioManager::playSound(char* fileName)
{
	PlaySound(TEXT(fileName), NULL, SND_FILENAME | SND_ASYNC);
}

AudioManager::AudioManager()
{
}
