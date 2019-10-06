#pragma once
#include <fstream>
#include <sstream>
#include "FPSCounter.h"

class TimeBaseLoopExecuter
{
public:
	TimeBaseLoopExecuter(double frame = 60.0):FRAME_TIME(1.0f / frame)
	{
		mFpsCountor = std::make_unique<FPSCounter>();
	}
	//FPSを固定するため処理時間に余裕がある場合その分待つ
	void TimeAdjustment();
	//FPSを取得
	double GetFPS() { return mFps; }
private:
	double mFps = 0;
	const double FRAME_TIME = 0.0;
	double mFrameTime = 0.0;
	std::unique_ptr<FPSCounter> mFpsCountor;

#ifdef _DEBUG
public:
private:
	int mFrameCount = 0;
	int mDebugCount = 10;
#endif // _DEBUG

};

