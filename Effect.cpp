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
}
cExplosion::~cExplosion() {
}
void cExplosion::Draw() {
	image->Draw(x, y, z, angle, image_name);
	if (image_name == EFFECT021 || image_name == EFFECT039)
		y = 184184;
	else
		image_name++;
}
void Explosion(cMover* mover, bool type) {
	if (type)
		effect.push_back(new cExplosion(mover->x, mover->y, mover->z, mover->r, mover->angle, 0, EFFECT010));
	else
		effect.push_back(new cExplosion(mover->x, mover->y, mover->z, mover->r, mover->angle, 0, EFFECT030));
}

backGraung::backGraung() {
}
backGraung::backGraung(float x, float y, float z, float r, float angle, float speed, int image_name) :cEffect(x, y, z, r, angle, speed, image_name) {
}
backGraung::~backGraung() {
}
bool backGraung::OutSide() {
	//return ... ‚Å‚Å‚«‚»‚¤
	if (z > 500 || z < 50)
		return true;
	return false;
}