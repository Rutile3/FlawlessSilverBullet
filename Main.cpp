#pragma warning(disable:4996)

#include "Main.h"

using namespace std;

class cPattern {
public:
	cPattern(int count, int number, int x, int y, int z) {
		this->count = count;
		this->number = number;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	int count, number, x, y, z;
};
vector<cPattern*> enemy_pattern;
vector<cPattern*> effect_pattern;

void Calc();
void Collision();
void CreateEffect();
void CreateEnemy();
void Draw();
void DrawSub(int lower_limits, int upper_limits);
void EndGame();
bool ReadPattern(char* file, vector<cPattern*> &ve);
void GameMain();
void OutSide();
void OutSideSub(vector<cMover*> &ve);
bool InitDxLibrary();
void InitGame();
void Title();

int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC) {
	if (InitDxLibrary() == false) return -1;
	InitGame();

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
	DxLib_End();

	return 0;
}

void Title() {
	image->Draw(320, 240, 200, 0, TITLE_4);
	image->Draw(320, 120, 200, 0, TITLE_2);
	image->Draw(320, 400, 200, 0, TITLE_3);

	if (key->z->Push() == true) {
		game_mode = GAME_MAIN;
		main_count = -1;//mainのほうで1加算されるので
		sound->Play(ENTER);
		stage = 0;
		ReadPattern("media/EnemyPattern.csv", enemy_pattern);
		ReadPattern("media/EffectPattern1.csv", effect_pattern);
	}
}

void GameMain() {
	Calc();
	CreateEnemy();
	CreateEffect();
	Collision();
	OutSide();
	Draw();
}

void Calc() {
	//自機->自機シールド->自弾->敵機->敵弾->エフェクト
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
	for (int i = 0; i != effect.size(); i++)
		effect[i]->Calc();
}

//引数で面を指定できるようにする。
bool ReadPattern(char* file, vector<cPattern*> &pattern) {
	FILE *fp;
	int count, number, x, y, z;
	char buf[50];

	pattern.clear();
	if ((fp = fopen(file, "r")) == NULL)return false;
	if (fscanf(fp, "%s\n", buf) == EOF)					return false;
	while (true) {
		if (fscanf(fp, "%[,]", buf) == EOF)										break;
		if (fscanf(fp, "%d,%d,%d,%d,%d\n", &count, &number, &x, &y, &z) == EOF)	break;
		pattern.push_back(new cPattern(count, number, x, y, z));
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
	OutSideSub(effect);
}

void OutSideSub(vector<cMover*> &ve) {
	//forだと全網羅できないがしなくてもそれほど問題ないし煩雑になるのでいまはこれでいい
	for (int i = 0; i < ve.size(); i++)
		if (ve[i]->OutSide())
			ve.erase(ve.begin() + i);
}

void Draw() {
	//デバッグ用
	//printfDx("es = %d\n", enemy_ship.size());
	//printfDx("eb = %d\n", enemy_bullet.size());
	//printfDx("mb = %d\n", my_bullet.size());
	//printfDx("main_count = %d\n", main_count);
	DrawSub(500, 600);
	DrawSub(400, 500);
	DrawSub(300, 400);
	DrawSub(200, 300);
	for (int i = 0; i < my_bullet.size(); i++)
		my_bullet[i]->Draw();
	my_shield->Draw();
	my_ship->Draw();
	DrawSub(0, 200);

}

void DrawSub(int lower_limits, int upper_limits) {
	//敵機->エフェクト->自弾->自機シールド->自機->敵弾
	for (int i = 0; i < enemy_ship.size(); i++)
		enemy_ship[i]->Draw(lower_limits, upper_limits);//まとめれるけどまとめんでも読めるからこのままにする。
	for (int i = 0; i < effect.size(); i++)
		effect[i]->Draw(lower_limits,upper_limits);
	for (int i = 0; i < enemy_bullet.size(); i++)
		enemy_bullet[i]->Draw(lower_limits, upper_limits);
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

void CreateEffect() {
	while (effect_pattern.empty() == false) {
		if (main_count == effect_pattern[0]->count) {
			int x = effect_pattern[0]->x;
			int y = effect_pattern[0]->y;
			int z = effect_pattern[0]->z;
			switch (effect_pattern[0]->number) {
				//100番台はデバッグコマンド
			case 100:main_count = 0;	break;
			case 101:main_count = 1000;	break;
			case 102:main_count = 2000; break;
			case 103:main_count = 3000; break;
			case 104:main_count = 4000; break;
			case 105:main_count = 5000; break;
			case 106:main_count = 6000; break;
			case 107:main_count = 7000; break;
			case 108:main_count = 8000; break;
			case 109:main_count = 9000;	break;
			case 110:main_count = 10000; break;
			case 111:main_count = 11000; break;
			case 112:main_count = 12000; break;
			case 113:main_count = 13000; break;
			case 114:main_count = 14000; break;
			case 115:main_count = 15000; break;
			case 116:main_count = 16000; break;
			case 117:main_count = 17000; break;
			case 118:main_count = 18000; break;
			case 119:main_count = 19000; break;
			//1000番台は背景
			case 1000:BackGround(500, 0.1f, BACK010, 960);	break;
			case 1001:BackGround(300, 10, BACK011, 3000);	break;
			//2000番台はBGM
			case 2000:sound->Play(BGM01); break;
			case 2001:sound->Stop(BGM01); break;
			default:
				assert(false);
				break;
			}
			effect_pattern.erase(effect_pattern.begin());
		}
		else if (main_count > effect_pattern[0]->count) {
			effect_pattern.erase(effect_pattern.begin());
		}
		else
			break;
	}
}

void CreateEnemy() {
	while (enemy_pattern.empty() == false) {
		if (main_count == enemy_pattern[0]->count) {
			int x = enemy_pattern[0]->x;
			int y = enemy_pattern[0]->y;
			int z = enemy_pattern[0]->z;
			switch (enemy_pattern[0]->number) {
			//100番台はデバッグコマンド
			case 100:main_count = 0;	break;
			case 101:main_count = 1000;	break;
			case 102:main_count = 2000; break;
			case 103:main_count = 3000; break;
			case 104:main_count = 4000; break;
			case 105:main_count = 5000; break;
			case 106:main_count = 6000; break;
			case 107:main_count = 7000; break;
			case 108:main_count = 8000; break;
			case 109:main_count = 9000;	break;
			case 110:main_count = 10000;break;
			case 111:main_count = 11000;break;
			case 112:main_count = 12000;break;
			case 113:main_count = 13000;break;
			case 114:main_count = 14000;break;
			case 115:main_count = 15000;break;
			case 116:main_count = 16000;break;
			case 117:main_count = 17000;break;
			case 118:main_count = 18000;break;
			case 119:main_count = 19000;break;
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
			case 3000:enemy_ship.push_back(new xLV(			x, y, 200, 16, PI / 2, 3)); break;
			case 3001:enemy_ship.push_back(new inFront(		x, y, 200, 12, PI / 2, 3, ENEMY_SHIP030)); break;
			case 3002:enemy_ship.push_back(new slalomFront(	x, y, 200, 12, PI / 2, 3, ENEMY_SHIP030)); break;
			case 3003:enemy_ship.push_back(new cutInLeft(	x, y, 200, 16, PI / 4, 4)); break;
			case 3004:enemy_ship.push_back(new cutInRight(	x, y, 200, 16, PI / 4 * 3, 4)); break;
			case 3005:enemy_ship.push_back(new cutInUp(		x, 500, 100, 16, PI / 2 * 3, 4)); break;
			case 3006:enemy_ship.push_back(new cutInDown(	x, 500, 300, 16, PI / 2 * 3, 4)); break;
			case 3007:enemy_ship.push_back(new easyInvaders(x, y, 200, 16, PI / 2, 6, ENEMY_SHIP020, 2000, 200)); break;
			case 3008:enemy_ship.push_back(new hoverShooter(x, y, 200, 16, PI / 2, 3, ENEMY_SHIP040)); break;
				//4000番台はボス
			case 4005:enemy_ship.push_back(new virtualBug(x, y, 200, 32, PI / 2, 3, ENEMY_SHIP050, 100000, 5000)); break;
			case 4006:enemy_ship.push_back(new wyvernUnder(320, 600, 300, 32, PI * 3 / 2, 1, ENEMY_SHIP060)); break;
			case 4007:enemy_ship.push_back(new cWyvern(320, 100, 200, 32, PI * 3 / 2, 3, ENEMY_SHIP060, 50000, 5000)); break;

			default:
				assert(false);
				break; 
			}
			enemy_pattern.erase(enemy_pattern.begin());
		}
		else if (main_count > enemy_pattern[0]->count) {
			enemy_pattern.erase(enemy_pattern.begin());
		}
		else
			break;
	}
}

void InitGame() {
	game_mode = TITLE;
	main_count = 0;
	stage = 0;
	ReadPattern("media/EnemyPattern.csv", enemy_pattern);
	ReadPattern("media/EffectPattern1.csv", effect_pattern);

	fps = new fpsManager(60);
	image = new imagesManager();
	sound = new soundsManager();
	key = new keysManager();

	my_ship = new myShip(320, 400, 200, 8, 0, 6);
	my_shield = new myShield(my_ship->x, my_ship->y, my_ship->z, 0, 0, 0,MY_SHIELD_0);
}

void EndGame() {
	enemy_pattern.clear();
	effect_pattern.clear();
	effect.clear();
	enemy_bullet.clear();
	enemy_ship.clear();
	my_bullet.clear();
	delete my_shield;
	delete my_ship;
	delete fps;
	//delete image;//なんでかメモリーリークに失敗する。
	delete key;
	//delete sound;
}