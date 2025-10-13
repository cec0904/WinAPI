#pragma once

#include "GameInfo.h"


class CGameManager
{
private:
	// static 쓰면 초기화 해줘야 한다.
	static bool mLoop;

	HINSTANCE mhInst = 0;
	HWND mhWnd = 0;
	HDC mhDC = 0;
	TCHAR mClassName[256] = {};
	TCHAR mTitleName[256] = {};



public:
	bool Init(HINSTANCE hInst);
	int Run();
	
private:
	ATOM RegisterWindowClass();
	bool Create();

	// 전역변수로 해야하기 때문에
	// static 을 추가해준다.
	// static을 쓰는 순간 this는 없다.
	static LRESULT CALLBACK    WndProc(HWND mhWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLETONE(CGameManager)

};

