#include "TimeBaseLoopExecuter.h"

void TimeBaseLoopExecuter::TimeAdjustment()
{
	//�������Ԃ��擾
	mFrameTime = mFpsCountor->GetDefTime();
	//�������Ԃɗ]�T������ꍇ�͂��̕��҂�
	if (mFrameTime < FRAME_TIME)
	{
		//Sleep�̎��Ԃ��v�Z
		//s��ms�ϊ��̂���*1000
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - mFrameTime) * 1000);
		//�Q��
		Sleep(sleepTime);
	}
	//FPS�v�Z
	mFps = mFpsCountor->UpdateFPS(mFrameTime);

	//FPS���o�͑��ɏo��
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
