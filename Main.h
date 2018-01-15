#ifndef _INCLUDR_MAIN_
#define _INCLUDR_MAIN_

#include <assert.h>
#include <DxLib.h>
#include <vector>

#include "FpsManager.h"
#include "GameImageManager.h"
#include "GameKeyManager.h"
#include "RutileMath.h"

#include "EnemyBullet.h"
#include "EnemyShip.h"
#include "MyShip.h"

using namespace std;

enum GAME_MODE {
	TITLE,
	GAME_MAIN
};
GAME_MODE game_mode;

int stage;
int main_count;
cKey* key;
fpsManager* fps;
imagesManager* image;

vector<cMover*> effect;
vector<cMover*> enemy_bullet;
vector<cMover*> enemy_ship;
vector<cMover*> my_bullet;
cMover* my_shield;
cMover* my_ship;

#endif