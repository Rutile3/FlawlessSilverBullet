#include "Main.h"

using namespace std;

void Calc();
void Collision();
void CollisionEnemyBullet();
void CollisionEnemyShip();
void CreateEnemy();
void Draw();
void EndGame();
void GameMain();
void OutSide();
void OutSideJudge(vector<cMover*> &ve);
bool InitDxLibrary();

int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC) {
	if (InitDxLibrary() == false) return -1;
	main_count = 0;
	fps = new fpsManager(60);
	key = new cKey();
	my_ship = new myShip(320, 400, 200, 12, 0, 5);
	my_shield = new myShield(my_ship->x,my_ship->y,my_ship->z,0,0,0);

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

//本来ならファイルから読み出す
void CreateEnemy() {
	//デバッグ用に敵を量産
	if (main_count % 30 == 0)
		enemy_ship.push_back(new testBothSpiralShotPatten(main_count % 640, -10, 200, 16, 3.141592 / 2, 3));
	//デバッグ用 個体テスト
	//if (main_count % 2000 == 0)
	//	enemy_ship.push_back(new testBothSpiralShotPatten(320, 200, 200, 16, 3.141592 / 2, 0));
}

void Collision() {
	CollisionEnemyBullet();
	CollisionEnemyShip();
}

//敵弾->シールドと自機
void CollisionEnemyBullet() {
	unsigned int eb_i = 0;
	while (eb_i < enemy_bullet.size()) {
		if (enemy_bullet[eb_i]->Hit(my_shield)) {
			//想定してしる処理
			//敵弾が極太レーザーか
			//->敵弾と同じエフェクトを生成
			//その他
			//->敵弾と同じ自弾を生成
			//敵弾を削除
			enemy_bullet.erase(enemy_bullet.begin() + eb_i);//上の処理を簡略化
			continue;
		}
		else if (enemy_bullet[eb_i]->Hit(my_ship)) {
			//想定している処理
			//自機の残機を減らす
			//自機を無敵にする
			//敵弾が貫通弾か
			//->敵弾を削除する
			enemy_bullet.erase(enemy_bullet.begin() + eb_i);//上の2つを簡略化
			continue;
		}
		eb_i++;
	}
}

//敵機->自弾と自機
void CollisionEnemyShip() {
	//敵機->自弾
EnemyShip_Collision_MyBullet:
	unsigned int es_i = 0;//enemy_ship_iの略
	while (es_i < enemy_ship.size()) {
		unsigned int mb_i = 0;
		while (mb_i < my_bullet.size()) {//敵を消した後終端になる可能性があるから
			if (enemy_ship[es_i]->Hit(my_bullet[mb_i])) {
				//想定している処理
				//敵機に自弾分のダメージ
				//敵機の生存確認
				//->敵機を削除
				enemy_ship.erase(enemy_ship.begin() + es_i);//上の3つを簡略化
				//自弾が通常弾か
				//->自弾を削除削除
				my_bullet.erase(my_bullet.begin() + mb_i);
				goto EnemyShip_Collision_MyBullet;
			}
			mb_i++;
		}
		es_i++;
	}

	//敵機->自機
	es_i = 0;
	while (es_i < enemy_ship.size()) {
		if (enemy_ship[es_i]->Hit(my_ship)) {
			//想定してる処理
			//敵機に固定ダメージ
			//敵機生存確認
			//->敵機を削除
			enemy_ship.erase(enemy_ship.begin() + es_i);//上の3つを簡略化
			//自機の残機を減らす
			//自機を無敵にする
			continue;
		}
		es_i++;
	}
}

void OutSide() {
	OutSideJudge(my_bullet);
	OutSideJudge(enemy_bullet);
	OutSideJudge(enemy_ship);
}

void OutSideJudge(vector<cMover*> &ve) {//ポインタにしたほうがいい
	unsigned int i = 0;
	while (i < ve.size()) {
		if (ve[i]->x > 640 + 50 ||
			ve[i]->y > 480 + 50 || 
			ve[i]->x < -50 ||
			ve[i]->y < -50) {
			ve.erase(ve.begin() + i);
			continue;
		}
		i++;
	}
}

void Draw() {
	//デバッグ用
	printfDx("es = %d\n", enemy_ship.size());
	printfDx("eb = %d\n", enemy_bullet.size());
	printfDx("mb = %d\n", my_bullet.size());

	//敵機->自弾->自機シールド->自機->敵弾
	for (int i = 0; i < enemy_ship.size(); i++)
		enemy_ship[i]->Draw();
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
	SetMainWindowText("苛烈弾幕");						//ゲームごとに手動でかえる -> どうにかならんか

	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);	//スクリーンの大きさ

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