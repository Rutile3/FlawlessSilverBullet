#include "SoundManager.h"

soundManager::soundManager(const char* file_name, const bool this_handle_se){
	handle = LoadSoundMem(file_name);
	this->this_handle_se = this_handle_se;

	assert(handle != -1);
}

soundManager::~soundManager(){
	DeleteSoundMem(handle);
}

void soundManager::Play(){
	//すでに再生されていたら止める
	if (CheckSoundMem(handle) == TRUE)
		StopSoundMem(handle);

	//ややこしいことしてるけど元の真理値と意味合いは一緒
	//あとSEは一時停止でもとめないので必ず最初から再生する
	PlaySoundMem(handle, this_handle_se == true ? DX_PLAYTYPE_BACK : DX_PLAYTYPE_LOOP, this_handle_se);

	return;
}

void soundManager::Stop(){
	StopSoundMem(handle);
}