#include "enemyShip.h"

enemyShip::enemyShip() {}
enemyShip::enemyShip(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
	spiralshot = new spiralShotPattern(&this->x, &this->y, &this->z, 8, 0, 0.2, 4, 1);
}
enemyShip::~enemyShip() {}
void enemyShip::Calc() {
	Move();
	Shot();
	count++;
}
void enemyShip::Move() {}
void enemyShip::Shot() {
	spiralshot->Calc();
}

xLV::xLV() {}
xLV::xLV(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
}
xLV::~xLV() {}
void xLV::Calc() {
	Move();
	Shot();
}
void xLV::Move() {
	x += add_x;
	y += add_y;
}
void xLV::Shot() {
	int tmp_x = abs(my_ship->x - x);
	int tmp_y = abs(my_ship->y - y);
	int tmp   = abs(tmp_x - tmp_y);//説明変数

	if (count == 0 && (tmp < 5)) {//大体45°で1回撃つ
		enemy_bullet.push_back(new directionalBullet(x, y, 200, 8, atan2(my_ship->y - y, my_ship->x - x), 5));
		count++;
	}
}

inFront::inFront() {}
inFront::inFront(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
}
inFront::~inFront() {}
void inFront::Calc() {
	Move();
	Shot();
	count++;
}
void inFront::Move() {
	x += add_x;
	y += add_y;
}
void inFront::Shot() {
	if (count == 60) {
		for (int i = 1; i <= 4; i++) {
			float tmp_speed = 3 + i * 0.5;
			enemy_bullet.push_back(new directionalBullet(x, y, 200, 12, angle, tmp_speed));
		}
	}
}

slalomFront::slalomFront() {}
slalomFront::slalomFront(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
}
slalomFront::~slalomFront() {}
void slalomFront::Calc() {
	Move();
	Shot();
	count++;
}
void slalomFront::Move() {
	x += speed*cos(count*0.1);
	y += add_y;
}
void slalomFront::Shot() {
	if (count == 60) {
		for (int i = 1; i <= 4; i++) {
			float tmp_speed = 3 + i * 0.5;
			enemy_bullet.push_back(new directionalBullet(x, y, 200, 12, angle, tmp_speed));
		}
	}
}

cutInLeft::cutInLeft() {}
cutInLeft::cutInLeft(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
	fit_x = false;
}
cutInLeft::~cutInLeft() {}
void cutInLeft::Calc() {
	Move();
}
void cutInLeft::Move() {
	if (fit_x) {
		if (count < 4) {
			angle += 3.141592 / 16;
			count++;
		}
	}
	else if (abs(x - my_ship->x) < 5)
		fit_x = true;

	x += speed*cos(angle);
	y += speed*sin(angle);
}

cutInRight::cutInRight() {}
cutInRight::cutInRight(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
	fit_x = false;
}
cutInRight::~cutInRight() {}
void cutInRight::Calc() {
	Move();
}
void cutInRight::Move() {
	if (fit_x) {
		if (count < 4) {
			angle -= 3.141592 / 16;
			count++;
		}
	}
	else if (abs(x - my_ship->x) < 5)
		fit_x = true;

	x += speed*cos(angle);
	y += speed*sin(angle);
}


//テスト
testSpiralShotPattern::testSpiralShotPattern() {}
testSpiralShotPattern::testSpiralShotPattern(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
	spiralshot = new spiralShotPattern(&this->x, &this->y, &this->z, 8, angle, -0.2, 4, 1);
}
testSpiralShotPattern::~testSpiralShotPattern() {
	delete spiralshot;
}
void testSpiralShotPattern::Calc() {
	Move();
	Shot();
	count++;
}
void testSpiralShotPattern::Move() {
	x += add_x;
	y += add_y;
}
void testSpiralShotPattern::Shot() {
	spiralshot->Calc();
}

testMultiSpiralShotPatten::testMultiSpiralShotPatten() {}
testMultiSpiralShotPatten::testMultiSpiralShotPatten(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
	multiple_spiral_shot_patten = new multiSpiralShotPatten(&this->x, &this->y, &this->z, 8, angle, 0.3, 6, 6, -3);
}
testMultiSpiralShotPatten::~testMultiSpiralShotPatten() {
	delete multiple_spiral_shot_patten;
}
void testMultiSpiralShotPatten::Calc() {
	Move();
	Shot();
	count++;
}
void testMultiSpiralShotPatten::Move() {
	x += add_x;
	y += add_y;
}
void testMultiSpiralShotPatten::Shot() {
	multiple_spiral_shot_patten->Calc();
}

testBothSpiralShotPatten::testBothSpiralShotPatten() {}
testBothSpiralShotPatten::testBothSpiralShotPatten(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	count = 0;
	both_spiral_shot_patten = new bothSpiralShotPatten(&this->x, &this->y, &this->z, 8, angle, 0.3, 6, 6, 5, angle, -0.1, 6, 3, -3);
}
testBothSpiralShotPatten::~testBothSpiralShotPatten() {
	delete both_spiral_shot_patten;
}
void testBothSpiralShotPatten::Calc() {
	Move();
	Shot();
	count++;
}
void testBothSpiralShotPatten::Move() {
	x += add_x;
	y += add_y;
}
void testBothSpiralShotPatten::Shot() {
	both_spiral_shot_patten->Calc();
}