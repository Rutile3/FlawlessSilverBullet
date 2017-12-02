#include "GameKeyManager.h"

cKey::cKey(){
	int key[9];
	key[0] = PAD_INPUT_A;
	key[1] = PAD_INPUT_B;
	key[2] = PAD_INPUT_C;
	key[3] = PAD_INPUT_X;
	key[4] = PAD_INPUT_Y;
	key[5] = PAD_INPUT_Z;
	key[6] = PAD_INPUT_L;
	key[7] = PAD_INPUT_R;
	key[8] = PAD_INPUT_M;

	down	= new keyManager(PAD_INPUT_DOWN);
	right	= new keyManager(PAD_INPUT_RIGHT);
	left	= new keyManager(PAD_INPUT_LEFT);
	up		= new keyManager(PAD_INPUT_UP);
	esc		= new keyManager(PAD_INPUT_START);
	this->z = new keyManager(key[0]);
	this->x = new keyManager(key[1]);
	this->space = new keyManager(key[8]);

}

cKey::~cKey(){
	delete x;
	delete z;
	delete down;
	delete right;
	delete left;
	delete up;
	delete esc;
	delete space;
}

void cKey::Update(){
	x->Update();
	z->Update();
	down->Update();
	right->Update();
	left->Update();
	up->Update();
	esc->Update();
	space->Update();
}