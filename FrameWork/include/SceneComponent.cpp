#include "SceneComponent.h"

CSceneComponent::CSceneComponent()
	: CComponent()
{
}

CSceneComponent::CSceneComponent(const CSceneComponent& Com)
	: CComponent(Com)
{
}

CSceneComponent::CSceneComponent(CSceneComponent&& Com)
	: CComponent(Com)
{
}

CSceneComponent::~CSceneComponent()
{
	size_t Size = mChildList.size();
	for (size_t i = 0; i < Size; i++)
	{
		mChildList[i]->Destroy();
	}
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
	Child->mParent = this;
	mChildList.emplace_back(Child);
}

bool CSceneComponent::Init()
{

	return true;
}
bool CSceneComponent::Init(const char* FileName)
{

	return true;
}
void CSceneComponent::PreUpdate(float DeltaTime)
{
	CComponent::PreUpdate(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}
		(*iter)->PreUpdate(DeltaTime);
		iter++;
	}

}
void CSceneComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) //삭제할 타이밍
		{
			//삭제할 컴포넌랑 자료구조의 마지막 요소랑 스왑 해준다. 
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::PostUpdate(float DeltaTime)
{
	CComponent::PostUpdate(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) //삭제할 타이밍
		{
			//삭제할 컴포넌랑 자료구조의 마지막 요소랑 스왑 해준다. 
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::Collision(float DeltaTime)
{
	CComponent::Collision(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) //삭제할 타이밍
		{
			//삭제할 컴포넌랑 자료구조의 마지막 요소랑 스왑 해준다. 
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::PreRender()
{
	CComponent::PreRender();

	mmatScale.Scaling(mWorldScale);
	mmatRot.Rotation(mWorldRot);
	mmatTranslate.Translation(mWorldPos);

	mmatWorld = mmatScale * mmatRot * mmatTranslate;

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) //삭제할 타이밍
		{
			//삭제할 컴포넌랑 자료구조의 마지막 요소랑 스왑 해준다. 
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::Render()
{
	CComponent::Render();

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) //삭제할 타이밍
		{
			//삭제할 컴포넌랑 자료구조의 마지막 요소랑 스왑 해준다. 
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::PostRender()
{
	CComponent::PostRender();

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) //삭제할 타이밍
		{
			//삭제할 컴포넌랑 자료구조의 마지막 요소랑 스왑 해준다. 
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
CSceneComponent* CSceneComponent::Clone()
{
	return new CSceneComponent(*this);
}


/////// 좌표 

void CSceneComponent::SetRelativeScale(const FVector3D& Scale)
{
	mRelativeScale = Scale;

	//부모 영향 받았으면 
	if (mParent)
	{
		mWorldScale = mRelativeScale * mParent->mWorldScale;
	}
	else
	{
		mWorldScale = mRelativeScale;
	}

	//내 크기가 정했으면 자식에게도 영향을 줘야한다. 
	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식의 월드 위치 = 자식의 상대 위치 * 내 월드스케일 + 내 월드위치 
		mChildList[i]->mWorldPos = mChildList[i]->mRelativePos * mWorldScale + mWorldPos;

		//자식의 월드 스케일도 셋팅 해줘야한다. 
		//자식의 크기 = 자식의 상대크기 * 내 월드 스케일 
		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
	}
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
	SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{
	SetRelativeScale(FVector3D(Scale.x, Scale.y, mRelativeScale.z));
}

void CSceneComponent::SetRelativeScale(float x, float y)
{
	SetRelativeScale(FVector3D(x, y, mRelativeScale.z));
}


//회전 

void CSceneComponent::SetRelativeRotation(const FVector3D& Rot)
{
	mRelativeRot = Rot;

	if (mParent)
	{
		mWorldRot = mRelativeRot + mParent->mWorldRot;
	}
	else
	{
		mWorldRot = mRelativeRot;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식의 월드 위치 = 자식의 상대 위치를 내 월드 회전값으로 횐전한 값 + 내 월드 위치 
		mChildList[i]->mWorldPos = mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos;

		//자식의 월드 회전 = 자식의 상대회전 + 내 월드회전 
		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeRot * mWorldRot);
	}
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
	SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeRotation(const FVector2D& Rot)
{
	SetRelativeRotation(FVector3D(Rot.x, Rot.y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotation(float x, float y)
{
	SetRelativeRotation(FVector3D(x, y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationX(float x)
{
	SetRelativeRotation(FVector3D(x, mRelativeRot.y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationY(float y)
{
	SetRelativeRotation(FVector3D(mRelativeRot.x, y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationZ(float z)
{
	SetRelativeRotation(FVector3D(mRelativeRot.x, mRelativeRot.y, z));
}

void CSceneComponent::SetRelativeRotationAxis(float Angle, const FVector3D& Axis)
{
	//추후에 구현하겠다. 
}

void CSceneComponent::SetRelativePos(const FVector3D& Pos)
{
	mRelativePos = Pos;

	if (mParent)
	{
		mWorldPos = mRelativePos + mParent->mWorldPos;
	}
	else
	{
		mWorldPos = mRelativePos;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식 위치 = 자식의 상대 위치 + 내 월드 위치 
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
	}
}

void CSceneComponent::SetRelativePos(float x, float y, float z)
{
	SetRelativePos(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativePos(const FVector2D& Pos)
{
	SetRelativePos(FVector3D(Pos.x, Pos.y, mRelativePos.z));
}

void CSceneComponent::SetRelativePos(float x, float y)
{
	SetRelativePos(FVector3D(x, y, mRelativePos.z));
}

//월드
void CSceneComponent::SetWorldScale(const FVector3D& Scale)
{
	mWorldScale = Scale;
	if (mParent)
	{
		//내 상대 크기 = 내 월드 크기 / 부모의 월드 크기 
		mRelativeScale = mWorldScale / mParent->mWorldScale;
	}
	else
	{
		mRelativeScale = mWorldScale;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식의 월드 스케일 = 자식의 상대 스케일 * 내 월드스케일 
		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);

		// 자식의 월드 위치 = 자식의 상대위치 * 내 월드 스케일 + 내월드 위치 
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos * mWorldScale + mWorldPos);
	}
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
	SetWorldScale(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{
	SetWorldScale(FVector3D(Scale.x, Scale.y, mWorldScale.z));
}

void CSceneComponent::SetWorldScale(float x, float y)
{
	SetWorldScale(FVector3D(x, y, mWorldScale.z));
}

void CSceneComponent::SetWorldRotation(const FVector3D& Rot)
{
	mWorldRot = Rot;

	if (mParent)
	{
		mRelativeRot = mWorldRot - mParent->mWorldRot;
	}
	else
	{
		mRelativeRot = mWorldRot;
	}

	size_t Size = mChildList.size();


	for (size_t i = 0; i < Size; ++i)
	{
		//자식의 월드 회전 = 자식의 상대 회전 + 내 월드 회전 
		mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);

		// 회전 시킨만큼 자식의 위치에도 영향을 주어야한다. 
		// 자식의 상대 위치에 내 월드만큼 회전을 시키고 + 내 위치만큼 이동
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos);
	}
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
	SetWorldRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldRotation(const FVector2D& Rot)
{
	SetWorldRotation(FVector3D(Rot.x, Rot.y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotation(float x, float y)
{
	SetWorldRotation(FVector3D(x, y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationX(float x)
{
	SetWorldRotation(FVector3D(x, mWorldRot.y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationY(float y)
{
	SetWorldRotation(FVector3D(mWorldRot.x, y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationZ(float z)
{
	SetWorldRotation(FVector3D(mWorldRot.x, mWorldRot.y, z));
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
	// 추후에 
}

void CSceneComponent::SetWorldPos(const FVector3D& Pos)
{
	mWorldPos = Pos;

	if (mParent)
	{
		//1. 내 월드 위치 - 부모의 월드위치 
		FVector3D RelativePos = mWorldPos - mParent->mWorldPos;
		//2 .부모의 월드 회전값의 반대만큼 회전해줘야한다. 
		mRelativePos = RelativePos.GetRotation(mParent->mWorldRot * -1);
	}
	else
	{
		mRelativePos = mWorldPos;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
	}
}

void CSceneComponent::SetWorldPos(float x, float y, float z)
{
	SetWorldPos(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldPos(const FVector2D& Pos)
{
	SetWorldPos(FVector3D(Pos.x, Pos.y, mWorldPos.z));
}

void CSceneComponent::SetWorldPos(float x, float y)
{
	SetWorldPos(FVector3D(x, y, mWorldPos.z));
}
