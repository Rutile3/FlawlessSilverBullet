#include "MyShip.h"

//�p���łǂ��ɂ��Ȃ肻��
int energy;
const int energy_max = 120000;//1200���z��l

myShip::myShip() {}
myShip::myShip(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	energy = energy_max;
	shot_count = 0;
}
myShip::~myShip(){}
void myShip::Calc(){
	Move();
	Shot();
	//�G�l���M�[�����ʂ͌��݂̃G�l���M�[�ʂɈˑ�
	if (key->z->State() == false && key->x->State() == false) {
		if		(energy >= energy_max / 3)	energy += 4;
		else if (energy >= energy_max / 4)	energy += 3;
		else if (energy >= energy_max / 5)	energy += 2;
		else								energy += 1;
	}
	//�ő�ŏ��l�̕␳
	if (energy > energy_max)			energy = energy_max;
	else if (energy < 0)				energy = 0;
}
void myShip::Draw() {
	DrawPixel(x, y, GetColor(255, 255, 255));
	DrawCircle(x, y, r, GetColor(255, 255, 255), FALSE);
	DrawCircle(x, y, r * 1.5, GetColor(255, 255, 255), FALSE);//�摜�𒣂�]
	printfDx("energy = %d\n", energy);//�f�o�b�O�p
	DrawBox(0, 0, energy / 2, 16, GetColor(100, 100, 255), TRUE);//�f�o�b�O�p
}
void myShip::Move() {
	float naname;
	if (key->up->State()	&& key->right->State()||
		key->up->State()	&& key->left->State() ||
		key->down->State()	&& key->right->State()||
		key->down->State()	&& key->left->State() )
		naname = 1.41;
	else
		naname = 1;
	if (key->up->State()) {//���̕ӊ֐��ɂ܂Ƃ߂ꂻ��
		y -= speed / naname;
		if (y <  10) y = 10;
	}
	if (key->down->State()) {
		y += speed / naname;
		if (y > 470) y = 470;
	}
	if (key->left->State()) {
		x -= speed / naname;
		if (x <  10) x = 10;
	}
	if (key->right->State()) {
		x += speed / naname;
		if (x > 630) x = 630;
	}
}
void myShip::Shot() {
	if (key->z->State() && key->x->State() == false && energy > 0) {
		if (shot_count++ % 6 == 0) {
			my_bullet.push_back(new myBullet(x, y, z, 0, 3.141592 / 2 * 3, 24));
			//���ʉ����o��
			energy -= 2;//�ˏo���ɃG�l���M�[�����炷
		}
	}
	else
		shot_count = 0;
}

myShield::myShield() {}
myShield::myShield(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {}
myShield::~myShield() {}
void myShield::Calc() {
	//�����Ă�Ԃ͌��ʉ��𗬂��ĕ������u�ԂɌ��ʉ���؂鏈��
	//�V�[���h�̓W�J�Ək��
	if (key->x->State() && key->z->State() == false && energy > 0) {
		r >= max_r ? r = max_r : r += 2;
		angle += 0.1;//���ۂ͉��
		energy -= 4;//�W�J���Ă�Ə�Ɍ���
	}
	else 
		r <= 0 ? r = 0 : r -= 2;
}
void myShield::Draw() {
	//�G�l���M�[�����ȉ����ƃV�[���h�̐F���ω�
	DrawPixel( my_ship->x, my_ship->y,		GetColor(100, 200, 200));
	int color;
	energy >= energy_max / 5 ? GetColor(100, 200, 200) : GetColor(255, 0, 0);//�摜�̐؂�ւ�
	DrawCircle(my_ship->x, my_ship->y, r,	GetColor(100, 200, 200), FALSE);//�摜�𒣂�
}

myBullet::myBullet() {}
myBullet::myBullet(const cMover& mover) :cMover(mover) {
	float x = my_ship->x - mover.x;
	float y = my_ship->y - mover.y;
	angle = atan2(y,x)+3.141592;
	add_x = speed*cos(angle);
	add_y = speed*sin(angle);
}
myBullet::myBullet(float x, float y, float z, float r, float angle, float speed) :cMover(x, y, z, r, angle, speed) {
	if		(energy >= energy_max / 3)	this->r = 16;//�b��I�ȑ傫��
	else if (energy >= energy_max / 4)	this->r = 12;
	else if (energy >= energy_max / 5)	this->r = 8;
	else								this->r = 4;
}
myBullet::~myBullet(){}
void myBullet::Draw() {
	DrawPixel(x, y, GetColor(z, z, z));
	DrawCircle(x, y, r, GetColor(z, z-100, z-100), FALSE);
}
