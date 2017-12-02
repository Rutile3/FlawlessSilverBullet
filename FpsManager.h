#ifndef _INCLUDE_FPS_
#define _INCLUDE_FPS_
#include <DxLib.h>

class fpsManager{
public:
	fpsManager(int);
	~fpsManager();
	void Update();
	void Draw(bool);
	void Wait();

private:
	int start_time_ms;
	int count;
	double fps;
	int target_fps;//–Ú“I‚ÌFPS
};

#endif