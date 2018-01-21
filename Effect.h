#ifndef _EFFECT_
#define _EFFECT_

#include <assert.h>//ïségóp
#include <DxLib.h>
#include <vector>

#include "Mover.h"

using namespace std;

class cEffect :public cMover {
public:
	cEffect();
	cEffect(float x, float y, float z, float r, float angle, float speed, int image_name);
	~cEffect();

	virtual void Hit(cMover* mover);

};

class cExplosion :public cEffect{
public:
	cExplosion();
	cExplosion::cExplosion(float x, float y, float z, float r, float angle, float speed, int image_name);
	~cExplosion();

	void Draw();
};
void Explosion(cMover* mover, bool type);

class backGround :public cEffect {
public:
	backGround();
	backGround(float x, float y, float z, float r, float angle, float speed, int image_name, int repeat_y = 1000);
	~backGround();

	bool OutSide();
private:
	int repeat_y;
};
void BackGround(int image_name, int repeat_y);

extern vector<cMover*> effect;

#endif