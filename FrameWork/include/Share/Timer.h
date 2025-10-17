#pragma once

#include "../GameInfo.h"

/*
	델타 타임이란?
	프레임 간의 시간차이를 의미한다
	FPS 는 1초에 몇 번 화면이 갱신 되었는가를 의미한다.
	60FPS -> 1초에 화면이 60번 그려진 것
	60FPS 일 때 1프레임은 0.01666 초 정도 된다.
*/


class CTimer
{

	friend class CGameManager;

private:
	static LARGE_INTEGER mSecond;
	static LARGE_INTEGER mTime;
	static float mDeltaTime;	// 델타타임을 나타낼 것이다.
	// static 선언했으면 소스파일쪽에서 밖에서 초기화 해야함

private:
	static void Init();
	static float Update();

public:
	static float GetDeltaTime();
};

