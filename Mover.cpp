#include "Mover.h"

cMover::cMover() {}
cMover::cMover(const cMover& mover) {
	x = mover.x;
	y = mover.y;
	z = mover.z;
	r = mover.r;
	hp = mover.r;//テスト用
	score = mover.score;
	angle = mover.angle;
	speed = mover.speed;
	add_x = speed*cos(angle);
	add_y = speed*sin(angle);
}
cMover::cMover(float x, float y, float z, float r, float angle, float speed, int score, int hp) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->angle = angle;
	this->speed = speed;
	this->add_x = speed*cos(angle);
	this->add_y = speed*sin(angle);
	this->hp = hp;
	this->score = score;
}
cMover::~cMover() {}
void cMover::Calc() {
	x += add_x;
	y += add_y;
}
void cMover::Draw() {
	DrawPixel(x, y, GetColor(z, z, z));
	DrawCircle(x, y, r, GetColor(z, z, z), z == 200 ? TRUE : FALSE);
}
bool cMover::OutSide() {
	//return ... でできそう
	if (x > 640 + 50 || x < -50 ||
		y > 480 + 50 || y < -50)
		return true;
	return false;
}