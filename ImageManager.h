#ifndef _IMAGE_MANAGER_
#define _IMAGE_MANAGER_

#include <DxLib.h>

class imageManager {
public:
	imageManager(const char* file_name, float expansion_rate = 1);
	~imageManager();

	void Draw(const int x, const int y, const float expansion_rate, const float angle);

private:
	int expansion_rate;
	int image_handle;
};

#endif