#pragma once
// 추상클래스
// 키워드로 추상 클래스를 만들 수 있다.
// abstract 해당 클래스는 추상 클래스다 ~ 라고 정의하는 것이다.

#include "../Gameinfo.h"

class CObject abstract
{
protected:
	CObject();
	virtual ~CObject();

protected:
	int mRefCount = 0;

public:
	virtual void AddRef();
	virtual void Release();

};

