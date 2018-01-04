#ifndef _GAME_IMAGE_MANAGER_
#define _GAME_IMAGE_MANAGER_

#include "ImageManager.h"

enum {
	MY_SHIP_0,

	MY_BULLET000,
	MY_BULLET001,
	MY_BULLET002,

	ENEMY_SHIP010,

	ENEMY_BULLET010,
	ENEMY_BULLET011,
	ENEMY_BULLET012,
	ENEMY_BULLET013,
	ENEMY_BULLET014,
	ENEMY_BULLET015,
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