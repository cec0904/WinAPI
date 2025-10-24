#include "Scene.h"
#include "../Object/SceneObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	SAFE_DELETE(mInput);
}

bool CScene::Init()
{
	mInput = new CInput;
	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	return true;
}

bool CScene::Init(const char* FileName)
{
	return true;
}

void CScene::Input(float DeltaTime)
{
}

void CScene::PreUpdate(float DeltaTime)
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreUpdate(DeltaTime);
		++iter;
	}
}

void CScene::Update(float DeltaTime)
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CScene::PostUpdate(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CScene::Collision(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Collision(DeltaTime);
		++iter;
	}
}

void CScene::PreRender()
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreRender();
		++iter;
	}
}

void CScene::Render()
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}
}

void CScene::PostRender()
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd;

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostRender();
		++iter;
	}
}