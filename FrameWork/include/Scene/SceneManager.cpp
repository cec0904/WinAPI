#include "SceneManager.h"

#include "SceneMain.h"

CSceneManager::CSceneManager()
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mCurrentScene);
}

bool CSceneManager::Init()
{
	mCurrentScene = CreateScene<SceneMain>();

	if (mCurrentScene == nullptr)
	{
		return false;
	}

	return true;

}
void CSceneManager::Input(float DeltaTime)
{
	mCurrentScene->Input(DeltaTime);
}
void CSceneManager::Update(float DeltaTime)
{

}

void CSceneManager::Collision(float DeltaTime)
{

}
void CSceneManager::Render() {

}