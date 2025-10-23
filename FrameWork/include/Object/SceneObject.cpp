#include "SceneObject.h"

CSceneObject::CSceneObject()
{
}

CSceneObject::CSceneObject(const CSceneObject& Obj)
{
}

CSceneObject::CSceneObject(CSceneObject&& Obj)
{
}

CSceneObject::~CSceneObject()
{
}


bool CSceneObject::Init()
{
	return true;
}

bool CSceneObject::Init(const char* FileName)
{
	return true;
}

void CSceneObject::PreUpdate(float DeltaTime)
{
}
void CSceneObject::Update(float DeltaTime)
{
}
void CSceneObject::PostUpdate(float DeltaTime)
{
}
void CSceneObject::Collsion(float DeltaTime)
{
}
void CSceneObject::PreRender()
{
}
void CSceneObject::Render()
{
}
void CSceneObject::PostRender()
{
}

CSceneObject* CSceneObject::Clone()
{
	return nullptr;
}