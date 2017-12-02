#ifndef _INCLUDE_KEY_MANAGER_
#define _INCLUDE_KEY_MANAGER_

#include <DxLib.h>
#include <assert.h>

//select_keyのパラメータ
//PAD_INPUT_DOWN　	// ↓チェックマスク(下キー or テンキーの２キー)
//PAD_INPUT_LEFT　	// ←チェックマスク(左キー or テンキーの４キー)
//PAD_INPUT_RIGHT　	// →チェックマスク(右キー or テンキーの６キー)
//PAD_INPUT_UP　	// ↑チェックマスク(上キー or テンキーの８キー)
//PAD_INPUT_A　		// 1ボタンチェックマスク(Ｚキー)
//PAD_INPUT_B　		// 2ボタンチェックマスク(Ｘキー)
//PAD_INPUT_C　		// 3ボタンチェックマスク(Ｃキー)
//PAD_INPUT_X　		// 4ボタンチェックマスク(Ａキー)
//PAD_INPUT_Y　		// 5ボタンチェックマスク(Ｓキー)
//PAD_INPUT_Z　		// 6ボタンチェックマスク(Ｄキー)
//PAD_INPUT_L　		// 7ボタンチェックマスク(Ｑキー)
//PAD_INPUT_R　		// 8ボタンチェックマスク(Ｗキー)
//PAD_INPUT_START　	// 9ボタンチェックマスク(ＥＳＣキー)
//PAD_INPUT_M　		// 10ボタンチェックマスク(スペースキー)
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
	
	bool before_input;//one_before_inputの方がいいかな？
	bool now_input;
	int select_key;
};

#endif