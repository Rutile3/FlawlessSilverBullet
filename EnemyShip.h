#ifndef _ENEMY_SHIP_
#define _ENEMY_SHIP_

#include <assert.h>//�s�g�p
#include <DxLib.h>
#include <math.h>
#include <vector>

#include "GameKeyManager.h"

#include "EnemyBullet.h"
#include "Mover.h"
#include "MyShip.h"

using namespace std;

class enemyShip :public cMover {
public:
	enemyShip();
	enemyShip(float x, float y, float z, float r, float angle, float speed);
	~enemyShip();

	int count;
	spiralShotPattern* spiralshot;

	void Calc();
	void Move();
	void Shot();
	
};

//45���Ō����Ă�����
class xLV :public cMover {
public:
	xLV();
	xLV(float x, float y, float z, float r, float angle, float speed);
	~xLV();

	int count;

	void Calc();
	void Move();
	void Shot();
};

//�𒼂ɒ��i
class inFront :public cMover {
public:
	inFront();
	inFront(float x, float y, float z, float r, float angle, float speed);
	~inFront();

	int count;

	void Calc();
	void Move();
	void Shot();
};

//�X�����[���ˌ��i�O���j���ォ��ȊO�o���Ă͂����Ȃ��I�I
class slalomFront :public cMover {
public:
	slalomFront();
	slalomFront(float x, float y, float z, float r, float angle, float speed);
	~slalomFront();

	int count;

	void Calc();
	void Move();
	void Shot();
};

//x���������ƒ��i��45���ȊO�ŌĂяo���Ȃ��I�I
class cutInLeft :public cMover {
public:
	cutInLeft();
	cutInLeft(float x, float y, float z, float r, float angle, float speed);
	~cutInLeft();

	int count;
	bool fit_x;

	void Calc();
	void Move();
	void Shot();
};

//x���������ƒ��i��45���ȊO�ŌĂяo���Ȃ��I�I
class cutInRight :public cMover {
public:
	cutInRight();
	cutInRight(float x, float y, float z, float r, float angle, float speed);
	~cutInRight();

	int count;
	bool fit_x;

	void Calc();
	void Move();
	void Shot();
};


//�e�X�g
class testSpiralShotPattern :public cMover {
public:
	testSpiralShotPattern();
	testSpiralShotPattern(float x, float y, float z, float r, float angle, float speed);
	~testSpiralShotPattern();

	int count;
	spiralShotPattern* spiralshot;

	void Calc();
	void Move();
	void Shot();

};
class testMultiSpiralShotPatten :public cMover {
public:
	testMultiSpiralShotPatten();
	testMultiSpiralShotPatten(float x, float y, float z, float r, float angle, float speed);
	~testMultiSpiralShotPatten();

	int count;
	multiSpiralShotPatten* multiple_spiral_shot_patten;

	void Calc();
	void Move();
	void Shot();

};
class testBothSpiralShotPatten :public cMover {
public:
	testBothSpiralShotPatten();
	testBothSpiralShotPatten(float x, float y, float z, float r, float angle, float speed);
	~testBothSpiralShotPatten();

	int count;
	bothSpiralShotPatten* both_spiral_shot_patten;

	void Calc();
	void Move();
	void Shot();

};

extern vector<cMover*> enemy_bullet;
extern vector<cMover*> enemy_ship;
extern cMover* my_ship;

#endif