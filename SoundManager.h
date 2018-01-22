#ifndef _INCLUDE_SOUND_IMAGMANAGER_
#define _INCLUDE_SOUND_IMAGMANAGER_

#include <DxLib.h>
#include <assert.h>

class soundManager{
public:
	soundManager(const char* file_name, const bool this_handle_se = true);
	~soundManager();
	void Play();
	void Stop();

private:
	int handle;
	bool this_handle_se;
};

#endif