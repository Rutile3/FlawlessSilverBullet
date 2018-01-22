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

	if (invincible_count >0)
		invincible_count--;
}
void myShip::Draw(int lower_limits, int upper_limits) {
	if (lower_limits < z && z <= upper_limits) {
		//DrawPixel(x, y, GetColor(255, 255, 255));
		//DrawCircle(x, y, r, GetColor(255, 255, 255), FALSE);			//�����蔻��̉���
		//printfDx("energy = %d\n", energy);								//�f�o�b�O�p
		//printfDx("my_hp = %d\n", hp); assert(hp != 0);					//�f�o�b�O�p
		switch (hp) {
		case 6:image->Draw(545, 464, 200, 0, LIFE1);
		case 5:image->Draw(560, 440, 200, 0, LIFE1);
		case 4:image->Draw(575, 464, 200, 0, LIFE1);
		case 3:image->Draw(590, 440, 200, 0, LIFE1);
		case 2:image->Draw(605, 464, 200, 0, LIFE1);
		case 1:image->Draw(620, 440, 200, 0, LIFE1); break;
		default:assert(false); break;
		}
		printfDx("score = %d\n", score);								//�f�o�b�O�p
		DrawBox(0, 624, energy / 2, 640, GetColor(100, 100, 255), TRUE);	//�f�o�b�O�p
		if (key->left->State())image_name = MY_SHIP_1;
		else if (key->left->State())image_name = MY_SHIP_2;
		else						image_name = MY_SHIP_0;
		image->Draw(x, y, z, angle, image_name);
	}
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
			Explosion(this, false);
			
			this->x = 184184;//��O�Ɉړ������ď�O����ŏ���
		}
		else {
			Explosion(this,true);
			sound->Stop(EXPLOSION1);
			sound->Play(DAMAGE);
		}
	}
}

myShield::myShield() {}
myShield::myShield(float x, float y, float z, float r, float angle, float speed, int image_name) :cMover(x, y, z, r, angle, speed, image_name) {
	free_count = 0;
}
myShield::~myShield() {}
void myShield::Calc() {
	//�����Ă�Ԃ͌��ʉ��𗬂��ĕ������u�ԂɌ��ʉ���؂鏈��
	//�V�[���h�̓W�J�Ək��
	if (key->x->State() && energy > 0) {
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
void myShield::Draw(int lower_limits, int upper_limits) {
	if (lower_limits < z && z <= upper_limits) 
		image->Draw(x, y, max_r/r*z, angle, image_name);
}
void myShield::Hit(cMover* mover) {
	//���ˉ�
	if (mover->image_name == ENEMY_BULLET01 || mover->image_name == ENEMY_BULLET04 || mover->image_name == ENEMY_BULLET07)
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
	hp = mover.hp * 1.5;
	switch (mover.image_name) {
	case ENEMY_BULLET01:image_name = ENEMY_BULLET03; break;
	case ENEMY_BULLET04:image_name = ENEMY_BULLET06; break;
	case ENEMY_BULLET07:image_name = ENEMY_BULLET09; break;
	default: assert(false); break;//�O�̂���
	}
	score = mover.score;
	count = 0;
	sound->Play(REFLECTION);
}
myBullet::myBullet(float x, float y, float z, float r, float angle, float speed, int image_name) :cMover(x, y, z, r, angle, speed, image_name) {
	count = 0;
	if (energy >= energy_max / 3) {
		this->r = 16;//�b��I�ȑ傫��
		this->image_name = MY_BULLET000;
	}
	else if (energy >= energy_max / 4) {
		this->r = 12;
		this->image_name = MY_BULLET001;
	}
	else {
		this->r = 8;
		this->image_name = MY_BULLET002;
	}
	hp = this->r;
}
myBullet::~myBullet() {}
void myBullet::Draw(int lower_limits, int upper_limits) {
	if (lower_limits < z && z <= upper_limits) {
		if (image_name == ENEMY_BULLET03 || image_name == ENEMY_BULLET06 || image_name == ENEMY_BULLET09) {
			image->Draw(x, y, z, angle + count*PI / 60, image_name);
			count++;
		}
		else
			image->Draw(x, y, z, angle, image_name);
		//DrawPixel(x, y, GetColor(z, z, z));//�����_�̕`��i�f�o�b�O�p�j
		//DrawCircle(x, y, r, GetColor(z, z, z), FALSE/*, z == 200 ? TRUE : FALSE*/);//�����蔻��̎��o��
	}
}
void myBullet::Hit(cMover* mover) {
	y = 184184;
	//��e�G�t�F�N�g
	//��e��
}