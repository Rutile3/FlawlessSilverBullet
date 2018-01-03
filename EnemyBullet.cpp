#include"enemyBullet.h"

//弾種
directionalBullet::directionalBullet() {}
directionalBullet::directionalBullet(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {}
directionalBullet::~directionalBullet() {}
void directionalBullet::Hit(cMover* mover) {
	float r = this->r + mover->r;//説明変数
	float x = this->x - mover->x;
	float y = this->y - mover->y;
	if (x*x + y*y < r*r) {
		mover->Hit(this);
		this->x = -184184;//場外に移動させて場外判定で消す
		//爆破エフェクト
	}
}


//弾幕(関数)
void NWay(float x, float y, float z, float r, float angle, float angle_renge, float speed, float shots) {
	if (shots == 1) {
		enemy_bullet.push_back(new directionalBullet(x, y, z, r, angle, speed));
	}
	else {
		for (int i = 0; i < shots; i++) {
			float tmp_angle = angle + angle_renge*(i / (shots - 1) - 0.5f);
			enemy_bullet.push_back(new directionalBullet(x, y, z, r, tmp_angle, speed));
		}
	}
}

void NCircle(float x, float y, float z, float r, float angle, float speed, float shots) {
	NWay(x, y, z, r, angle, 2 * PI, speed, shots - 1);
}

//弾幕(クラス)
spiralShotPattern::spiralShotPattern() {}
spiralShotPattern::spiralShotPattern(float* x, float* y,float* z, float r, float angle, float angle_rate, float speed, int interval) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->angle = angle;
	this->angle_rate = angle_rate;
	this->interval = interval;
	this->speed = speed;
	count = 0;
}
spiralShotPattern::~spiralShotPattern() {}
void spiralShotPattern::Calc() {
	if (count % interval == 0) {
		enemy_bullet.push_back(new directionalBullet(*x, *y, *z, r, angle, speed));
		angle += angle_rate;
	}
	count++;
}

multiSpiralShotPatten::multiSpiralShotPatten() {}
multiSpiralShotPatten::multiSpiralShotPatten(float* x, float* y, float* z, float r, float angle, float angle_rate, float speed, int interval, int  way) {
	if (way < 0) {
		way *= -1;
		angle += PI;
	}
	for (int i = 0; i < way; i++) {
		float tmp_angle = angle + 2 * PI / way * i;
		spiral_shot_pattern.push_back(new spiralShotPattern(x, y, z, r, tmp_angle, angle_rate, speed, interval));
	}
}
multiSpiralShotPatten::~multiSpiralShotPatten() {
	spiral_shot_pattern.clear();
}
void multiSpiralShotPatten::Calc() {
	for (int i = 0; i < spiral_shot_pattern.size(); i++)
		spiral_shot_pattern[i]->Calc();
}

bothSpiralShotPatten::bothSpiralShotPatten() {}
bothSpiralShotPatten::bothSpiralShotPatten(float* x, float* y, float* z, float r, float angle_1, float angle_rate_1, float speed_1, int interval_1, int way_1, float angle_2, float angle_rate_2, float speed_2, int interval_2, int way_2) {
	multi_spiral_shot_patten[0] = new multiSpiralShotPatten(x, y, z, r, angle_1, angle_rate_1, speed_1, interval_1, way_1);
	multi_spiral_shot_patten[1] = new multiSpiralShotPatten(x, y, z, r, angle_2, angle_rate_2, speed_2, interval_2, way_2);
}
bothSpiralShotPatten::~bothSpiralShotPatten() {
	delete[] multi_spiral_shot_patten;
}
void bothSpiralShotPatten::Calc() {
	multi_spiral_shot_patten[0]->Calc();
	multi_spiral_shot_patten[1]->Calc();
}
