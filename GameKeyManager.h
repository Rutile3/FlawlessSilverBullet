#ifndef _INCLUDE_GAME_KEY_MANAGER_
#define _INCLUDE_GAME_KEY_MANAGER_

#include <DxLib.h>
#include "KeyManager.h"

class keysManager {
public:
	keysManager();
	~keysManager();

	void Update();

	keyManager* z;
	keyManager* x;
	keyManager* space;
	keyManager* esc;
	keyManager* up;
	keyManager* down;
	keyManager* right;
	keyManager* left;

private:

};

#endif