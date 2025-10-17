#pragma once
// 미리 컴파일 된 헤더


// .lib 을 통해서 DX11 기능을 불러와야 한다.
// 링크를 거는 방법
#pragma comment(lib, "d3d11.lib")
// dx11 기능을 포함하는 애

// 이미 c++ 컴파일러 포함된거 아님 ? -> 아님
// dx11 은 쉐이더를 별도로 컴파일 해줘야 하므로, 그 컴파일을 하기 위해서 필요하다.
// 왜 ? 쉐이더는 c++로 되어있지 않다. glsl, hlsl 라는 쉐이더 언어가 따로 있어서 그 별도의 언어를 컴파일 하기 위해 컴파일러를 추가한다.
#pragma comment(lib, "d3dcompiler.lib")


// glid를 사용하기 위해서 필요하다.
#pragma comment(lib, "dxguid.lib")




#include <Windows.h>

#include <vector>	// 자료구조 리스트
#include <map>	// 기본 트리
#include <unordered_map>	// 해쉬트리

#include <list>	// 자료구조 리스트
//using namespace std;

// DX를 사용하기 위한 헤더
#include <d3d11.h>
#include <d3dcompiler.h>

/*
	라이브러리를 가져와서 사용하는 방식이다.
	lib, dll
	그 프로그램의 주소값만 가지고 있다. 참조만 한다.
	외부참조를 한다.

	lib : 정적 라이브러리
	프로그램 빌드 시점에서 실행파일에 코드가 직접 포함된다.

	dll : 동적 라이브러리
	프로그램 시작되면 그 때 메모리에 별도로 로드된다. 런타임 중 기능을 불러온다. 프로그램 빌드 시 코드가 포함은 안된다.
*/

#include "Vector2D.h"

// RELEASE 매크로
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr;}

// 마이어스 싱글톤
// 정적변수 프로그램 종료될 때 까지 쓰겠다.
#define DECLARE_SINGLETONE(ClassName)\
private:\
	ClassName();\
	~ClassName();\
public:\
	static ClassName* GetInst()\
	{\
		static ClassName instance;\
		return &instance;\
	}

struct FRects
{
	float Left = 0.f;
	float Top = 0.f;
	float Right = 0.f;
	float Bottom = 0.f;
};

enum class EBulletOption
{
	Normal,
	Bound,
	Wave
};

struct FBullet
{
	FVector2D Pos;
	FVector2D Size;
	FVector2D MoveDir;

	float Distance = 400.f;	//사정거리 
	EBulletOption Option = EBulletOption::Normal;

	//time
	float AccTime = 0;
};


struct FResolution
{
	unsigned int Width;
	unsigned int Height;
};