#include "TimeBaseLoopExecuter.h"

double TimeBaseLoopExecuter::TimeAdjustment()
{
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&mTimeEnd);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	mFrameTime = static_cast<double>(mTimeEnd.QuadPart - mTimeStart.QuadPart) / static_cast<double>(mTimeFreq.QuadPart);
	double fps = 0.0;
	//�������Ԃɗ]�T������ꍇ�͂��̕��҂�
	if (mFrameTime < FRAME_TIME)
	{
		//Sleep�̎��Ԃ��v�Z
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - mFrameTime) * 1000);
		timeBeginPeriod(1);
		//�Q��
		Sleep(sleepTime);
		timeEndPeriod(1);
	}
	else 
	{
		fps = 1 / mFrameTime;
		mTimeStart = mTimeEnd;

		//FPS���o�͑��ɏo��
#ifdef _DEBUG
#ifdef UNICODE
		std::wstringstream stream;
#else
		std::stringstream stream;
#endif
		mFrameCount++;
		if (mFrameCount % mDebugCount == 0)
		{
			stream << std::to_string(fps).c_str() << " FPS" << std::endl;
			OutputDebugString(stream.str().c_str());
		}
#endif // _DEBUG
	}
	return fps;
}
