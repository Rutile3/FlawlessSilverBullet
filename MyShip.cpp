#include "MyShip.h"

//�p���łǂ��ɂ��Ȃ肻��
int energy;
const int energy_max = 800;//800���z��l

myShip::myShip() {}
myShip::myShip(float x, float y, float z, float r, float angle, float speed, int image_name) :cMover(x, y, z, r, angle, speed, image_name, 0, 6) {
	energy = energy_max;
	invincible_count = 0;
	shot_count = 0;
}
myShip::~myShip(){}
void myShip::Calc(){
	Move();
	Shot();
	//�G�l���M�[�����ʂ͌��݂̃G�l���M�[�ʂɈˑ�
	if (key->x->State() == false) {
		if		(energy >= energy_max / 3)	energy += 6;
		else if (energy >= energy_max / 9)	energy += 5;
		else 								energy += 3;
	}
	//�ő�ŏ��l�̕␳
	if (energy > energy_max)			energy = energy_max;
	else if (energy < 0)				energy = 0;
}
void myShip::Draw() {
	//DrawPixel(x, y, GetColor(255, 255, 255));
	DrawCircle(x, y, r, GetColor(255, 255, 255), FALSE);			//�����蔻��̉���
	printfDx("energy = %d\n", energy);								//�f�o�b�O�p
	printfDx("my_hp = %d\n", hp); assert(hp != 0);					//�f�o�b�O�p
	printfDx("score = %d\n", score);								//�f�o�b�O�p
	DrawBox(0, 0, energy / 2, 16, GetColor(100, 100, 255), TRUE);	//�f�o�b�O�p

	image->Draw(x, y, z, angle, image_name);
}
void myShip::Move() {
	float naname;
	if (key->up->State()	&& key->right->State()||
		key->up->State()	&& key->left->State() ||
		key->down->State()	&& key->right->State()||
		key->down->State()	&& key->left->State() )
		naname = 1.41f;//��2
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
			my_bullet.push_back(new myBullet(x, y, z, 0, PI / 2 * 3, 24));
			//���ʉ����o��
			energy -= 4;//�ˏo���ɃG�l���M�[�����炷
		}
	}
	else
		shot_count = 0;
}
void myShip::Hit(cMover* mover) {
	if (invincible_count == 0) {
		invincible_count = 60;
		hp--;
		if (hp <= 0) {
			this->x = 184184;//��O�Ɉړ������ď�O����ŏ���
			//���j�G�t�F�N�g
			//���j��
		}
		else {
			//��e�G�t�F�N�g
			//��e��
		}
	}
	else
		invincible_count--;
}

myShield::myShield() {}
myShield::myShield(float x, float y, float z, float r, float angle, float speed, int image_name) :cMover(x, y, z, r, angle, speed, image_name) {
	free_count = 0;
}
myShield::~myShield() {}
void myShield::Calc() {
	//�����Ă�Ԃ͌��ʉ��𗬂��ĕ������u�ԂɌ��ʉ���؂鏈��
	//�V�[���h�̓W�J�Ək��
	if (key->x->State() && key->z->State() == false && energy > 0) {
		r >= max_r ? r = max_r : r += 8;
		angle += 0.1f;//���ۂ͉��
		energy -= 4;//�W�J���Ă�Ə�Ɍ���
		free_count = 0;
	}
	else {
		r <= 0 ? r = 0 : r -= 4;
		if (free_count <= 20) {
			free_count++;
			energy -= 2;
		}
	}
}
void myShield::Draw() {
	image->Draw(x, y, max_r/r*z, angle, image_name);
}
void myShield::Hit(cMover* mover) {
	//���ˉ�
	my_bullet.push_back(new myBullet(*mover));
}


myBullet::myBullet() {}
myBullet::myBullet(const cMover& mover) :cMover(mover) {
	float x = my_ship->x - mover.x;
	float y = my_ship->y - mover.y;
	angle = atan2(y,x)+PI;//OR����
	speed = mover.speed*1.5f;
	add_x = speed*cos(angle);
	add_y = speed*sin(angle);
	hp    = mover.hp*1.5f;
	image_name = mover.image_name;
	score = mover.score;
}
myBullet::myBullet(float x, float y, float z, float r, float angle, float speed, int image_name) :cMover(x, y, z, r, angle, speed, image_name) {
	if		(energy >= energy_max / 3)	this->r = 16;//�b��I�ȑ傫��
	else if (energy >= energy_max / 4)	this->r = 12;
	else if (energy >= energy_max / 5)	this->r = 8;
	else								this->r = 4;
	hp = this->r;
}
myBullet::~myBullet(){}
void myBullet::Hit(cMover* mover) {
	y = 184184;
	//��e�G�t�F�N�g
	//��e��
}