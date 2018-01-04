#include "ImageManager.h"

imageManager::imageManager(const char* file_name, float expansion_rate) {
	this->expansion_rate = expansion_rate;
	image_handle = LoadGraph(file_name);
}

imageManager::~imageManager() {
	DeleteGraph(image_handle);
}

void imageManager::Draw(const int x, const int y, const float z, const float angle) {
	float tmp_z = 200 / z;
	DrawRotaGraph(x, y, tmp_z * expansion_rate, angle, image_handle, TRUE, FALSE);
}