#pragma once

#include "../Gameinfo.h"

//월드를 구상하는 클래스이다. 
class CScene
{
protected:
	CScene();
	virtual ~CScene();

protected:
	//오브젝트
	std::list<CSharedPtr<class CSceneObject>> mObjList;


public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collsion(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

};

