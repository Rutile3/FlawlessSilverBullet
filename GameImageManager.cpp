#include "GameImageManager.h"

imagesManager::imagesManager() {
	image[MY_SHIP_0] = new imageManager("media/MyShip0.png");

	image[MY_BULLET000] = new imageManager("media/MyBullet000.png");
	image[MY_BULLET001] = new imageManager("media/MyBullet001.png");
	image[MY_BULLET002] = new imageManager("media/MyBullet002.png");

	image[ENEMY_SHIP010] = new imageManager("media/Enemy010.png", 1.5f);
	image[ENEMY_SHIP020] = new imageManager("media/Enemy020.png", 1.5f);
	image[ENEMY_SHIP030] = new imageManager("media/Enemy030.png", 1.5f);
	image[ENEMY_SHIP040] = new imageManager("media/Enemy040.png", 1.5f);

	image[ENEMY_BULLET01] = new imageManager("media/Bullet01.png", 2);
	image[ENEMY_BULLET02] = new imageManager("media/Bullet02.png", 2);
	image[ENEMY_BULLET03] = new imageManager("media/Bullet03.png", 2);
	image[ENEMY_BULLET04] = new imageManager("media/Bullet04.png", 1.7f);
	image[ENEMY_BULLET05] = new imageManager("media/Bullet05.png", 1.7f);
	image[ENEMY_BULLET06] = new imageManager("media/Bullet06.png", 1.7f);
	image[ENEMY_BULLET07] = new imageManager("media/Bullet07.png", 1.14f);
	image[ENEMY_BULLET08] = new imageManager("media/Bullet08.png", 1.14f);
	image[ENEMY_BULLET09] = new imageManager("media/Bullet09.png", 1.14f);

	image[BACK010] = new imageManager("media/Back010.png");
	image[BACK011] = new imageManager("media/Back011.png");

	image[EFFECT010] = new imageManager("media/Effect010.png");
	image[EFFECT011] = new imageManager("media/Effect011.png");
	image[EFFECT012] = new imageManager("media/Effect012.png");
	image[EFFECT013] = new imageManager("media/Effect013.png");
	image[EFFECT014] = new imageManager("media/Effect014.png");
	image[EFFECT015] = new imageManager("media/Effect015.png");
	image[EFFECT016] = new imageManager("media/Effect016.png");
	image[EFFECT017] = new imageManager("media/Effect017.png");
	image[EFFECT018] = new imageManager("media/Effect018.png");
	image[EFFECT019] = new imageManager("media/Effect019.png");
	image[EFFECT020] = new imageManager("media/Effect020.png");
	image[EFFECT021] = new imageManager("media/Effect021.png");
	image[EFFECT030] = new imageManager("media/Effect030.png");
	image[EFFECT031] = new imageManager("media/Effect031.png");
	image[EFFECT032] = new imageManager("media/Effect032.png");
	image[EFFECT033] = new imageManager("media/Effect033.png");
	image[EFFECT034] = new imageManager("media/Effect034.png");
	image[EFFECT035] = new imageManager("media/Effect035.png");
	image[EFFECT036] = new imageManager("media/Effect036.png");
	image[EFFECT037] = new imageManager("media/Effect037.png");
	image[EFFECT038] = new imageManager("media/Effect038.png");
	image[EFFECT039] = new imageManager("media/Effect039.png");

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