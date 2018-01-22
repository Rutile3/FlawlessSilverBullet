#ifndef _GAME_SOUND_MANAGER_
#define _GAME_SOUND_MANAGER_

#include "SoundManager.h"

enum {
	DAMAGE,
	ENTER,
	EXPLOSION1,
	REFLECTION,

	BGM01,

	MAX_SOUND_SIZE
};

class soundsManager {
public:
	soundsManager();
	~soundsManager();

	void Play(const int file_name);
	void Stop(const int file_name);

private:
	soundManager* sound[MAX_SOUND_SIZE];
};

extern soundsManager* sound;

#endif