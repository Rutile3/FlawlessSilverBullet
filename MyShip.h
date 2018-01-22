#ifndef _MY_SHIP_
#define _MY_SHIP_

#include <assert.h>
#include <DxLib.h>
#include <vector>

#include "GameKeyManager.h"
#include "GameSoundManager.h"
#include "RutileMath.h"

#include "Effect.h"
#include "Mover.h"

using namespace std;

class myShield :public cMover {
public:
	myShield();
	myShield(float x, float y, float z, float r, float angle, float speed, int image_name = MY_SHIP_0);
	~myShield();

	const int max_r = 32;
	int free_count;

	void Calc();
	void Draw(int lower_limits = 199, int upper_limits = 200);
	void Hit(cMover* mover);
};

class myShip :public cMover {
public:
	myShip();
	myShip(float x, float y, float z, float r, float angle, float speed, int image_name = MY_SHIP_0);
	~myShip();

	int shot_count;

	void Calc();
	void Draw(int lower_limits = 199, int upper_limits = 200);
	void Move();
	void Shot();
	void Hit(cMover* mover);

private:
	int invincible_count;
};

class myBullet :public cMover {
public:
	myBullet();
	myBullet(const cMover& mover);
	myBullet(float x, float y, float z, float r, float angle, float speed, int image_name = MY_BULLET000);
	~myBullet();

	void Draw(int lower_limits = 199, int upper_limits = 200);
	void Hit(cMover* mover);

private:
	int count;
};

extern keysManager* key;
extern cMover* my_ship;
extern cMover* my_shield;
extern vector<cMover*> my_bullet;
extern soundsManager* sound;

#endif