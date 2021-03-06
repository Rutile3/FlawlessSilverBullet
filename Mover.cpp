#include "Mover.h"

cMover::cMover() {}
cMover::cMover(const cMover& mover) {
	x = mover.x;
	y = mover.y;
	z = mover.z;
	r = mover.r;
	angle = mover.angle;
	speed = mover.speed;
	add_x = speed*cos(angle);
	add_y = speed*sin(angle);
}
cMover::cMover(float x, float y, float z, float r, float angle, float speed) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->angle = angle;
	this->speed = speed;
	this->add_x = speed*cos(angle);
	this->add_y = speed*sin(angle);
}
cMover::~cMover() {}
void cMover::Calc() {
	x += add_x;
	y += add_y;
}
void cMover::Draw() {
	DrawPixel(x, y, GetColor(z, z, z));
	DrawCircle(x, y, r, GetColor(z, z, z), FALSE);
}
bool cMover::Hit(cMover* mover) {
	float r = this->r + mover->r;
	float x = this->x - mover->x;
	float y = this->y - mover->y;
	return x*x + y*y < r*r;
}