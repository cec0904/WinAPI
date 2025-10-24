#include "StaticMeshComponent.h"

#include"../Asset/Mesh/StaticMesh.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"


CStaticMeshComponent::CStaticMeshComponent()
	: CMeshComponent()
{
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& Com)
	: CMeshComponent(Com)
{
}

CStaticMeshComponent::CStaticMeshComponent(CStaticMeshComponent&& Com)
	: CMeshComponent(Com)
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

void CStaticMeshComponent::SetShader(const std::string& Name)
{
	mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CStaticMeshComponent::SetShader(CShader* Shader)
{
	mShader = Shader;
}

void CStaticMeshComponent::SetMesh(const std::string& Name)
{
	mMesh = (CStaticMesh*)CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);
}

void CStaticMeshComponent::SetMesh(CMesh* Mesh)
{
	mMesh = (CStaticMesh*)Mesh;
}

bool CStaticMeshComponent::Init()
{
	return true;
}
bool CStaticMeshComponent::Init(const char* FileName)
{
	return true;
}
void CStaticMeshComponent::PreUpdate(float DeltaTime)
{
}
void CStaticMeshComponent::Update(float DeltaTime)
{
}
void CStaticMeshComponent::PostUpdate(float DeltaTime)
{
}
void CStaticMeshComponent::Collsion(float DeltaTime)
{
}
void CStaticMeshComponent::PreRender()
{
}
void CStaticMeshComponent::Render()
{
}
void CStaticMeshComponent::PostRender()
{
}
CStaticMeshComponent* CStaticMeshComponent::Clone()
{
	return new CStaticMeshComponent(*this);
}
