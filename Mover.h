#ifndef _MOVER_
#define _MOVER_

#include <DxLib.h>
#include <math.h>
#include <vector>

class cMover {
public:
	cMover();
	cMover(const cMover& mover);
	cMover(float x, float y, float z, float r, float angle, float speed);
	~cMover();

	float angle, speed, hp, id, r, x, y, z;

	virtual void Calc();
	virtual void Draw();
	virtual bool Hit(cMover* mover);
	virtual bool OutSide();

protected:
	float add_x, add_y;
	//imageManager
private:

};

#endif