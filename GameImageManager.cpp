#include "GameImageManager.h"

ImagesManager::ImagesManager() {
	image[MY_SHIP_1] = new imageManager("media/MyShip1.png");
}

ImagesManager::~ImagesManager() {
	delete[] image;
}

void ImagesManager::Draw(const int x, const int y, const float expansion_rate, const float angle, const int file_name) {
	image[file_name]->Draw(x, y, expansion_rate, angle);
}