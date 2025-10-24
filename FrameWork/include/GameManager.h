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

	

	////사각형 하나 띄어보기 
	////FRects mRC = { 100, 100, 200, 200 };

	//// 플레이어 위치
	//FVector2D mPlayerPos = { 150.f, 150.f };
	//// 플레이어 크기
	//FVector2D mPlayerSize = { 100.f, 100.f };

	//std::list<FBullet> mBulletList;	// 여기에 총알을 넣어줄 것이다.

	//// 적
	///*FRects mEnemy = { 1000, 500, 1100, 600 };
	//std::list<FRects> mEnemyBulletList;
	//float mFireTime = 1.f;
	//float mFireAccTime = 0.f;
	//FVector2D FireDir;*/

	//FVector2D mEnemyPos = { 1000.f, 300.f };
	//FVector2D mEnemySize = { 100.f, 100.f };
	//float mEnemyDir = 1.f;
	//std::list<FBullet> mEnemyBulletList;
	//float mFireTime = 1.f;
	//float mFireAccTime = 0.f;

	//배경색 
	//처음 하시는 분들은 검정이 아닌 다른색으로 하는것을 추천드립니다. 
	//검정 비추 개발중일때는 
	float mClearColor[4] = { 1.f, 0.f, 1.f, 1.f };
	

public:
	HINSTANCE GetWindowInstance() const
	{
		return mhInst;
	}
	
	HWND GetWindowHandle()
	{
		return mhWnd;
	}


public:
	bool Init(HINSTANCE hInst);
	int Run();

	

private:
	// 시점 잡기
	void Logic();

	void Input(float DeltaTime);
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void PostCollisionUpdate(float DeltaTime);
	void Render(float DeltaTime);
	
private:
	ATOM RegisterWindowClass();
	bool Create();

	// 전역변수로 해야하기 때문에
	// static 을 추가해준다.
	// static을 쓰는 순간 this는 없다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	DECLARE_SINGLETONE(CGameManager)

};

