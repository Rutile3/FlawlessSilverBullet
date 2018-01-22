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
	//‚·‚Å‚ÉÄ¶‚³‚ê‚Ä‚¢‚½‚ç~‚ß‚é
	if (CheckSoundMem(handle) == TRUE)
		StopSoundMem(handle);

	//‚â‚â‚±‚µ‚¢‚±‚Æ‚µ‚Ä‚é‚¯‚ÇŒ³‚Ì^—’l‚ÆˆÓ–¡‡‚¢‚Íˆê
	//‚ ‚ÆSE‚Íˆê’â~‚Å‚à‚Æ‚ß‚È‚¢‚Ì‚Å•K‚¸Å‰‚©‚çÄ¶‚·‚é
	PlaySoundMem(handle, this_handle_se == true ? DX_PLAYTYPE_BACK : DX_PLAYTYPE_LOOP, this_handle_se);

	return;
}

void soundManager::Stop(){
	StopSoundMem(handle);
}