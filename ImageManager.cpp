#include "ImageManager.h"

imageManager::imageManager(const char* file_name) {
	image_handle = LoadGraph(file_name);
}

imageManager::~imageManager() {
	DeleteGraph(image_handle);
}

void imageManager::Draw(const int x, const int y, const float expansion_rate, const float angle) {
	DrawRotaGraph(x,y,expansion_rate,angle,image_handle,TRUE,FALSE);
}