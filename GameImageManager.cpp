#include "GameImageManager.h"

imagesManager::imagesManager() {
	image[MY_SHIP_0] = new imageManager("media/MyShip0.png");

	image[MY_BULLET000] = new imageManager("media/MyBullet000.png");
	image[MY_BULLET001] = new imageManager("media/MyBullet001.png");
	image[MY_BULLET002] = new imageManager("media/MyBullet002.png");

	image[ENEMY_SHIP010] = new imageManager("media/Enemy010.png", 1.5f);

	image[ENEMY_BULLET01] = new imageManager("media/Bullet01.png");
	image[ENEMY_BULLET02] = new imageManager("media/Bullet02.png");
	image[ENEMY_BULLET03] = new imageManager("media/Bullet03.png");
	image[ENEMY_BULLET04] = new imageManager("media/Bullet04.png");
	image[ENEMY_BULLET05] = new imageManager("media/Bullet05.png");
	image[ENEMY_BULLET06] = new imageManager("media/Bullet06.png");
	image[ENEMY_BULLET07] = new imageManager("media/Bullet07.png");
	image[ENEMY_BULLET08] = new imageManager("media/Bullet08.png");
	image[ENEMY_BULLET09] = new imageManager("media/Bullet09.png");
}

imagesManager::~imagesManager() {
	delete[] image;
}

void imagesManager::Draw(const int x, const int y, const float expansion_rate, const float angle, const int file_name) {
	image[file_name]->Draw(x, y, expansion_rate, angle);
}