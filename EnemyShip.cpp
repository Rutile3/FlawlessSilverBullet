#include "enemyShip.h"

enemyShip::enemyShip() {}
enemyShip::enemyShip(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) :cMover(x, y, z, r, angle, speed, image_name, score, hp) {
}
enemyShip::~enemyShip() {}
void enemyShip::Hit(cMover* mover) {
	float r = this->r + mover->r;//説明変数
	float x = this->x - mover->x;
	float y = this->y - mover->y;
	if (x*x + y*y < r*r && z == mover->z) {
		mover->Hit(this);
		hp -= mover->hp;
		if (hp <= 0) {
			this->x = 184184;//場外に移動させて場外判定で消す
			my_ship->score += score;
			//爆破エフェクト
		}
	}
}

xLV::xLV() {}
xLV::xLV(float x, float y, float z, float r, float angle, float speed) : enemyShip(x, y, z, r, angle, speed) {
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
	float tmp_x = abs(my_ship->x - x);
	float tmp_y = abs(my_ship->y - y);
	float tmp = abs(tmp_x - tmp_y);//説明変数

	if (count == 0 && (tmp < 5)) {//大体45°で1回撃つ
		enemy_bullet.push_back(new directionalBullet(x, y, 200, 12, atan2(my_ship->y - y, my_ship->x - x), 5, ENEMY_BULLET04));
		count++;
	}
}

inFront::inFront() {}
inFront::inFront(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) :enemyShip(x, y, z, r, angle, speed, image_name, score, hp) {
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
			float tmp_speed = 4 + i * 0.5f;
			enemy_bullet.push_back(new directionalBullet(x - 4, y, 200, 8, angle, tmp_speed, ENEMY_BULLET08));
			enemy_bullet.push_back(new directionalBullet(x + 4, y, 200, 8, angle, tmp_speed, ENEMY_BULLET08));
		}
	}
}

slalomFront::slalomFront() {}
slalomFront::slalomFront(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) :enemyShip(x, y, z, r, angle, speed, image_name, score, hp) {
	count = 0;
}
slalomFront::~slalomFront() {}
void slalomFront::Calc() {
	Move();
	Shot();
	count++;
}
void slalomFront::Move() {
	x += speed*cos(count*0.1f);
	y += add_y;
}
void slalomFront::Shot() {
	if (count == 60) {
		for (int i = 1; i <= 4; i++) {
			float tmp_speed = 4 + i * 0.5f;
			enemy_bullet.push_back(new directionalBullet(x - 4, y, 200, 8, angle, tmp_speed, ENEMY_BULLET07));
			enemy_bullet.push_back(new directionalBullet(x + 4, y, 200, 8, angle, tmp_speed, ENEMY_BULLET07));
		}
	}
}

cutInLeft::cutInLeft() {}
cutInLeft::cutInLeft(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	fit_x = false;
}
cutInLeft::~cutInLeft() {}
void cutInLeft::Calc() {
	Move();
}
void cutInLeft::Move() {
	if (fit_x) {
		if (count < 16) {
			angle += PI / 64;
			count++;
		}
	}
	else if (abs(x - my_ship->x) < 26)
		fit_x = true;

	x += speed*cos(angle);
	y += speed*sin(angle);
}

cutInRight::cutInRight() {}
cutInRight::cutInRight(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	fit_x = false;
}
cutInRight::~cutInRight() {}
void cutInRight::Calc() {
	Move();
}
void cutInRight::Move() {
	if (fit_x) {
		if (count < 16) {
			angle -= PI / 64;
			count++;
		}
	}
	else if (abs(x - my_ship->x) < 26)
		fit_x = true;

	x += speed*cos(angle);
	y += speed*sin(angle);
}

cutInUp::cutInUp() {}
cutInUp::cutInUp(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	tmp_speed = speed;
	this->speed *= 3;
}
cutInUp::~cutInUp() {}
void cutInUp::Calc() {
	Move();
}
void cutInUp::Move() {
	if (z != 200 && y < -20) {
		z++;
		speed = 0;
	}
	else if (z == 200 && angle != PI / 2) {
		angle = PI / 2;
		speed = tmp_speed;
	}

	x += speed*cos(angle);
	y += speed*sin(angle);
}

cutInDown::cutInDown() {}
cutInDown::cutInDown(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	tmp_speed = speed;
}
cutInDown::~cutInDown() {}
void cutInDown::Calc() {
	Move();
}
void cutInDown::Move() {
	if (z != 200 && y < -20) {
		z--;
		speed = 0;
	}
	else if (z == 200 && angle != PI / 2) {
		angle = PI / 2;
		speed = tmp_speed;
	}

	x += speed*cos(angle);
	y += speed*sin(angle);
}

easyInvaders::easyInvaders() {}
easyInvaders::easyInvaders(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) :enemyShip(x, y, z, r, angle, speed, image_name, score, hp) {
	count = 0;
}
easyInvaders::~easyInvaders() {}
void easyInvaders::Calc() {
	Move();
	Shot();
	count++;
}
void easyInvaders::Move() {
	if (count < 60)			speed -= 0.1f;
	else if (count == 60)	speed = 0;
	else if (count > 210)	speed += 0.2;

	x += speed*cos(angle);
	y += speed*sin(angle);
}
void easyInvaders::Shot() {
	if (count == 60 || count == 90 || count == 120) {
		for (int i = 1; i <= 4; i++) {
			float tmp_speed = 3 + i * 0.5f;
			DirectionalBullet(x - 4, y, 200, 8, angle, tmp_speed, ENEMY_BULLET07);
			DirectionalBullet(x + 4, y, 200, 8, angle, tmp_speed, ENEMY_BULLET07);
		}
	}
	else if (count == 150) 
		NWay(x, y, z, 16, angle, PI / 4, 5, 5, ENEMY_BULLET01);
}

//テスト
testSpiralShotPattern::testSpiralShotPattern() {}
testSpiralShotPattern::testSpiralShotPattern(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	spiralshot = new spiralShotPattern(&this->x, &this->y, &this->z, 8, angle, -0.2f, 4, 1);
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
testMultiSpiralShotPatten::testMultiSpiralShotPatten(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	multiple_spiral_shot_patten = new multiSpiralShotPatten(&this->x, &this->y, &this->z, 8, angle, 0.3f, 6, 6, -3);
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
testBothSpiralShotPatten::testBothSpiralShotPatten(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
	both_spiral_shot_patten = new bothSpiralShotPatten(&this->x, &this->y, &this->z, 8, angle, 0.3f, 6, 6, 5, angle, -0.1f, 6, 3, -3);
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

testNWay::testNWay() {}
testNWay::testNWay(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
}
testNWay::~testNWay() {}
void testNWay::Calc() {
	Move();
	Shot();
	count++;
}
void testNWay::Move() {
	x += add_x;
	y += add_y;
}
void testNWay::Shot() {
	if (count % 5 == 0)
		NWay(x, y, z, 6, angle + sin(count*0.01f), 2, 4, 5);//ワインダー
	//if (count % 5 == 0)
	//	NWay(x, y, z, 6, angle + count*0.1f, 1, 6, 3);//回転
	//if (count % 5 == 0)
	//	NWay(x, y, z, 6, angle, 1.5, 8, 4);//安地
}

testNCircle::testNCircle() {}
testNCircle::testNCircle(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed) {
	count = 0;
}
testNCircle::~testNCircle() {}
void testNCircle::Calc() {
	Move();
	Shot();
	count++;
}
void testNCircle::Move() {
	x += add_x;
	y += add_y;
}
void testNCircle::Shot() {
	if (count == 80)
		NCircle(x, y, z, 6, angle + sin(count*0.01f), 8, 32);
}