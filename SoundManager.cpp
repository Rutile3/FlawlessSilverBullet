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
	//���łɍĐ�����Ă�����~�߂�
	if (CheckSoundMem(handle) == TRUE)
		StopSoundMem(handle);

	//��₱�������Ƃ��Ă邯�ǌ��̐^���l�ƈӖ������͈ꏏ
	//����SE�͈ꎞ��~�ł��Ƃ߂Ȃ��̂ŕK���ŏ�����Đ�����
	PlaySoundMem(handle, this_handle_se == true ? DX_PLAYTYPE_BACK : DX_PLAYTYPE_LOOP, this_handle_se);

	return;
}

void soundManager::Stop(){
	StopSoundMem(handle);
}