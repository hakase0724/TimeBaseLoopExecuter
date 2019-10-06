#include "TimeBaseLoopExecuter.h"

void TimeBaseLoopExecuter::TimeAdjustment()
{
	//差分時間を取得
	mFrameTime = mFpsCountor->GetDefTime();
	//処理時間に余裕がある場合はその分待つ
	if (mFrameTime < FRAME_TIME)
	{
		//Sleepの時間を計算
		//s→ms変換のため*1000
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - mFrameTime) * 1000);
		//寝る
		Sleep(sleepTime);
	}
	//FPS計算
	mFps = mFpsCountor->UpdateFPS(mFrameTime);

	//FPSを出力窓に出す
#ifdef _DEBUG
#ifdef UNICODE
	std::wstringstream stream;
#else
	std::stringstream stream;
#endif
	mFrameCount++;
	if (mFrameTime > 0.0)
	{
		stream << std::to_string(mFps).c_str() << " FPS" << std::endl;
		if (mFrameCount % mDebugCount == 0)
		{
			OutputDebugString(stream.str().c_str());
		}
	}
#endif // _DEBUG
}
