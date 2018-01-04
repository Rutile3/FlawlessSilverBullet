#include "GameImageManager.h"

imagesManager::imagesManager() {
	image[MY_SHIP_0] = new imageManager("media/MyShip0.png");

	image[MY_BULLET000] = new imageManager("media/MyBullet000.png");
	image[MY_BULLET001] = new imageManager("media/MyBullet001.png");
	image[MY_BULLET002] = new imageManager("media/MyBullet002.png");

	image[ENEMY_SHIP010] = new imageManager("media/Enemy010.png", 1.5f);

	image[ENEMY_BULLET010] = new imageManager("media/Bullet010.png");
	image[ENEMY_BULLET011] = new imageManager("media/Bullet011.png");
	image[ENEMY_BULLET012] = new imageManager("media/Bullet012.png");
	image[ENEMY_BULLET013] = new imageManager("media/Bullet013.png");
	image[ENEMY_BULLET014] = new imageManager("media/Bullet014.png");
	image[ENEMY_BULLET015] = new imageManager("media/Bullet015.png");
}

imagesManager::~imagesManager() {
	delete[] image;
}

void imagesManager::Draw(const int x, const int y, const float expansion_rate, const float angle, const int file_name) {
	image[file_name]->Draw(x, y, expansion_rate, angle);
}