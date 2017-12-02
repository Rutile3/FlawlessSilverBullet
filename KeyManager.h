#ifndef _INCLUDE_KEY_MANAGER_
#define _INCLUDE_KEY_MANAGER_

#include <DxLib.h>
#include <assert.h>

//select_key�̃p�����[�^
//PAD_INPUT_DOWN�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂Q�L�[)
//PAD_INPUT_LEFT�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂S�L�[)
//PAD_INPUT_RIGHT�@	// ���`�F�b�N�}�X�N(�E�L�[ or �e���L�[�̂U�L�[)
//PAD_INPUT_UP�@	// ���`�F�b�N�}�X�N(��L�[ or �e���L�[�̂W�L�[)
//PAD_INPUT_A�@		// 1�{�^���`�F�b�N�}�X�N(�y�L�[)
//PAD_INPUT_B�@		// 2�{�^���`�F�b�N�}�X�N(�w�L�[)
//PAD_INPUT_C�@		// 3�{�^���`�F�b�N�}�X�N(�b�L�[)
//PAD_INPUT_X�@		// 4�{�^���`�F�b�N�}�X�N(�`�L�[)
//PAD_INPUT_Y�@		// 5�{�^���`�F�b�N�}�X�N(�r�L�[)
//PAD_INPUT_Z�@		// 6�{�^���`�F�b�N�}�X�N(�c�L�[)
//PAD_INPUT_L�@		// 7�{�^���`�F�b�N�}�X�N(�p�L�[)
//PAD_INPUT_R�@		// 8�{�^���`�F�b�N�}�X�N(�v�L�[)
//PAD_INPUT_START�@	// 9�{�^���`�F�b�N�}�X�N(�d�r�b�L�[)
//PAD_INPUT_M�@		// 10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)
class keyManager{
public:
	keyManager(int select_key);
	~keyManager();
	bool Free();
	bool Keep();
	bool Push();
	bool State();
	void Update();

private:
	bool Judge(bool before_input, bool now_input);
	
	bool before_input;//one_before_input�̕����������ȁH
	bool now_input;
	int select_key;
};

#endif