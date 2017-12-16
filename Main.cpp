#pragma warning(disable:4996)

#include "Main.h"

using namespace std;

void Calc();
void Collision();
void CollisionEnemyBullet();
void CollisionEnemyShip();
void CreateEnemy();
void Draw();
void EndGame();
bool ReadEnemyPattern();
void GameMain();
void OutSide();
void OutSideSub(vector<cMover*> &ve);
bool InitDxLibrary();

class enemyPattern {
public:
	enemyPattern(int count, int number, int x, int y, int z) {
		this->count = count;
		this->number = number;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	int count, number, x, y, z;
};
vector<enemyPattern*> enemy_pattern;

int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC) {
	if (InitDxLibrary() == false) return -1;
	main_count = 0;
	fps = new fpsManager(60);
	key = new cKey();
	my_ship = new myShip(320, 400, 200, 12, 0, 5);
	my_shield = new myShield(my_ship->x,my_ship->y,my_ship->z,0,0,0);
	if (ReadEnemyPattern() == false)
		return -1;

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		clsDx();
		fps->Update();
		key->Update();
		if (key->esc->Push())
			break;

		GameMain();

		fps->Draw(true);
		ScreenFlip();
		main_count++;
		fps->Wait();
	}

	EndGame();
	delete fps;
	delete key;
	DxLib_End();

	return 0;
}

void GameMain() {
	Calc();
	CreateEnemy();
	Collision();
	OutSide();
	Draw();
}

void Calc() {
	//���@->���@�V�[���h->���e->�G�@->�G�e
	my_ship->Calc();
	my_shield->x = my_ship->x;
	my_shield->y = my_ship->y;
	my_shield->z = my_ship->z;
	my_shield->Calc();
	for (int i = 0; i != my_bullet.size(); i++)
		my_bullet[i]->Calc();
	for (int i = 0; i != enemy_ship.size(); i++)
		enemy_ship[i]->Calc();
	for (int i = 0; i != enemy_bullet.size(); i++)
		enemy_bullet[i]->Calc();
}

//�{���Ȃ�t�@�C������ǂݏo��
void CreateEnemy() {
	//�f�o�b�O�p�ɓG��ʎY
	//if (main_count % 30 == 0)
	//	enemy_ship.push_back(new testNCircle(main_count % 640, -10, 200, 16, 3.141592f / 2, 3));
	//�f�o�b�O�p �̃e�X�g
	//if (main_count % 2000 == 0)
	//	enemy_ship.push_back(new testNWay(320, 200, 200, 16, 3.141592 / 2, 0));
	while (true) {
		if (main_count == enemy_pattern[0]->count) {
			enemy_ship.push_back(new testNCircle(enemy_pattern[0]->x, enemy_pattern[0]->y, enemy_pattern[0]->z, enemy_pattern[0]->number, 3.141592f / 2, 3));
			enemy_pattern.erase(enemy_pattern.begin());
		}
		else
			break;
	}
}

void Collision() {
	CollisionEnemyBullet();
	CollisionEnemyShip();
}

//�G�e->�V�[���h�Ǝ��@
void CollisionEnemyBullet() {
	unsigned int eb_i = 0;
	while (eb_i < enemy_bullet.size()) {
		if (enemy_bullet[eb_i]->Hit(my_shield)) {
			//�z�肵�Ă��鏈��
			if (false) {//�G�e���ɑ����[�U�[��
				//->�G�e�Ɠ����G�t�F�N�g�𐶐�
			}
			else{//���̑�
				my_bullet.push_back(new myBullet(*enemy_bullet[eb_i]));
			}
			enemy_bullet.erase(enemy_bullet.begin() + eb_i);
			continue;
		}
		else if (enemy_bullet[eb_i]->Hit(my_ship)) {
			//�z�肵�Ă��鏈��
			//���@�̎c�@�����炷
			//���@�𖳓G�ɂ���
			//�G�e���ђʒe��
			//->�G�e���폜����
			enemy_bullet.erase(enemy_bullet.begin() + eb_i);//���2���ȗ���
			continue;
		}
		eb_i++;
	}
}

//�G�@->���e�Ǝ��@
void CollisionEnemyShip() {
	//�G�@->���e
EnemyShip_Collision_MyBullet:
	unsigned int es_i = 0;//enemy_ship_i�̗�
	while (es_i < enemy_ship.size()) {
		unsigned int mb_i = 0;
		while (mb_i < my_bullet.size()) {//�G����������I�[�ɂȂ�\�������邩��
			if (enemy_ship[es_i]->Hit(my_bullet[mb_i])) {
				//�z�肵�Ă��鏈��
				//�G�@�Ɏ��e���̃_���[�W
				//�G�@�̐����m�F
				//->�G�@���폜
				enemy_ship.erase(enemy_ship.begin() + es_i);//���3���ȗ���
				//���e���ʏ�e��
				//->���e���폜�폜
				my_bullet.erase(my_bullet.begin() + mb_i);
				goto EnemyShip_Collision_MyBullet;
			}
			mb_i++;
		}
		es_i++;
	}

	//�G�@->���@
	es_i = 0;
	while (es_i < enemy_ship.size()) {
		if (enemy_ship[es_i]->Hit(my_ship)) {
			//�z�肵�Ă鏈��
			//�G�@�ɌŒ�_���[�W
			//�G�@�����m�F
			//->�G�@���폜
			enemy_ship.erase(enemy_ship.begin() + es_i);//���3���ȗ���
			//���@�̎c�@�����炷
			//���@�𖳓G�ɂ���
			continue;
		}
		es_i++;
	}
}

void OutSide() {
	OutSideSub(enemy_bullet);
	OutSideSub(enemy_ship);
	OutSideSub(my_bullet);
}

void OutSideSub(vector<cMover*> &ve) {
	//for���ƑS�ԗ��ł��Ȃ������Ȃ��Ă�����قǖ��Ȃ����ώG�ɂȂ�̂ł��܂͂���ł���
	for (int i = 0; i < ve.size(); i++)
		if (ve[i]->OutSide())
			ve.erase(ve.begin() + i);
}

void Draw() {
	//�f�o�b�O�p
	printfDx("es = %d\n", enemy_ship.size());
	printfDx("eb = %d\n", enemy_bullet.size());
	printfDx("mb = %d\n", my_bullet.size());

	//�G�@->���e->���@�V�[���h->���@->�G�e
	for (int i = 0; i < enemy_ship.size(); i++)
		enemy_ship[i]->Draw();
	for (int i = 0; i < my_bullet.size(); i++)
		my_bullet[i]->Draw();
	my_shield->Draw();
	my_ship->Draw();
	for (int i = 0; i < enemy_bullet.size(); i++)
		enemy_bullet[i]->Draw();
}

bool ReadEnemyPattern() {
	FILE *fp;
	int count, number, x, y, z;
	char buf[50];


	enemy_pattern.clear();
	if ((fp = fopen("enemy_pattern.csv", "r")) == NULL)	return false;
	if (fscanf(fp, "%s", buf) == EOF)					return false;
	while (true) {
		if (fscanf(fp, "%[,]", buf) == EOF)										break;
		if (fscanf(fp, "%d,%d,%d,%d,%d", &count, &number, &x, &y, &z) == EOF)	break;
		enemy_pattern.push_back(new enemyPattern(count, number, x, y, z));
	}
	enemy_pattern.erase(enemy_pattern.begin());//��[�̂��݂��폜
	enemy_pattern.push_back(new enemyPattern(216000, 0, 0, 0, 0));//�I�[�Ƀf�[�^��}�����ăf�[�^���Ȃ��ꍇ�̏������ȗ���
	fclose(fp);

	return true;
}

bool InitDxLibrary() {
	SetAlwaysRunFlag(TRUE);								//�E�C���h�E���A�N�e�B�u����Ȃ��Ă�������
	SetOutApplicationLogValidFlag(FALSE);				//���O���o�͂����Ȃ�
	SetMainWindowText("FlawlessSilverBullet");			//�t�H�[���̖��O

	ChangeWindowMode(TRUE);		//FALSE�őS���
	SetGraphMode(640, 480, 32);	//�X�N���[���̑傫��

	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void EndGame() {
	enemy_bullet.clear();
	enemy_ship.clear();
	my_bullet.clear();
	delete my_shield;
	delete my_ship;
}