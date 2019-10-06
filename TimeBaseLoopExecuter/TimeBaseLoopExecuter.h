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
	//FPS���Œ肷�邽�ߏ������Ԃɗ]�T������ꍇ���̕��҂�
	void TimeAdjustment();
	//FPS���擾
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

