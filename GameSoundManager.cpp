#include "GameSoundManager.h"

soundsManager::soundsManager() {
	sound[DAMAGE] = new soundManager("media/Sound/Damage.mp3"); 
	sound[ENTER] = new soundManager("media/Sound/Enter.mp3");
	sound[EXPLOSION1] = new soundManager("media/Sound/Explosion1.mp3");
	sound[REFLECTION] = new soundManager("media/Sound/Reflection.mp3");
	sound[BGM01] = new soundManager("media/Sound/Stage1.mp3", false);
}

soundsManager::~soundsManager() {
	delete[] sound;
}

void soundsManager::Play(const int file_name) {
	sound[file_name]->Play();
}
void soundsManager::Stop(const int file_name) {

	sound[file_name]->Stop();
}