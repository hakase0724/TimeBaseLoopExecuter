#pragma once
#include <fstream>
#include <sstream>
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib,"winmm.lib")

class TimeBaseLoopExecuter
{
public:
	TimeBaseLoopExecuter(double frame = 60.0):FRAME_TIME(1.0f / frame)
	{
		//���g���擾
		QueryPerformanceFrequency(&mTimeFreq);
		//�v���J�n���Ԃ̏�����
		QueryPerformanceCounter(&mTimeStart);
	}
	//FPS���Œ肷�邽�ߏ������Ԃɗ]�T������ꍇ���̕��҂�
	double TimeAdjustment();
private:
	const double FRAME_TIME = 0.0;
	double mFrameTime = 0.0;
	//�v���J�n����
	LARGE_INTEGER mTimeStart;
	//�v���I������
	LARGE_INTEGER mTimeEnd;
	//�v�����g��
	LARGE_INTEGER mTimeFreq;

#ifdef _DEBUG
public:
private:
	int mFrameCount = 0;
	int mDebugCount = 10;
#endif // _DEBUG

};

