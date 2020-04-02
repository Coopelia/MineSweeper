#pragma once
#include"Def.h"

class MyClock
{
public:
	int hour;
	int minute;
	int second;
	float elapsedTime;
	bool isRun;
	clock_t beginTime, endTime;
	MyClock();
	void updata();
	void start();
	void stop();
};