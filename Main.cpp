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

	//そのうち移す
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
	//自機->自機シールド->自弾->敵機->敵弾
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

//引数で面を指定できるようにする。
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
	//敵弾->シールドと自機
	for (int i = 0; i < enemy_bullet.size(); i++) {
		enemy_bullet[i]->Hit(my_shield);
		enemy_bullet[i]->Hit(my_ship);
	}
	//敵機->自弾と自機
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
	//forだと全網羅できないがしなくてもそれほど問題ないし煩雑になるのでいまはこれでいい
	for (int i = 0; i < ve.size(); i++)
		if (ve[i]->OutSide())
			ve.erase(ve.begin() + i);
}

void Draw() {
	//デバッグ用
	printfDx("es = %d\n", enemy_ship.size());
	printfDx("eb = %d\n", enemy_bullet.size());
	printfDx("mb = %d\n", my_bullet.size());

	//敵機->自弾->自機シールド->自機->敵弾
	for (int i = 0; i < enemy_ship.size(); i++)
		enemy_ship[i]->Draw();//まとめれるけどまとめんでも読めるからこのままにする。
	for (int i = 0; i < my_bullet.size(); i++)
		my_bullet[i]->Draw();
	my_shield->Draw();
	my_ship->Draw();
	for (int i = 0; i < enemy_bullet.size(); i++)
		enemy_bullet[i]->Draw();
}

bool InitDxLibrary() {
	SetAlwaysRunFlag(TRUE);								//ウインドウがアクティブじゃなくても動かす
	SetOutApplicationLogValidFlag(FALSE);				//ログを出力をしない
	SetMainWindowText("FlawlessSilverBullet");			//フォームの名前

	ChangeWindowMode(TRUE);		//FALSEで全画面
	SetGraphMode(640, 480, 32);	//スクリーンの大きさ

	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void CreateEnemy() {
	//デバッグ用に敵を量産
	//if (main_count % 30 == 0)
	//	enemy_ship.push_back(new testNCircle(main_count % 640, -10, 200, 16, PI / 2, 3));
	//デバッグ用 個体テスト
	//if (main_count % 2000 == 0)
	//	enemy_ship.push_back(new testNWay(320, 200, 200, 16, 3.141592 / 2, 0));
	while (enemy_pattern.empty() == false) {
		if (main_count == enemy_pattern[0]->count) {
			int x = enemy_pattern[0]->x;
			int y = enemy_pattern[0]->y;
			int z = enemy_pattern[0]->z;
			switch (enemy_pattern[0]->number) {
			//1000番台はデバッグ用固定
			case 1000:enemy_ship.push_back(new testSpiralShotPattern(		x, y, z, 16, PI / 2, 0)); break;
			case 1001:enemy_ship.push_back(new testMultiSpiralShotPatten(	x, y, z, 16, PI / 2, 0)); break;
			case 1002:enemy_ship.push_back(new testBothSpiralShotPatten(	x, y, z, 16, PI / 2, 0)); break;
			case 1003:enemy_ship.push_back(new testNWay(					x, y, z, 16, PI / 2, 0)); break;
			case 1004:enemy_ship.push_back(new testNCircle(					x, y, z, 16, PI / 2, 0)); break;
			//2000番台はデバッグ用動く
			case 2000:enemy_ship.push_back(new testSpiralShotPattern(		x, y, z, 16, PI / 2, 3)); break;
			case 2001:enemy_ship.push_back(new testMultiSpiralShotPatten(	x, y, z, 16, PI / 2, 3)); break;
			case 2002:enemy_ship.push_back(new testBothSpiralShotPatten(	x, y, z, 16, PI / 2, 3)); break;
			case 2003:enemy_ship.push_back(new testNWay(	x, y, z, 16, PI / 2, 3)); break;
			case 2004:enemy_ship.push_back(new testNCircle(	x, y, z, 16, PI / 2, 3)); break;
			//3000番台は雑魚敵
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