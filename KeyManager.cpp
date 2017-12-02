#include "KeyManager.h"

keyManager::keyManager(int select_key){
	before_input = false;
	this->select_key = select_key;
}

keyManager::~keyManager(){
	//‰½‚à‚µ‚È‚¢
}

bool keyManager::Free(){
	return Judge(true, false);
}

bool keyManager::Keep(){
	return Judge(true, true);
}

bool keyManager::Push(){
	return Judge(false, true);
}

//Œ»İ‚Ì“ü—Íó‹µ
bool keyManager::State(){
		return now_input;
}

void keyManager::Update(){
	before_input = now_input;
	now_input = (GetJoypadInputState(DX_INPUT_KEY_PAD1)& select_key) == 0 ? false : true;
}

bool keyManager::Judge(bool before_input, bool now_input){
	if ((this->before_input == before_input) && (this->now_input == now_input))
		return true;
	else
		return false;
}