﻿#include "AssetManager.h"

#include "Mesh/MeshManager.h"

CAssetManager::CAssetManager()
{

}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mMeshManager);
}

bool CAssetManager::Init()
{
	//메쉬를 관리 
	mMeshManager = new CMeshManager;

	//이미지 텍스쳐 

	//사운드, 이펙트 등 다양한 리소들을 관리 할수도 있다. 


	return true;
}