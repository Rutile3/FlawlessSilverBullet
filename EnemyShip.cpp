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
			Explosion(this, 1);
			this->x = 184184;//場外に移動させて場外判定で消す
			my_ship->score += score;
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

hoverShooter::hoverShooter() {}
hoverShooter::hoverShooter(float x, float y, float z, float r, float angle, float speed, int image_name) :enemyShip(x, y, z, r, angle, speed, image_name) {
	count = 0;
}
hoverShooter::~hoverShooter() {}
void hoverShooter::Calc() {
	Move();
	Shot();
	count++;
}
void hoverShooter::Move() {
	if (count < 450)y += speed*sin(count*PI / 90);
	else			y -= speed;

	angle = atan2(my_ship->y - y, my_ship->x - x);
}
void hoverShooter::Shot() {
	if (count % 180== 135)
		NWay(x, y, z, 8, angle, PI / 64, 4, 5, ENEMY_BULLET07);
}

virtualBug::virtualBug() {}
virtualBug::virtualBug(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) :enemyShip(x, y, z, r, angle, speed, image_name, score, hp) {
	count = 0;
	add_angle = 0;
}
virtualBug::~virtualBug() {}
void virtualBug::Calc() {
	Move();
	Shot();
	count++;
	count = count % 3600;
}
void virtualBug::Move() {
}
void virtualBug::Shot() {
	if (count < 900) {
		if (count % 6 == 0) {
			NCircle(x, y+5, z, 8, angle + add_angle, 6, 3, ENEMY_BULLET07);
			DirectionalBullet(x - 110, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
			DirectionalBullet(x + 110, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
			DirectionalBullet(x - 170, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
			DirectionalBullet(x + 170, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
		}
		else if (count % 3 == 0) {
			NCircle(x, y+5, z, 8, angle + add_angle, 6, 3, ENEMY_BULLET08);
			DirectionalBullet(x - 150, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
			DirectionalBullet(x + 150, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
			DirectionalBullet(x - 130, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
			DirectionalBullet(x + 130, y + 10, 200, 8, angle, 8, ENEMY_BULLET07);
		}
		else
			add_angle += count*PI/4056;

	}
	else if (count < 1800) {

	}
	else if (count < 2700) {

	}
	else {

	}
}

wyvernMissile::wyvernMissile() {}
wyvernMissile::wyvernMissile(float x, float y, float z, float r, float angle, float speed) :enemyShip(x, y, z, r, angle, speed,ENEMY_SHIP070,20,8) {
	count = 0;
	tmp_speed = speed;
}
wyvernMissile::~wyvernMissile() {}
void wyvernMissile::Calc() {
	Move();
}
void wyvernMissile::Move() {
	if (z != 200 && y < -50) {
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
void WyvernMissile(float x, float y, float z) {
	enemy_ship.push_back(new wyvernMissile(x, y, z, 6, PI * 3 / 2, 7));
}
wyvernUnder::wyvernUnder() {}
wyvernUnder::wyvernUnder(float x, float y, float z, float r, float angle, float speed, int image_name) :enemyShip(x, y, z, r, angle, speed, image_name) {
	count = 0;
}
wyvernUnder::~wyvernUnder() {}
void wyvernUnder::Calc() {
	Move();
	Shot();
	count++;
	count = count % 3600;
}
void wyvernUnder::Move() {
	x += add_x;
	y += add_y;
}
void wyvernUnder::Shot() {
	switch (count) {
	case 200:WyvernMissile(x + 70, y - 24, z + 1); WyvernMissile(x - 90, y - 27, z + 1); WyvernMissile(x + 110, y + 13, z + 1); WyvernMissile(x - 160, y + 19, z + 1); break;
	case 220:WyvernMissile(x + 80, y - 27, z + 1); WyvernMissile(x - 20, y - 24, z + 1); WyvernMissile(x + 150, y + 14, z + 1); WyvernMissile(x - 120, y + 14, z + 1); break;
	case 240:WyvernMissile(x + 60, y - 22, z + 1); WyvernMissile(x - 40, y - 21, z + 1); WyvernMissile(x + 100, y + 17, z + 1); WyvernMissile(x - 120, y + 12, z + 1); break;
	case 260:WyvernMissile(x + 90, y - 25, z + 1); WyvernMissile(x - 90, y - 25, z + 1); WyvernMissile(x + 120, y + 11, z + 1); WyvernMissile(x - 130, y + 11, z + 1); break;
	case 280:WyvernMissile(x + 80, y - 27, z + 1); WyvernMissile(x - 10, y - 28, z + 1); WyvernMissile(x + 150, y + 11, z + 1); WyvernMissile(x - 120, y + 15, z + 1); break;
	case 300:WyvernMissile(x + 70, y - 21, z + 1); WyvernMissile(x - 70, y - 23, z + 1); WyvernMissile(x + 160, y + 17, z + 1); WyvernMissile(x - 160, y + 18, z + 1); break;
	case 320:WyvernMissile(x + 50, y - 23, z + 1); WyvernMissile(x - 80, y - 21, z + 1); WyvernMissile(x + 140, y + 11, z + 1); WyvernMissile(x - 120, y + 12, z + 1); break;
	case 340:WyvernMissile(x + 10, y - 27, z + 1); WyvernMissile(x - 30, y - 25, z + 1); WyvernMissile(x + 120, y + 14, z + 1); WyvernMissile(x - 140, y + 14, z + 1); break;
	case 360:WyvernMissile(x + 70, y - 24, z + 1); WyvernMissile(x - 50, y - 20, z + 1); WyvernMissile(x + 150, y + 17, z + 1); WyvernMissile(x - 110, y + 11, z + 1); break;
	case 380:WyvernMissile(x + 60, y - 23, z + 1); WyvernMissile(x - 60, y - 21, z + 1); WyvernMissile(x + 110, y + 18, z + 1); WyvernMissile(x - 150, y + 15, z + 1); break;
	default:break;
	}
}
bool wyvernUnder::OutSide() {
	//return ... でできそう
	if (x > 640 + 200 || x < -200 ||
		y > 480 + 200 || y < -200)
		return true;
	return false;
}

//仮（絶対後から書き直す）
float x_2[16] = { 130, -130, 200, -200, 70, 120, 150, 180, 210, 240, -70, -120, -150, -180, -210, -240 };
float y_2[16] = { 8, 8, 40, 40, -15, -15, -5, 5, 25, 35, -15, -15, -5, 5, 25, 35 };
float r_2[16] = { 16, 16, 32, 32, 32, 16, 16, 16, 16, 16, 32, 16, 16, 16, 16, 16 };
int hp_2[4] = { 500, 500, 200, 200 };
int score_2[4] = { 2000, 2000, 1000, 1000 };
static bool destroy_part[4] = { false, false, false, false };
cWyvern::cWyvern() {}
cWyvern::cWyvern(float x, float y, float z, float r, float angle, float speed, int image_name, int score, int hp) :enemyShip(x, y, z, r, angle, speed, image_name, score, hp) {
	count = 0;
	add_angle = 0;
}
cWyvern::~cWyvern() {}
void cWyvern::Calc() {
	Move();
	Shot();
	count++;
	count = count % 3600;
}
void cWyvern::Move() {
}
void cWyvern::Shot() {
	if (destroy_part[0] == true && destroy_part[1] == true) {
		if (count % 4 == 0)
			NCircle(x, y - 24, z, 8, angle + add_angle, 6, 3, ENEMY_BULLET07);
		else if (count % 2 == 0) 
			NCircle(x, y - 24, z, 8, angle + add_angle, 6, 3, ENEMY_BULLET08);
		else
			add_angle += count*PI / 4056;

		for (int i = 0; i < 4; i++) {
			if (count % 12 == 0)
				NWay(x, y - 24, z, 12, angle + add_angle/8, PI / 4, 6 + i/4.0f, 8, ENEMY_BULLET04);
			else if (count % 6 == 0)
				NWay(x, y - 24, z, 12, angle - add_angle/8, PI / 4, 6 + i/4.0f, 8, ENEMY_BULLET04);
		}
	}
	//else if (count < 1800) {

	//}
	//else if (count < 2700) {

	//}
	else {
		float x;
		float y;
		switch (count % 210) {
		case 0:case 30:case 60:case 90:case 120:case 150:
			x = my_ship->x - this->x;
			y = my_ship->y - (this->y-24);
			NWay(this->x, this->y - 24, z, 8, atan2(y,x), PI / 8, 6, 2, ENEMY_BULLET08);
			break;
		case 15:case 75:case 135:
			if (destroy_part[0] == true) {
				x = my_ship->x - this->x;
				y = my_ship->y - (this->y - 24);
				NWay(this->x, this->y - 24, z, 8, atan2(y, x), PI / 16, 6, 2, ENEMY_BULLET07);
			}
			break;
		case 45:case 115:case 165:
			if (destroy_part[1] == true) {
				x = my_ship->x - this->x;
				y = my_ship->y - (this->y - 24);
				NWay(this->x, this->y - 24, z, 8, atan2(y, x), PI / 16, 6, 2, ENEMY_BULLET07);
			}
			break;
		case 180:
			x = my_ship->x - this->x;
			y = my_ship->y - this->y;
			if (destroy_part[0] == false)
				for (int i = 0; i < 8; i++)
					DirectionalBullet(this->x + x_2[0], this->y + y_2[0], z, 12, atan2(y, x-x_2[0]), 5 + i / 5.0f, ENEMY_BULLET04);
			if (destroy_part[1] == false)
				for (int i = 0; i < 8; i++)
					DirectionalBullet(this->x + x_2[1], this->y + y_2[1], z, 12, atan2(y, x-x_2[1]), 5 + i / 5.0f, ENEMY_BULLET04);
			break;
		default:
			break;
		}
	}
}
void cWyvern::Draw(int lower_limits, int upper_limits) {
	if (lower_limits < z && z <= upper_limits) {
		if (destroy_part[2] == false)
			image->Draw(x, y, z, angle, ENEMY_SHIP065);
		if (destroy_part[3] == false)
			image->Draw(x, y, z, angle, ENEMY_SHIP064);
		image->Draw(x, y, z, angle, ENEMY_SHIP063);
		image->Draw(x, y, z, angle, ENEMY_SHIP062);
		image->Draw(x, y, z, angle, ENEMY_SHIP061);
		if (destroy_part[0] == false)
			image->Draw(x + 130, y + 8, z, atan2(my_ship->y - this->y - y_2[0], my_ship->x - this->x - x_2[0]), ENEMY_SHIP066);
		if (destroy_part[1] == false)
			image->Draw(x - 130, y + 8, z, atan2(my_ship->y - this->y - y_2[1], my_ship->x - this->x - x_2[1]), ENEMY_SHIP066);
		//デバッグ用に当たり判定を表示
		DrawCircle(x, y, r, GetColor(z, z, z), FALSE);				//本体
		for (int i = 0; i < 16; i++)
			DrawCircle(x+x_2[i], y+y_2[i], r_2[i], GetColor(z, z, z), FALSE);
	}
}
void cWyvern::Hit(cMover* mover) {
	float r = this->r + mover->r;//説明変数
	float x = this->x - mover->x;
	float y = this->y - mover->y;
	if (x*x + y*y < r*r && z == mover->z) {
		mover->Hit(this);
		hp -= mover->hp;
		if (hp <= 0) {
			Explosion(this, 1);
			this->x = 184184;//場外に移動させて場外判定で消す
			my_ship->score += score;
		}
	}
	for (int i = 0; i < 16; i++) {
		float r = r_2[i] + mover->r;//説明変数
		float x = this->x + x_2[i] - mover->x;
		float y = this->y + y_2[i] - mover->y;
		if (x*x + y*y < r*r && z == mover->z) {
			mover->Hit(this);
			if (i < 4 && destroy_part[i] == false) {
				hp_2[i] -= mover->hp;
				if (hp_2[i] <= 0) {
					enemyShip* tmp;
					Explosion(tmp  = new enemyShip(this->x+x_2[i],this->y+y_2[i],z,0,0,0), 1);
					delete tmp;
					destroy_part[i] = true;
					my_ship->score += score_2[i];
				}
			}
			else {
				hp -= mover->hp;
				if (hp <= 0) {
					Explosion(this, 1);
					this->x = 184184;//場外に移動させて場外判定で消す
					my_ship->score += score;
				}
			}
		}
	}
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