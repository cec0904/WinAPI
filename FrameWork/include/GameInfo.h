#pragma

// 미리 컴파일 된 헤더
#include <Windows.h>

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