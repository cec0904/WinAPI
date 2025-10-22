﻿//#pragma once
//
///*
//	공유 포인터 클래스 를 만들것이다.
//	참조 카운트 방식
//	목적 : 메모리 누수 방지
//*/
//class CSharedPtr
//{
//private:
//	// 모든 객체들은 CObject를 상속받아서 만들 계획이니까
//	class CObject* mObj = nullptr;
//
//public:
//	CSharedPtr();
//	CSharedPtr(class CObject* Obj);
//	CSharedPtr(const CSharedPtr& Ptr);
//	CSharedPtr(CSharedPtr&& Ptr);
//	~CSharedPtr();
//	// 여기까지가 생성소멸//
//
//	// 연산자
//public:
//	void operator = (class CObject* Obj);
//	void operator = (const CSharedPtr& Ptr);
//	void operator = (CSharedPtr&& Ptr);
//
//	bool operator == (class CObject* Obj) const;
//	bool operator == (const CSharedPtr& Ptr) const;
//	bool operator == (CSharedPtr&& Ptr) const;
//
//	bool operator != (class CObject* Obj) const;
//	bool operator != (const CSharedPtr& Ptr) const;
//	bool operator != (CSharedPtr&& Ptr) const;
//
//	class CObject* operator->() const;
//
//	/*
//		CSharedPtr ptr = new CObject;
//	*/
//
//
//	operator class CObject* () const;
//
//	class CObject* Get() const;
//
//};
//


#pragma once
/*
	공유 포인터 클래스 를 만들것이다.
	참조 카운트 방식
	목적 : 메모리 누수 방지
*/

template <typename T>
class CSharedPtr
{
private:
	//모든 객체들은 CObject를 상속받아서 만들 계획이니까 
	T* mObj = nullptr;

public:
	CSharedPtr()
	{

	}
	CSharedPtr(T* Obj)
	{
		mObj = Obj;

		if (mObj)
		{
			mObj->AddRef();
		}
	}
	CSharedPtr(const CSharedPtr& Ptr)
	{
		mObj = Ptr.mObj;

		if (mObj)
		{
			mObj->AddRef();
		}
	}
	CSharedPtr(CSharedPtr&& Ptr)
	{
		mObj = Ptr.mObj;

		if (mObj)
		{
			mObj->AddRef();
		}
	}
	~CSharedPtr()
	{
		if (mObj)
		{
			mObj->Release();
		}
	}

	///여기까지가 생성 소멸 ///////////////
	//연산자 = == !=
public:
	void operator = (T* Obj)
	{
		if (mObj)
		{
			mObj->Release();
		}

		mObj = Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다. 
		if (mObj)
		{
			mObj->AddRef();
		}
	}
	void operator = (const CSharedPtr& Ptr)
	{
		if (mObj)
		{
			mObj->Release();
		}

		mObj = Ptr.mObj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다. 
		if (mObj)
		{
			mObj->AddRef();
		}
	}
	void operator = (CSharedPtr&& Ptr)
	{
		if (mObj)
		{
			mObj->Release();
		}

		mObj = Ptr.mObj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다. 
		if (mObj)
		{
			mObj->AddRef();
		}
	}

	bool operator == (T* Obj) const
	{
		return mObj == Obj;
	}
	bool operator == (const CSharedPtr& Ptr) const
	{
		return mObj == Ptr.mObj;
	}
	bool operator == (CSharedPtr&& Ptr) const
	{
		return mObj == Ptr.mObj;
	}

	bool operator != (T* Obj) const
	{
		return mObj != Obj;
	}
	bool operator != (const CSharedPtr& Ptr) const
	{
		return mObj != Ptr.mObj;
	}
	bool operator != (CSharedPtr&& Ptr) const
	{
		return mObj != Ptr.mObj;
	}

	T* operator -> () const
	{
		return mObj;
	}
	/*
		CSharedPtr ptr = new CObject;
	*/
	operator T* () const
	{
		return mObj;
	}

	T* Get() const
	{
		return mObj;
	}
};


