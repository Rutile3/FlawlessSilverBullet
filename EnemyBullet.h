#ifndef _ENEMY__BULLET_
#define _ENEMY__BULLET_

#include <assert.h>//•sŽg—p
#include <DxLib.h>
#include <math.h>
#include <vector>

#include "GameKeyManager.h"

#include "Mover.h"

using namespace std;

//•ûŒü’e
class directionalBullet :public cMover {
public:
	directionalBullet();
	directionalBullet(float x, float y, float z, float r, float angle, float speed);//Šp“x‚¢‚ç‚ñ‚©‚à
	~directionalBullet();
};

//‰QŠª’e
class spiralShotPattern {
public:
	spiralShotPattern();
	spiralShotPattern(float* x, float* y, float* z, float r, float angle, float angle_rate, float speed, float interval);
	~spiralShotPattern();

	void Calc();

private:
	float* x;
	float* y;
	float* z;
	float angle;
	float angle_rate;
	float r;
	float speed;
	int count;
	int interval;
};
//‘½•ûŒü‰QŠª’e
class multiSpiralShotPatten {
public:
	multiSpiralShotPatten();
	multiSpiralShotPatten(float* x, float* y, float* z, float r, float angle, float angle_rate, float speed, float interval, int  way);
	~multiSpiralShotPatten();

	void Calc();

private:
	vector<spiralShotPattern*> spiral_shot_pattern;
};
//—¼‰ñ“]‰QŠª’e
class bothSpiralShotPatten {
public:
	bothSpiralShotPatten();
	bothSpiralShotPatten(float* x, float* y, float* z, float r, float angle_1, float angle_rate_1, float speed_1, float interval_1, int way_1, float angle_2, float angle_rate_2, float speed_2, float interval_2, int way_2);
	~bothSpiralShotPatten();

	void Calc();

private:
	multiSpiralShotPatten* multi_spiral_shot_patten[2];
};

//NWay’e
void NWay(float x, float y, float z, float r, float angle, float angle_renge, float speed, float shots);


extern vector<cMover*> enemy_bullet;

#endif