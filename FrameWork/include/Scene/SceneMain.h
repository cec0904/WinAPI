#pragma once
#include "Scene.h"

class SceneMain :
	public CScene
{
	friend class CSceneManager;

protected:
	SceneMain();
	virtual ~SceneMain();

public:
	virtual bool Init();

};

