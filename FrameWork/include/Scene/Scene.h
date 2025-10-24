#pragma once

#include "../Gameinfo.h"
#include "../Scene/Input/Input.h"

//월드를 구상하는 클래스이다. 
class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

protected:
	// 입력
	class CInput* mInput = nullptr;


	//오브젝트
	list<CSharedPtr<class CSceneObject>> mObjList;


public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void Input(float DeltaTime);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

};

