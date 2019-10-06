#include "FPSCounter.h"


FPSCounter::FPSCounter(unsigned int inSampleNum)
{
	//�T���v�����̐ݒ�
	//���ς��v�Z�����
	mTimeDataCount = inSampleNum;
	//���X�g������
	mTimeList.resize(mTimeDataCount, 0.0);
	mSumTimes = 0;
	//�v�����鎞�v�̑I��
	if (QueryPerformanceCounter(&mCounter) != 0)
	{
		//QueryPerformanceCounter�֐����g���t���O
		mCounterFlg = FPSCOUNTER_QUERYPER_COUNTER;
		//�������̎����i�N���b�N���j���擾
		mBeforeClockCount = mCounter.QuadPart;        
		LARGE_INTEGER Freq;
		//1�b������N���b�N�����擾
		QueryPerformanceFrequency(&Freq);            
		mFreq = (double)Freq.QuadPart;
	}
	else
	{
		//timeGetTime�֐����g���t���O
		mCounterFlg = FPSCOUNTER_TIMEGETTIME;
		//���x���グ��
		timeBeginPeriod(1);
		//�������̎����i�~���b�j���擾
		mBeforeMillSecond = timeGetTime();
	}
}


FPSCounter::~FPSCounter()
{
	//�^�C�}�[�̐��x��߂�
	if (mCounterFlg == FPSCOUNTER_TIMEGETTIME) timeEndPeriod(1);    
}

double FPSCounter::GetDefTime()
{
	//�������Ԃ��v��
	//�g���鎞�v�ɂ���Ďg���֐���؂�ւ���
	if (mCounterFlg == FPSCOUNTER_QUERYPER_COUNTER)
	{
		//QueryPerformanceCounter�֐��ɂ��v��
		QueryPerformanceCounter(&mCounter);
		LONGLONG longDef = mCounter.QuadPart - mBeforeClockCount;
		mBeforeClockCount = mCounter.QuadPart;
		return (double)longDef * 1000 / mFreq;
	}
	else 
	{
		//timeGetTime�֐��ɂ��v��
		DWORD time = timeGetTime();
		DWORD defTime = time - mBeforeMillSecond;
		mBeforeMillSecond = time;
		return defTime;
	}
}

double FPSCounter::UpdateFPS(double inDef)
{
	//���ʉ��Z�����̍X�V
	mSumTimes += inDef - *mTimeList.begin();
	//�ł��Â��f�[�^������
	mTimeList.pop_front();
	//�V�����f�[�^��ǉ�
	mTimeList.push_back(inDef);
	//FPS�Z�o
	double fps = 0.0;
	double aveDef = mSumTimes / mTimeDataCount;
	if (aveDef != 0) fps = 1000.0 / aveDef;
	return fps;
}

