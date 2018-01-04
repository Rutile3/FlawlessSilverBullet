#ifndef _IMAGE_MANAGER_
#define _IMAGE_MANAGER_

#include <DxLib.h>
#include <vector>

class imageManager {
public:
	imageManager(const char* file_name);
	~imageManager();

	void Draw(const int x, const int y, const float expansion_rate, const float angle);

private:
	int image_handle;
};

#endif