#ifndef _GAME_IMAGE_MANAGER_
#define _GAME_IMAGE_MANAGER_

#include "ImageManager.h"

enum {
	MY_SHIP_0,

	MY_BULLET000,
	MY_BULLET001,
	MY_BULLET002,

	ENEMY_SHIP010,

	ENEMY_BULLET01,
	ENEMY_BULLET02,
	ENEMY_BULLET03,
	ENEMY_BULLET04,
	ENEMY_BULLET05,
	ENEMY_BULLET06,
	ENEMY_BULLET07,
	ENEMY_BULLET08,
	ENEMY_BULLET09,
	MAX_IMAGES_SIZE
};

class imagesManager {
public:
	imagesManager();
	~imagesManager();

	void Draw(const int x, const int y, const float z, const float angle, const int file_name);

private:
	imageManager* image[MAX_IMAGES_SIZE];
};

#endif