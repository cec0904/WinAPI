#include "Input.h"
#include "../../Device.h"
#include "../../GameManager.h"


CInput::CInput()
{
}
CInput::~CInput()
{
	auto iter = mKeyStateMap.begin();
	auto iterEnd = mKeyStateMap.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}

	auto iter1 = mBindKeyMap.begin();
	auto iterEnd1 = mBindKeyMap.end();

	for (; iter1 != iterEnd1; iter1++)
	{
		SAFE_DELETE(iter1->second);
	}

	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		SAFE_RELEASE(mKeyboard);
	}

	if (mMouse)
	{
		mMouse->Unacquire();
		SAFE_RELEASE(mMouse);
	}
}

// AddBindKey("MoveUp", 'W');
void CInput::AddBindKey(const string& Name, unsigned char Key)
{
	if (FindBindKey(Name))
	{
		return;
	}
	FBindKey* NewKey = new FBindKey;

	FKeyState* State = FindKeyState(Key);

	if (!State)
	{
		State = new FKeyState;
		State->Key = ConvertKey(Key);
		mKeyStateMap.insert(make_pair(Key, State));
	}

	NewKey->Key = State;
	mBindKeyMap.insert(make_pair(Name, NewKey));
}
void CInput::ChangeKeyCtrl(const string& Name, bool Ctrl)
{
	FBindKey* Key = FindBindKey(Name);

	if (!Key)
	{
		return;
	}
	Key->Ctrl = Ctrl;
}
void CInput::ChangeKeyAlt(const string& Name, bool Alt)
{
	FBindKey* Key = FindBindKey(Name);
	if (!Key)
	{
		return;
	}
	Key->Alt = Alt;
}
void CInput::ChangeKeyShift(const string& Name, bool Shift)
{
	FBindKey* Key = FindBindKey(Name);
	if (!Key)
	{
		return;
	}
	Key->Shift = Shift;
}
bool CInput::InitInput()
{
	if (FAILED(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr)))
	{
		return false;
	}

	if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	//창모드냐 아니냐에 따라서 기본 설정값이 달라집니다. 
	//DISCL_FOREGROUND		: 활설화 시에만 키를 입력받게 한다. 
	//DISCL_BACKGROUND		: 백그라운드에서도 사용할 수 있게 설정한다.
	//DISCL_EXCLUSIVE		: 입력 디바이스를 독점모드로 설정한다. 
	//DISCL_NONEXCLUSIVE	: 입력 디바이스를 비독점 모드로설정한다. 
	if (CDevice::GetInst()->GetWindowMod())	//창모드
	{
		if (FAILED(mKeyboard->SetCooperativeLevel(mhWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		{
			return false;
		}
	}
	else
	{
		if (FAILED(mKeyboard->SetCooperativeLevel(mhWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			return false;
		}
	}

	//키보드 장치를 획득한다. 
	if (FAILED(mKeyboard->Acquire()))
	{
		return false;
	}

	/////////////마우스 
	if (FAILED(mInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
	{
		return false;
	}

	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}

	if (CDevice::GetInst()->GetWindowMod())	//창모드
	{
		if (FAILED(mMouse->SetCooperativeLevel(mhWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		{
			return false;
		}
	}
	else
	{
		if (FAILED(mMouse->SetCooperativeLevel(mhWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			return false;
		}
	}

	//마우스 장치를 획득한다. 
	if (FAILED(mMouse->Acquire()))
	{
		return false;
	}



	return true;
}

bool CInput::UpdateKeyboard()
{
	if (!mKeyboard)
	{
		return false;
	}

	HRESULT result = mKeyboard->GetDeviceState(256, (LPVOID) & mKeyState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			mKeyboard->Acquire();
		}
	}


	return true;
}

bool CInput::UpdateMouse()
{
	if (!mMouse)
	{
		return false;
	}

	HRESULT result = mMouse->GetDeviceState(sizeof(mMouseState),(LPVOID)&mMouseState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			mMouse->Acquire();
		}
	}


	return true;

}

FKeyState* CInput::FindKeyState(unsigned char Key)
{
	auto iter = mKeyStateMap.find(Key);

	if (iter == mKeyStateMap.end())
	{
	return nullptr;

	}
	return iter->second;
}

FBindKey* CInput::FindBindKey(const string& Name)
{
	auto iter = mBindKeyMap.find(Name);

	if (iter == mBindKeyMap.end())
	{
		return nullptr;

	}
	return iter->second;
}

bool CInput::Init()
{
	// 입력장치 초기화하는데
	// 윈도우의 Instance, handle 이 필요하다.
	// Inst, hWnd
	mhInst = CGameManager::GetInst()->GetWindowInstance();
	mhWnd = CGameManager::GetInst()->GetWindowHandle();

	if (FAILED(DirectInput8Create(mhInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInput, nullptr)))
	{
		// 다이렉트 입력을 초기화 못하면
		// 윈도우의 입력을 사용하겠다.
		mInputType = EInputSystem_Type::Window;
	}

	if (mInputType == EInputSystem_Type::DInput)
	{
		// 다이렉트 인풋이 사용 가능하면 장치를 여기서 얻어올 것이다.`
		if (!InitInput())
		{
			return false;
		}
	}

	return true;
	

	
}

void CInput::Update(float DeltaTime)
{
	if (mInputType == EInputSystem_Type::DInput)
	{
	UpdateKeyboard();
	UpdateMouse();

	}
	UpdateBind(DeltaTime);
	UpdateInput(DeltaTime);
}

void CInput::UpdateInput(float DeltaTime)
{
	switch (mInputType)
	{
	case EInputSystem_Type::DInput:
		if (mKeyState[DIK_LCONTROL] & 0x80)
		{
			mCtrl = true;
		}
		else
		{
			mCtrl = false;
		}

		if (mKeyState[DIK_LALT] & 0x80)
		{
			mAlt = true;
		}
		else
		{
			mAlt = false;
		}

		if (mKeyState[DIK_LSHIFT] & 0x80)
		{
			mShift= true;
		}
		else
		{
			mShift = false;
		}

		for (int i = 0; i < EMouseButtonType::End; i++)
		{
			if (mMou)
			{

			}
		}


		break;
	case EInputSystem_Type::Window:
		break;
	default:
		break;
	}
}

void CInput::UpdateBind(float DeltaTime)
{
}

unsigned char CInput::ConvertKey(unsigned char Key)
{
	return 0;
}


