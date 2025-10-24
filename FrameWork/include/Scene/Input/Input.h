#pragma once
#include "/SVN/Windows/FrameWork/FrameWork/include/GameInfo.h"

// 다이렉트에서 제공하는 input 을 사용해 볼것이다.
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")


// #define DIRECTINPUT_VERSION 0x8000

// 16진수
// 2진수 -> 10진수 -> 16진수
#define DIK_MOUSEBUTTON 0xfc
#define DIK_MOUSEBUTTON 0xfd
#define DIK_MOUSEWHEEL 0xfe

enum class EInputSystem_Type
{
	DInput,
	Window
};

namespace EMouseButtonType
{
	enum Type
	{
		LButton,
		RButton,
		MButton,
		End
	};
};

struct FKeyState
{
	unsigned char Key = 0;
	bool Down = false;
	bool Hold = false;
	bool Up = false;
};

namespace EInputType
{
	enum Type
	{
		Down,
		Hold,
		Up,
		End
	};
}

struct FBindFunction
{
	void* Obj = nullptr;
	function<void(float)> Func;
};

struct FBindKey
{
	FKeyState* Key = nullptr;
	bool Ctrl = false;
	bool Alt = false;
	bool Shift = false;

	vector<FBindFunction> FunctionList[EInputType::End];
};

class CInput
{
	friend class CScene;

private:
	CInput();
	~CInput();

private:
	HINSTANCE mhInst;
	HWND mhWnd;

	unsigned char mKeyState[256] = {};
	DIMOUSESTATE mMouseState = {};

	// 원한 키, 이벤트 이름을 바인드
	// 모든 키보드 마우스 상태값을 검사하는 게 아닌
	// 내가 추가한 키랑 이벤트만 상태가 들어왔는지를 검사할 것이고
	// 이벤트 이름이랑 키상태랑 함수포인터 바인드 할 것이다.
	// 상태가 들어온 키들만 해당 이벤트 이름을 호출할 것이다.

	// 해당 키가 눌렸는지 확인하고
	unordered_map<unsigned char, FKeyState*> mKeyStateMap;
	// 해당키가 눌린 상태면 바인드키를 호출한다.
	unordered_map<string, FBindKey*> mBindKeyMap;


	// 키 입력
	bool mCtrl = false;
	bool mAlt = false;
	bool mShift = false;

	// 마우스 버튼 타입 저장
	bool mMouseDown[EMouseButtonType::End] = {};	// 마우스 눌림
	bool mMouseHold[EMouseButtonType::End] = {};	// 누르고 있음
	bool mMouseUp[EMouseButtonType::End] = {};		// 마우스 뗐음

	// 디바이스 입력
	// 디바이스를 생성시키라고 요청을 할 때
	// 디바이스 같은 녀석인데 디바이스는 아니다.
	// IDirectInput8 객체로부터 내가 원하는 장치의 디바이스를 얻어온다.
	// 키보드 디바이스, 마우스 디바이스, 게임패드 디바이스 등등
	IDirectInput8* mInput = nullptr;
	IDirectInputDevice8* mKeyboard = nullptr;
	IDirectInputDevice8* mMouse = nullptr;


	EInputSystem_Type mInputType = EInputSystem_Type::DInput;


public:
	void AddBindKey(const string& Name, unsigned char Key);
	void ChangeKeyCtrl(const string& Name, bool Ctrl);
	void ChangeKeyAlt(const string& Name, bool Alt);
	void ChangeKeyShift(const string& Name, bool Shift);

private:
	bool InitInput();

	bool UpdateKeyboard();
	bool UpdateMouse();

	FKeyState* FindKeyState(unsigned char Key);
	FBindKey* FindBindKey(const string& Name);

public:
	bool Init();
	void Update(float DeltaTime);
	
private:
	void UpdateInput(float DeltaTime);
	void UpdateBind(float DeltaTime);


public:
	template<typename T>
	void AddBindFunction(const string& KeyName, EInputType::Type Type, T* Object, void(T::* Func)(float))
	{
		FBindKey* BindKey = FindBindKey(KeyName);

		if (!BindKey)
		{
			return;

			FBindFunction BindFunc;

			BindFunc.Obj = Object;
			// c++ 문법 : 멤버함수 바인드 문법
			BindFunc.Func = bind(Func, Object, placeholders::_1);

			BindKey->FunctionList[Type].emplace_back(BindFunc);
		}
	}

private:
	unsigned char ConvertKey(unsigned char Key);
};

