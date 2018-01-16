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
	hp = mover.hp;
	image_name = mover.image_name;
	score = mover.score;
}
cMover::cMover(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->angle = angle;
	this->speed = speed;
	this->add_x = speed*cos(angle);
	this->add_y = speed*sin(angle);
	this->hp = hp;
	this->image_name = image_name;
	this->score = score;
}
cMover::~cMover() {}
void cMover::Calc() {
	x += add_x;
	y += add_y;
}
void cMover::Draw() {
	image->Draw(x, y, z, angle, image_name);
	//DrawPixel(x, y, GetColor(z, z, z));//中央点の描画（デバッグ用）
	//DrawCircle(x, y, r, GetColor(z, z, z), FALSE/*, z == 200 ? TRUE : FALSE*/);//当たり判定の視覚化
}
bool cMover::OutSide() {
	//return ... でできそう
	if (x > 640 + 50 || x < -50 ||
		y > 480 + 50 || y < -50)
		return true;
	return false;
}