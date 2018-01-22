#include "Effect.h"

cEffect::cEffect() {
}
cEffect::cEffect(float x, float y, float z, float r, float angle, float speed, int image_name) :cMover(x, y, z, r, angle, speed, image_name, score, hp) {
}
cEffect::~cEffect() {
}
void cEffect::Hit(cMover* mover) {
}

cExplosion::cExplosion() {
}
cExplosion::cExplosion(float x, float y, float z, float r, float angle, float speed, int image_name) :cEffect(x, y, z, r, angle, speed, image_name) {
	sound->Play(EXPLOSION1);
}
cExplosion::~cExplosion() {
}
void cExplosion::Draw(int lower_limits, int upper_limits) {
	if (lower_limits < z && z <= upper_limits) {
		image->Draw(x, y, z, angle, image_name);
		if (image_name == EFFECT021 || image_name == EFFECT039)
			y = 184184;
		else
			image_name++;
	}
}
void Explosion(cMover* mover, bool type) {
	if (type)
		effect.push_back(new cExplosion(mover->x, mover->y, mover->z, mover->r, mover->angle, 0, EFFECT010));
	else
		effect.push_back(new cExplosion(mover->x, mover->y, mover->z, mover->r, mover->angle, 0, EFFECT030));
}

backGround::backGround() {}
backGround::backGround(float x, float y, float z, float r, float angle, float speed, int image_name, int repeat_y) :cEffect(x, y, z, r, angle, speed, image_name) {
	this->repeat_y = repeat_y;
	base_z = z;
}
backGround::~backGround() {}
void backGround::Draw(int lower_limits, int upper_limits) {
	if (lower_limits < z && z <= upper_limits) {
		image->Draw(x, y, z/base_z*200, angle, image_name);
		//DrawPixel(x, y, GetColor(z, z, z));//中央点の描画（デバッグ用）
		//DrawCircle(x, y, r, GetColor(z, z, z), FALSE/*, z == 200 ? TRUE : FALSE*/);//当たり判定の視覚化
	}
}
bool backGround::OutSide() {
	if (y >= repeat_y)
		y *= -1;
	//return ... でできそう
	if (z > 500 || z < 50)
		return true;
	return false;
}
void BackGround(int z, int speed, int image_name, int repeat_y) {
	effect.push_back(new backGround(320, repeat_y * 0.5, z, 0, PI / 2, speed, image_name, repeat_y));
	effect.push_back(new backGround(320, repeat_y * -0.5, z, 0, PI / 2, speed, image_name, repeat_y));
}