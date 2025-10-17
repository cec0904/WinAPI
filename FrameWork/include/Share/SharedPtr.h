#pragma once

/*
	공유 포인터 클래스 를 만들것이다.
	참조 카운트 방식
	목적 : 메모리 누수 방지
*/
class CSharedPtr
{
private:
	// 모든 객체들은 CObject를 상속받아서 만들 계획이니까
	class CObject* mObj = nullptr;

public:
	CSharedPtr();
	CSharedPtr(class CObject* Obj);
	CSharedPtr(const CSharedPtr& Ptr);
	CSharedPtr(CSharedPtr&& Ptr);
	~CSharedPtr();
	// 여기까지가 생성소멸//

	// 연산자
public:
	void operator = (class CObject* Obj);
	void operator = (const CSharedPtr& Ptr);
	void operator = (CSharedPtr&& Ptr);

	bool operator == (class CObject* Obj) const;
	bool operator == (const CSharedPtr& Ptr) const;
	bool operator == (CSharedPtr&& Ptr) const;

	bool operator != (class CObject* Obj) const;
	bool operator != (const CSharedPtr& Ptr) const;
	bool operator != (CSharedPtr&& Ptr) const;

	class CObject* operator->() const;

	/*
		CSharedPtr ptr = new CObject;
	*/


	operator class CObject* () const;

	class CObject* Get() const;

};

