#ifndef _MOVER_
#define _MOVER_

#include <DxLib.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "RutileMath.h"

class cMover {
public:
	cMover();
	cMover(const cMover& mover);
	cMover(float x, float y, float z, float r, float angle, float speed);
	~cMover();

	float angle, speed, id, r, x, y, z;
	int hp;

	virtual void Calc();
	virtual void Draw();
	virtual void Hit(cMover* mover) = 0;
	virtual bool OutSide();

protected:
	float add_x, add_y;
	//imageManager
private:

};

#endif