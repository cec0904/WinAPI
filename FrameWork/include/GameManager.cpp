#include "GameManager.h"
#include "resource.h"

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
    // DC 반납
    ReleaseDC(mhWnd, mhDC);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	mhInst = hInst;

	lstrcpy(mClassName, TEXT("KDT4FrameWork"));
	lstrcpy(mTitleName, TEXT("KDT4FrameWork"));

    RegisterWindowClass();

    if (!Create())
    {
        return false;
    }

    // DC : 디바이스 컨텍스트
    // 주의사항 : 꼭 해제해줘야 한다.
    mhDC = GetDC(mhWnd);

	return true;
}

int CGameManager::Run()
{
    MSG msg;    // 운영체제가 만들어 주는 메세지를 전달 받기 위한 구조체


    while (mLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
                // 메세지를 처리하는 함수
                // 키보드 입력 메세지가 발생할 경우 동작한다.
                // WM_KEYDOWN, WM_KEYUP 등 메세지가 발생하면 호출된다.
                TranslateMessage(&msg);
                // WndProc 함수로 메세지를 전달해주는 함수다.
                DispatchMessage(&msg);
        }
        else
        {
            // 윈도우 데드타임
            // 여기서 부터 게임을 만들 수 있게 된다.
        }
    }


    return (int)msg.wParam;

}

ATOM CGameManager::RegisterWindowClass()
{
    // 윈도우 클래스 구조체 
    // 윈도우의 속성들을 지정하는 구조체이다.
    WNDCLASSEXW wcex;

    //윈도우 클래스 구조체의 크기를 나타낸다. 반드시 지정되어야 한다. 
    wcex.cbSize = sizeof(WNDCLASSEX);

    //윈도우 클래스의 스타일을 지정한다. 
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // 메시지를 처리하는 함수의 포인터 이다. 
    // 메시지큐에서 얻어온 메시지를 인자로 넣어서 호출해줄 함수를 주소를 넘겨준다. 
    wcex.lpfnWndProc = WndProc;

    // 필요없는애다. 그래서 0들어가는 것이다.
    // 윈도우 클래스에 대한 추가메모리를 지정한다.
    wcex.cbClsExtra = 0;

    // 윈도우 인스턴스에 대한 추가 메모리를 지정한다.
    wcex.cbWndExtra = 0;

    // 운영체제에서 부여해준 HISTANCE를 지정해준다.
    wcex.hInstance = mhInst;

    // 실행파일 아이콘을 지정한다.
    // 바탕화면 아이콘
    // 리소스 뷰 : 보기 -> 다른창 -> 리소스 뷰
    // 솔루션 탐색기 -> 리소스 파일 -> 우클릭 -> 추가 -> 리소스
    wcex.hIcon = LoadIcon(mhInst, MAKEINTRESOURCE(IDI_ICON1));

    // 커서 모양
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    // 클라이언트 영역의 색상을 지정해준다.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // 윈도우 메뉴를 지정해준다.
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDI_ICON1);
    // wcex.lpszMenuName   = 0;
    // 0을 넣으면 메뉴가 없는 윈도우가 된다.

    // 윈도우 클래스의 이름을 지정한다.
    wcex.lpszClassName = mClassName;

    // 타이틀 바 왼쪽의 아이콘을 의미한다.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // 위에서 설정한 윈도우 클래스를 등록한다.
    return RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    mhWnd = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mhInst, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }
    //여기까지가 창을 만들기 위하 한것들.

    //위에서 윈도우 창을 만들었다면 이제 ShowWindow 함수를 이용해서 창을 보여줄지 숨길지 결정한다. 
    //ShowWindow(hWnd, nCmdShow);
    ShowWindow(mhWnd, SW_SHOW);
    //ShowWindow(hWnd, SW_MAXIMIZE);
    // 클라이언트 영역을 강제로 다시 그리게 요청해주는 함수이다. 
    // 처음 생성시나 특정상황에 창을 다시 그려야 할때 호출 된다. 
    UpdateWindow(mhWnd);

    return TRUE;
}

LRESULT CGameManager::WndProc(HWND mhWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        HDC hdc = BeginPaint(mhWnd, &ps);


        //텍스트 출력 
        TextOut(hdc, 10, 10, L"Output", 6);
        TextOut(hdc, 100, 100, TEXT("Output"), 6);

        //사각형 그리기 
        Rectangle(hdc, 100, 200, 200, 300);
        Ellipse(hdc, 100, 200, 200, 300);

        //선 그리기
        //선 시작점 
        MoveToEx(hdc, 200, 100, nullptr);   //선의 시작점 
        LineTo(hdc, 300, 200);
        LineTo(hdc, 400, 100);

        MoveToEx(hdc, 300, 300, nullptr);
        LineTo(hdc, 400, 300);

        EndPaint(mhWnd, &ps);
    }
    break;
    case WM_DESTROY:
        mLoop = false;      // 윈도우를 종료하게 되면 루프를 종료 해준다.
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(mhWnd, message, wParam, lParam);
    }
    return 0;
}
