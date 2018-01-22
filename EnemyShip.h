#ifndef _ENEMY_SHIP_
#define _ENEMY_SHIP_

#include <assert.h>//�s�g�p
#include <DxLib.h>
#include <vector>

#include "GameKeyManager.h"
#include "RutileMath.h"

#include "Effect.h"
#include "EnemyBullet.h"
#include "Mover.h"
#include "MyShip.h"

using namespace std;

class enemyShip :public cMover {
public:
	enemyShip();
	enemyShip(float x, float y, float z, float r, float angle, float speed, int image_name = ENEMY_SHIP010, int score = 100, int hp = 10);
	~enemyShip();

	void Hit(cMover* mover);
};

//45���Ō����Ă�����
class xLV :public enemyShip {
public:
	xLV();
	xLV(float x, float y, float z, float r, float angle, float speed);
	~xLV();

	void Calc();

private:
	int count;

	void Move();
	void Shot();
};

//�𒼂ɒ��i
class inFront :public enemyShip {
public:
	inFront();
	inFront(float x, float y, float z, float r, float angle, float speed, int image_name, int score = 100, int hp = 10);
	~inFront();

	void Calc();
private:
	int count;

	void Move();
	void Shot();
};

//�X�����[���ˌ��i�O���j���ォ��ȊO�o���Ă͂����Ȃ��I�I
class slalomFront :public enemyShip {
public:
	slalomFront();
	slalomFront(float x, float y, float z, float r, float angle, float speed, int image_name, int score = 100, int hp = 10);
	~slalomFront();

	void Calc();
private:
	int count;

	void Move();
	void Shot();
};

//x���������ƒ��i��45���ȊO�ŌĂяo���Ȃ��I�I
class cutInLeft :public enemyShip {
public:
	cutInLeft();
	cutInLeft(float x, float y, float z, float r, float angle, float speed);
	~cutInLeft();

	void Calc();

private:
	int count;
	bool fit_x;

	void Move();
};

//x���������ƒ��i��45���ȊO�ŌĂяo���Ȃ��I�I
class cutInRight :public enemyShip {
public:
	cutInRight();
	cutInRight(float x, float y, float z, float r, float angle, float speed);
	~cutInRight();

	void Calc();

private:
	int count;
	bool fit_x;

	void Move();
};

//�ォ�炭����z=100�ȊO�ŌĂяo���Ȃ��I�I
class cutInUp :public enemyShip {
public:
	cutInUp();
	cutInUp(float x, float y, float z, float r, float angle, float speed);
	~cutInUp();

	void Calc();

private:
	int count;
	int tmp_speed;

	void Move();
};

//�����炭����z=300�ȊO�ŌĂяo���Ȃ��I�I
class cutInDown :public enemyShip {
public:
	cutInDown();
	cutInDown(float x, float y, float z, float r, float angle, float speed);
	~cutInDown();

	void Calc();

private:
	int count;
	int tmp_speed;

	void Move();
};

class easyInvaders :public enemyShip {
public:
	easyInvaders();
	easyInvaders(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp);
	~easyInvaders();

	void Calc();

private:
	int count;

	void Move();
	void Shot();
};

class hoverShooter :public enemyShip {
public:
	hoverShooter();
	hoverShooter(float x, float y, float z, float r, float angle, float speed, int image_name);
	~hoverShooter();

	void Calc();

private:
	int count;

	void Move();
	void Shot();
};

class virtualBug :public enemyShip {
public:
	virtualBug();
	virtualBug(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp);
	~virtualBug();

	void Calc();

private:
	int count;
	float add_angle;

	void Move();
	void Shot();
};

class wyvernUnder :public enemyShip {
public:
	wyvernUnder();
	wyvernUnder(float x, float y, float z, float r, float angle, float speed, int image_name);
	~wyvernUnder();

	void Calc();

private:
	int count;

	void Move();
	void Shot();
	bool OutSide();
};

class wyvernMissile :public enemyShip {
public:
	wyvernMissile();
	wyvernMissile(float x, float y, float z, float r, float angle, float speed);
	~wyvernMissile();

	void Calc();

private:
	int count;
	int tmp_speed;

	void Move();
};

class cWyvern :public enemyShip {
public:
	cWyvern();
	cWyvern(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp);
	~cWyvern();

	void Calc();

private:
	int count;
	float add_angle;

	void Move();
	void Shot();
};

//�e�X�g
class testSpiralShotPattern :public enemyShip {
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
class testMultiSpiralShotPatten :public enemyShip {
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
class testBothSpiralShotPatten :public enemyShip {
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
class testNWay :public enemyShip {
public:
	testNWay();
	testNWay(float x, float y, float z, float r, float angle, float speed);
	~testNWay();

	void Calc();

private:
	int count;

	void Move();
	void Shot();
};
class testNCircle :public enemyShip {
public:
	testNCircle();
	testNCircle(float x, float y, float z, float r, float angle, float speed);
	~testNCircle();

	void Calc();

private:
	int count;

	void Move();
	void Shot();
};

extern vector<cMover*> effect;
extern vector<cMover*> enemy_bullet;
extern vector<cMover*> enemy_ship;
extern cMover* my_ship;

#endif