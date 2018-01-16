#ifndef _MOVER_
#define _MOVER_

#include <DxLib.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "GameImageManager.h"
#include "RutileMath.h"

class cMover {
public:
	cMover();
	cMover(const cMover& mover);
	cMover(float x, float y, float z, float r, float angle, float speed, int image = MY_SHIP_0, int score = 100, int hp = 12);
	~cMover();

	float angle, speed, id, r, x, y, z;
	int hp, image_name, score;

	virtual void Calc();
	virtual void Draw();
	virtual void Hit(cMover* mover) = 0;
	virtual bool OutSide();

protected:
	float add_x, add_y;
private:

};

extern imagesManager* image;

#endif