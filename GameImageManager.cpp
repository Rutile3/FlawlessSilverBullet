#include "GameImageManager.h"

imagesManager::imagesManager() {
	image[TITLE_1] = new imageManager("media/Image/Title1.png");
	image[TITLE_2] = new imageManager("media/Image/Title2.png");
	image[TITLE_3] = new imageManager("media/Image/Title3.png");

	image[MY_SHIP_0] = new imageManager("media/Image/MyShip0.png");
	image[MY_SHIP_1] = new imageManager("media/Image/MyShip1.png");
	image[MY_SHIP_2] = new imageManager("media/Image/MyShip2.png");

	image[MY_SHIELD_0] = new imageManager("media/Image/Myshield0.png", 4.57f);

	image[LIFE1] = new imageManager("media/Image/Life1.png", 2);

	image[MY_BULLET000] = new imageManager("media/Image/MyBullet000.png");
	image[MY_BULLET001] = new imageManager("media/Image/MyBullet001.png");
	image[MY_BULLET002] = new imageManager("media/Image/MyBullet002.png");

	image[ENEMY_SHIP010] = new imageManager("media/Image/Enemy010.png", 1.5f);
	image[ENEMY_SHIP020] = new imageManager("media/Image/Enemy020.png", 1.5f);
	image[ENEMY_SHIP030] = new imageManager("media/Image/Enemy030.png", 1.5f);
	image[ENEMY_SHIP040] = new imageManager("media/Image/Enemy040.png", 1.5f);
	image[ENEMY_SHIP050] = new imageManager("media/Image/Enemy050.png", 1.5f);
	image[ENEMY_SHIP060] = new imageManager("media/Image/Enemy060.png", 1.5f);
	image[ENEMY_SHIP070] = new imageManager("media/Image/Enemy070.png", 1.5f);

	image[ENEMY_BULLET01] = new imageManager("media/Image/Bullet01.png", 2);
	image[ENEMY_BULLET02] = new imageManager("media/Image/Bullet02.png", 2);
	image[ENEMY_BULLET03] = new imageManager("media/Image/Bullet03.png", 2);
	image[ENEMY_BULLET04] = new imageManager("media/Image/Bullet04.png", 1.7f);
	image[ENEMY_BULLET05] = new imageManager("media/Image/Bullet05.png", 1.7f);
	image[ENEMY_BULLET06] = new imageManager("media/Image/Bullet06.png", 1.7f);
	image[ENEMY_BULLET07] = new imageManager("media/Image/Bullet07.png", 1.14f);
	image[ENEMY_BULLET08] = new imageManager("media/Image/Bullet08.png", 1.14f);
	image[ENEMY_BULLET09] = new imageManager("media/Image/Bullet09.png", 1.14f);

	image[BACK010] = new imageManager("media/Image/Back010.png");
	image[BACK011] = new imageManager("media/Image/Back011.png");

	image[EFFECT010] = new imageManager("media/Image/Effect010.png");
	image[EFFECT011] = new imageManager("media/Image/Effect011.png");
	image[EFFECT012] = new imageManager("media/Image/Effect012.png");
	image[EFFECT013] = new imageManager("media/Image/Effect013.png");
	image[EFFECT014] = new imageManager("media/Image/Effect014.png");
	image[EFFECT015] = new imageManager("media/Image/Effect015.png");
	image[EFFECT016] = new imageManager("media/Image/Effect016.png");
	image[EFFECT017] = new imageManager("media/Image/Effect017.png");
	image[EFFECT018] = new imageManager("media/Image/Effect018.png");
	image[EFFECT019] = new imageManager("media/Image/Effect019.png");
	image[EFFECT020] = new imageManager("media/Image/Effect020.png");
	image[EFFECT021] = new imageManager("media/Image/Effect021.png");
	image[EFFECT030] = new imageManager("media/Image/Effect030.png");
	image[EFFECT031] = new imageManager("media/Image/Effect031.png");
	image[EFFECT032] = new imageManager("media/Image/Effect032.png");
	image[EFFECT033] = new imageManager("media/Image/Effect033.png");
	image[EFFECT034] = new imageManager("media/Image/Effect034.png");
	image[EFFECT035] = new imageManager("media/Image/Effect035.png");
	image[EFFECT036] = new imageManager("media/Image/Effect036.png");
	image[EFFECT037] = new imageManager("media/Image/Effect037.png");
	image[EFFECT038] = new imageManager("media/Image/Effect038.png");
	image[EFFECT039] = new imageManager("media/Image/Effect039.png");

	//読み込みが完全かチェックしたほうがいい
	for (int i = 0; i < MAX_IMAGES_SIZE; i++) {

	}
}

imagesManager::~imagesManager() {
	delete[] image;
}

void imagesManager::Draw(const int x, const int y, const float expansion_rate, const float angle, const int file_name) {
	image[file_name]->Draw(x, y, expansion_rate, angle);
}