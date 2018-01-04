#ifndef _GAME_IMAGE_MANAGER_
#define _GAME_IMAGE_MANAGER_

#include "ImageManager.h"

enum {
	MY_SHIP_1,
	MAX_IMAGES_SIZE
};

class ImagesManager {
public:
	ImagesManager();
	~ImagesManager();

	void Draw(const int x, const int y, const float expansion_rate, const float angle, const int file_name);

private:
	imageManager* image[MAX_IMAGES_SIZE];
};



#endif