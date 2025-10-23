#pragma once

#include "../Share/Object.h"

class CSceneObject : public CObject
{
	friend class CScene;

protected:
	CSceneObject();
	CSceneObject(const CSceneObject& Obj);
	CSceneObject(CSceneObject&& Obj);
	virtual ~CSceneObject();

protected:
	//어떤 씬이 나를 들고있는지 
	class CScene* mScene = nullptr;
	std::string mName;
	//내가어떤 컴포넌트를 가지고 있을것인가?


public:
	class CScene* GetScene() const
	{
		return mScene;
	}

	const char* GetName() const
	{
		return  mName.c_str();
	}

	//set 
	void SetName(const std::string& Name)
	{
		mName = Name;
	}

	//시점 함수 
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
	virtual CSceneObject* Clone();

};

