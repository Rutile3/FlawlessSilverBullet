#pragma warning(disable:4996)

#include "Main.h"

using namespace std;

void Calc();
void Collision();
void CreateEnemy();
void Draw();
void EndGame();
bool ReadEnemyPattern();
void GameMain();
void OutSide();
void OutSideSub(vector<cMover*> &ve);
bool InitDxLibrary();
void InitGame();
void Title();

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
	InitGame();

	//���̂����ڂ�
	if (ReadEnemyPattern() == false)
		return -1;

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		clsDx();
		fps->Update();
		key->Update();
		if (key->esc->Push())
			break;
		switch (game_mode) {
		case TITLE:		Title();	break;
		case GAME_MAIN: GameMain(); break;
		default:
			break;
		}

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

void Title() {
	printfDx("FlawlessSilverBullet\n");
	printfDx("Please Z Key\n");

	if (key->z->Push() == true) {
		game_mode = GAME_MAIN;
		main_count = 0;
	}
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

//�����Ŗʂ��w��ł���悤�ɂ���B
bool ReadEnemyPattern() {
	FILE *fp;
	int count, number, x, y, z;
	char buf[50];

	enemy_pattern.clear();
	if ((fp = fopen("enemy_pattern1.csv", "r")) == NULL)	return false;
	if (fscanf(fp, "%s\n", buf) == EOF)					return false;
	while (true) {
		if (fscanf(fp, "%[,]", buf) == EOF)										break;
		if (fscanf(fp, "%d,%d,%d,%d,%d\n", &count, &number, &x, &y, &z) == EOF)	break;
		enemy_pattern.push_back(new enemyPattern(count, number, x, y, z));
	}
	fclose(fp);

	return true;
}

void Collision() {
	//�G�e->�V�[���h�Ǝ��@
	for (int i = 0; i < enemy_bullet.size(); i++) {
		enemy_bullet[i]->Hit(my_shield);
		enemy_bullet[i]->Hit(my_ship);
	}
	//�G�@->���e�Ǝ��@
	for (int i = 0; i < enemy_ship.size(); i++) {
		for (int j = 0; j < my_bullet.size(); j++)
			enemy_ship[i]->Hit(my_bullet[j]);
		enemy_ship[i]->Hit(my_ship);
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
		enemy_ship[i]->Draw();//�܂Ƃ߂�邯�ǂ܂Ƃ߂�ł��ǂ߂邩�炱�̂܂܂ɂ���B
	for (int i = 0; i < my_bullet.size(); i++)
		my_bullet[i]->Draw();
	my_shield->Draw();
	my_ship->Draw();
	for (int i = 0; i < enemy_bullet.size(); i++)
		enemy_bullet[i]->Draw();
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

void CreateEnemy() {
	//�f�o�b�O�p�ɓG��ʎY
	//if (main_count % 30 == 0)
	//	enemy_ship.push_back(new testNCircle(main_count % 640, -10, 200, 16, PI / 2, 3));
	//�f�o�b�O�p �̃e�X�g
	//if (main_count % 2000 == 0)
	//	enemy_ship.push_back(new testNWay(320, 200, 200, 16, 3.141592 / 2, 0));
	while (enemy_pattern.empty() == false) {
		if (main_count == enemy_pattern[0]->count) {
			int x = enemy_pattern[0]->x;
			int y = enemy_pattern[0]->y;
			int z = enemy_pattern[0]->z;
			switch (enemy_pattern[0]->number) {
			//1000�ԑ�̓f�o�b�O�p�Œ�
			case 1000:enemy_ship.push_back(new testSpiralShotPattern(		x, y, z, 16, PI / 2, 0)); break;
			case 1001:enemy_ship.push_back(new testMultiSpiralShotPatten(	x, y, z, 16, PI / 2, 0)); break;
			case 1002:enemy_ship.push_back(new testBothSpiralShotPatten(	x, y, z, 16, PI / 2, 0)); break;
			case 1003:enemy_ship.push_back(new testNWay(					x, y, z, 16, PI / 2, 0)); break;
			case 1004:enemy_ship.push_back(new testNCircle(					x, y, z, 16, PI / 2, 0)); break;
			//2000�ԑ�̓f�o�b�O�p����
			case 2000:enemy_ship.push_back(new testSpiralShotPattern(		x, y, z, 16, PI / 2, 3)); break;
			case 2001:enemy_ship.push_back(new testMultiSpiralShotPatten(	x, y, z, 16, PI / 2, 3)); break;
			case 2002:enemy_ship.push_back(new testBothSpiralShotPatten(	x, y, z, 16, PI / 2, 3)); break;
			case 2003:enemy_ship.push_back(new testNWay(	x, y, z, 16, PI / 2, 3)); break;
			case 2004:enemy_ship.push_back(new testNCircle(	x, y, z, 16, PI / 2, 3)); break;
			//3000�ԑ�͎G���G
			case 3000:enemy_ship.push_back(new xLV(			x, y, z, 16, PI / 2, 3)); break;
			case 3001:enemy_ship.push_back(new inFront(		x, y, z, 16, PI / 2, 3)); break;
			case 3002:enemy_ship.push_back(new slalomFront(	x, y, z, 16, PI / 2, 3)); break;
			case 3003:enemy_ship.push_back(new cutInLeft(	x, y, z, 16, PI / 4, 3)); break;
			case 3004:enemy_ship.push_back(new cutInRight(	x, y, z, 16, PI / 4*3, 3)); break;
			case 3005:enemy_ship.push_back(new cutInUp(		x, 500, 100, 16, PI / 2*3, 3)); break;
			case 3006:enemy_ship.push_back(new cutInDown(	x, 500, 300, 16, PI / 2*3, 3)); break;
			default:
				assert(false);
				break; 
			}
			enemy_pattern.erase(enemy_pattern.begin());
		}
		else
			break;
	}
}

void InitGame() {
	game_mode = GAME_MAIN;
	main_count = 0;

	fps = new fpsManager(60);
	image = new imagesManager();
	key = new cKey();

	my_ship = new myShip(320, 400, 200, 8, 0, 5);
	my_shield = new myShield(my_ship->x, my_ship->y, my_ship->z, 0, 0, 0);
}

void EndGame() {
	enemy_bullet.clear();
	enemy_ship.clear();
	my_bullet.clear();
	delete my_shield;
	delete my_ship;
}