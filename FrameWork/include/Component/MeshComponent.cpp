#include "MeshComponent.h"
#include "../Shader/TransformCBuffer.h"


CMeshComponent::CMeshComponent()
	:CSceneComponent()
{
	mTransformCBuffer = new CTransformCBuffer;
	mTransformCBuffer->Init();
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com)
	: CSceneComponent(Com)
{
	mTransformCBuffer = Com.mTransformCBuffer->Clone();

}

CMeshComponent::CMeshComponent(CMeshComponent&& Com)
	: CSceneComponent(Com)
{
	mTransformCBuffer = Com.mTransformCBuffer->Clone();
}

CMeshComponent::~CMeshComponent()
{
	SAFE_DELETE(mTransformCBuffer);
}

bool CMeshComponent::Init()
{
	return true;
}
bool CMeshComponent::Init(const char* FileName)
{
	return true;
}
void CMeshComponent::PreUpdate(float DeltaTime)
{
}
void CMeshComponent::Update(float DeltaTime)
{
}
void CMeshComponent::PostUpdate(float DeltaTime)
{
}
void CMeshComponent::Collsion(float DeltaTime)
{
}
void CMeshComponent::PreRender()
{
}
void CMeshComponent::Render()
{
	mTransformCBuffer->SetWorldMatrix(mmatWorld);

	FMatrix matProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90.f), 1280.f / 720.f, 0.5f, 1000.f);
	mTransformCBuffer->SetProjMatrix(matProj);

	mTransformCBuffer->UpdateBuffer();
}
void CMeshComponent::PostRender()
{
}
CMeshComponent* CMeshComponent::Clone()
{
	return new CMeshComponent(*this);
}