#include "Timer.h"

LARGE_INTEGER CTimer::mSecond = {};
LARGE_INTEGER CTimer::mTime = {};
float CTimer::mDeltaTime = 0.f;



void CTimer::Init()
{
	QueryPerformanceFrequency(&mSecond);		// 초당 몇 프레임(카운트) 수를 얻어온다.
	QueryPerformanceCounter(&mTime);		// 현재 시간을 가져온다. 현재 몇번 호출 됐는지 계속 카운트 하고 있음
}

float CTimer::Update()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	
	// 공식
	// (현재 프레임 카운트 - 이전 프레임 카운트) / 초당 카운트 수 
	//  105                     100               100(1초동안 100번)
	// 5 : X초 : 100 : 1초 
	// (time.QuadPart - mTime.QuadPart) : mDeltaTime = mSecond : 1;
	// mDeltaTime * mSecond = (time.QuadPart - mTime.QuadPart)
	// mDeltaTime = (time.QuadPart - mTime.QuadPart) / mSecond
	mDeltaTime = (time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
	mTime = time;	//시간 갱신 
	return mDeltaTime;
}

float CTimer::GetDeltaTime()
{
	return mDeltaTime;
}
