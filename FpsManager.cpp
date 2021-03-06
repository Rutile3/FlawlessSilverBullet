#include "Fpsmanager.h"

fpsManager::fpsManager(int target_fps){//できればtarget_value_fps以外でいい言葉探してる
	start_time_ms = 0;
	count = 0;
	fps = 0;
	this->target_fps = target_fps;
}

fpsManager::~fpsManager(){

}

void fpsManager::Update(){
	if (count == 0)
		start_time_ms = GetNowCount();
	else if (count == target_fps){
		int end_time_ms = GetNowCount();
		fps = 1000.0 / ((end_time_ms - start_time_ms) / (double)target_fps);//???
		count = 0;
		start_time_ms = end_time_ms;
	}
	count++;
}

void fpsManager::Draw(bool draw_string){
	if(draw_string == true)
		DrawFormatString(600, 460, GetColor(255, 255, 255), "%.1lf", fps);
}	//色の変数作ったほうがいい

void fpsManager::Wait(){
	int tmp_time_ms = GetNowCount() - start_time_ms;
	int wait_time_ms = count * 1000 / target_fps - tmp_time_ms;//???
	if (wait_time_ms > 0)
		Sleep(wait_time_ms);
}