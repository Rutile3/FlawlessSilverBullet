#ifndef _MY_SHIP_
#define _MY_SHIP_

#include <assert.h>
#include <DxLib.h>
#include <math.h>
#include <vector>

#include "GameKeyManager.h"

#include "Mover.h"

using namespace std;

class myShield :public cMover {
public:
	myShield();
	myShield(float x, float y, float z, float r, float angle, float speed);
	~myShield();

	const int max_r = 32;
	int free_count;

	void Calc();
	void Draw();
};

class myShip :public cMover {
public:
	myShip();
	myShip(float x, float y, float z, float r, float angle, float speed);
	~myShip();

	int shot_count;

	void Calc();
	void Draw();
	void Move();
	void Shot();
};

class myBullet :public cMover {
public:
	myBullet();
	myBullet(const cMover& mover);
	myBullet(float x, float y, float z, float r, float angle, float speed);
	~myBullet();

	void Draw();
};

extern cKey* key;
extern cMover* my_ship;
extern cMover* my_shield;
extern vector<cMover*> my_bullet;

#endif