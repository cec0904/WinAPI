#include "GameManager.h"
#include "resource.h"

#include "Share/Timer.h"
#include "Device.h"

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

	lstrcpy(mClassName, TEXT("FrameWork"));
	lstrcpy(mTitleName, TEXT("FrameWork"));

    RegisterWindowClass();

    if (!Create())
    {
        return false;
    }

    // DC : 디바이스 컨텍스트
    // 주의사항 : 꼭 해제해줘야 한다.
    mhDC = GetDC(mhWnd);

    if (!CDevice::GetInst()->Init(mhWnd, 1280, 720, true))
    {
        return false;
    }

    CTimer::Init();

	return true;
}

int CGameManager::Run()
{
    ///!!!!!!!!!!!!!!!!
    // 여기가 가장 중요하다 
    MSG msg = {};    // 운영체제가 만들어 주는 메세지를 전달 받기 위한 구조체 
    // PeekMessage : 메시지큐의 메시지를 얻어오는 함수이다. 
    // 이 함수는 메시지큐가 비어있을 경우 바로 빠져나오면서 0을 반환한다. 
    // 메시지큐에 메시지가 있다면 해당 메시지를 가져온다. 


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
            // 윈도우는 메시지 기반
            // 메시지가 없는 시간
            // 여기서 부터 게임을 만들 수 있게 된다.
            Logic();
        }
    }


    return (int)msg.wParam;

}

void CGameManager::Logic()
{
    float DeltaTime = CTimer::Update();
    // deltatime -> 한번 각각 돌아오는 시간

    Input(DeltaTime);
    Update(DeltaTime);
    PostUpdate(DeltaTime);
    Collision(DeltaTime);
    PostCollisionUpdate(DeltaTime);
    Render(DeltaTime);
}

void CGameManager::Input(float DeltaTime)
{

    FVector2D PlayerMoveDir = { 0.f, 0.f };

    // GetAsyncKeyState 이걸 통해서 키 입력을 확인할 수 있다.
    //W A S D 이동 
    if (GetAsyncKeyState('W') & 0x8000)
    {
        //W키가 눌려있음 
        /*mRC.Top -= 400.f * DeltaTime;
        mRC.Bottom -= 400.f * DeltaTime;*/

        // mPlayerPos.y -= 400.f * DeltaTime;

        PlayerMoveDir.y -= 1.f;
    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        //W키가 눌려있음 
        /*mRC.Top += 400.f * DeltaTime;
        mRC.Bottom += 400.f * DeltaTime;*/
        //mPlayerPos.y += 400.f * DeltaTime;

        PlayerMoveDir.y += 1.f;
    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        //W키가 눌려있음 
        /*mRC.Left -= 400.f * DeltaTime;
        mRC.Right -= 400.f * DeltaTime;*/

        //mPlayerPos.x -= 400.f * DeltaTime;
        PlayerMoveDir.x -= 1.f;
    }

    if (GetAsyncKeyState('D') & 0x8000)
    {
        //W키가 눌려있음 
    /*	mRC.Left += 400.f * DeltaTime;
        mRC.Right += 400.f * DeltaTime;*/
        //mPlayerPos.x += 400.f * DeltaTime;

        PlayerMoveDir.x += 1.f;
    }

    PlayerMoveDir.Normalize();
    mPlayerPos += PlayerMoveDir * 400.f * DeltaTime;

    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        ////이때 총알을 발사하고싶다. 
        //FRect Bullet = {};

        //Bullet.Left = mRC.Left + 100.f;
        //Bullet.Top = mRC.Top + 25.f;
        //Bullet.Right = Bullet.Left + 50.f;
        //Bullet.Bottom = Bullet.Top + 50.f;

        //mRectList.push_back(Bullet);

        FBullet Bullet;

        Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = mPlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDir = FVector2D(1.f, 0.f);
        Bullet.Distance = 1000;

        mBulletList.push_back(Bullet);

    }

    //플레이어 스킬 
    // 산탄
    if (GetAsyncKeyState('1') & 0x8000)
    {
        for (int i = 0; i < 3; ++i)
        {
            FBullet Bullet;

            Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
            Bullet.Pos.y = mPlayerPos.y;

            Bullet.Size = FVector2D(50.f, 50.f);
            Bullet.MoveDir = FVector2D(1.f, i - 1.f);	// 0 : -1 , 1: 0,  2 : 1
            Bullet.MoveDir.Normalize();
            Bullet.Distance = 1000;

            mBulletList.push_back(Bullet);
        }
    }
    // 8방향
    if (GetAsyncKeyState('2') & 0x8000)
    {
        FVector2D Dir[8] =
        {
            {1.f, 0.f}, //우
            {1.f, 1.f}, //우 하
            {0.f, 1.f}, // 하
            {-1.f, 1.f}, // 좌 하
            {-1.f, 0.f}, // 좌
            {-1.f, -1.f}, //좌 상
            {0.f, -1.f}, // 상
            {1.f, -1.f}, // 우 상
        };

        for (int i = 0; i < 8; ++i)
        {
            FBullet Bullet;

            Bullet.Pos.x = mPlayerPos.x;
            Bullet.Pos.y = mPlayerPos.y;

            Bullet.Size = FVector2D(50.f, 50.f);
            Bullet.MoveDir = Dir[i];
            Bullet.MoveDir.Normalize();
            Bullet.Distance = 1000;

            mBulletList.push_back(Bullet);
        }
    }
    // 가능하신분들은 총알 팅기기? 
    if (GetAsyncKeyState('3') & 0x8000)
    {

        FBullet Bullet;

        Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = mPlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDir = FVector2D(1.f, 1.f);
        Bullet.MoveDir.Normalize();
        Bullet.Distance = FLT_MAX;	// float MAX
        Bullet.Option = EBulletOption::Bound;

        mBulletList.push_back(Bullet);
    }

    if (GetAsyncKeyState('4') & 0x8000)
    {
        FBullet Bullet;

        Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = mPlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDir = FVector2D(0.5f, 0.f);
        Bullet.MoveDir.Normalize();
        Bullet.Distance = FLT_MAX;	// float MAX
        Bullet.Option = EBulletOption::Wave;

        mBulletList.push_back(Bullet);
    }
}

void CGameManager::Update(float DeltaTime)
{
    // 매번 갱신 되어야 하는 것들
    std::list<FBullet>::iterator iter = mBulletList.begin();
    std::list<FBullet>::iterator iterEnd = mBulletList.end();

    for (; iter != iterEnd;)
    {
        FBullet& Bullet = *iter;
        /*Bullet.Left += 600.f * DeltaTime;
        Bullet.Right += 600.f * DeltaTime;*/

        // 기존 위치 + 원하는 방향 * 원하는 속도 * 델타타임
        // Bullet.Pos += Bullet.MoveDir * 500.f * DeltaTime;

        FVector2D Move = Bullet.MoveDir * 500.f * DeltaTime;

        Bullet.Pos += Move;

        //거리만큼만 이동하겠다. 
        float Dist = Move.Length();	//총알이 현재 이동한거리 
        Bullet.Distance -= Dist;
        if (Bullet.Distance <= 0.f)	//거리가 멀어지면 삭제
        {
            iter = mBulletList.erase(iter);
            iterEnd = mBulletList.end();
            continue;
        }

        if (Bullet.Option == EBulletOption::Bound)
        {
            FVector2D Normal;
            //벽에 부딪혔는지 판단한다. 
            if (Bullet.Pos.x - Bullet.Size.x / 2.f <= 0) //왼쪽 벽
            {
                Bullet.MoveDir.x = 1.f;
            }
            else if (Bullet.Pos.x + Bullet.Size.x / 2.f >= 1280.f) //오른쪽 벽 
            {
                Bullet.MoveDir.x = -1;
            }
            else if (Bullet.Pos.y - Bullet.Size.y / 2 <= 0.f) //위 벽 
            {
                Bullet.MoveDir.y = 1.f;
            }
            else if (Bullet.Pos.y + Bullet.Size.y / 2 >= 720.f)	//아래 벽
            {
                Bullet.MoveDir.y = -1.f;
            }
        }

        if (Bullet.Option == EBulletOption::Wave)
        {
            Bullet.AccTime += DeltaTime;
            //Bullet.Pos.y += 3 *			sinf(20*Bullet.AccTime);
            //				  그래프 진폭      주기
            Bullet.Pos.y += 3 * cosf(20 * Bullet.AccTime);
        }

        ++iter;
    }

    // 적이 일정 시간마다 총알을 발사한다.
    // mFireAccTime += DeltaTime;  // 시간 누적

    mEnemyPos.y += mEnemyDir * 300 * DeltaTime;

    //if (mFireAccTime >= mFireTime)
    //{
    //    mFireAccTime -= mFireTime;

    //    // 총알 생성
    //    FRects Bullet = {};

    //    Bullet.Left = mEnemy.Left - 50.f;
    //    Bullet.Top = mEnemy.Top + 25.f;
    //    Bullet.Right = mEnemy.Left;
    //    Bullet.Bottom = Bullet.Top + 50.f;

    //    mEnemyBulletList.push_back(Bullet);
    //}

    ////적 총알 발사 
    //std::list<FRects>::iterator iter1 = mEnemyBulletList.begin();
    //std::list<FRects>::iterator iterEnd1 = mEnemyBulletList.end();

    //for (; iter1 != iterEnd1; ++iter1)
    //{
    //    FRects& Bullet = *iter1;
    //    Bullet.Left -= 600.f * DeltaTime;
    //    Bullet.Right -= 600.f * DeltaTime;
    //}

    if (mEnemyPos.y + mEnemySize.y / 2.f >= 720.f)	//아래 닿음
    {
        mEnemyPos.y = 670.f;
        mEnemyDir = -1.f;
    }
    else if (mEnemyPos.y - mEnemySize.y / 2.f <= 0) //화면 위에 닿음 
    {
        mEnemyPos.y = 50.f;
        mEnemyDir = 1.f;
    }

    //적이 일정 시간마다 총알을 발사한다. 
    mFireAccTime += DeltaTime; //시간을 누적한다. 

    if (mFireAccTime >= mFireTime)
    {
        mFireAccTime -= mFireTime;

        //총알 생성 
        FBullet Bullet = {};
        Bullet.Pos.x = mEnemyPos.x - mEnemySize.x / 2.f - 25.f;
        Bullet.Pos.y = mEnemyPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        //총알 방향은 플레이어 에게 향하고 싶다. 
        // 플레이어로 향하는 방향 벡터 -> 플레이어 위치 - 적 위치
        Bullet.MoveDir = mPlayerPos - mEnemyPos;
        Bullet.MoveDir.Normalize();	// 정규화 : 적 -> 플레이어로 가는 단위 벡터를 계산해준다. 
        Bullet.Distance = 2000;

        mEnemyBulletList.push_back(Bullet);
    }

    //적 총알 발사 
    //적 총알 거리 제한하고 삭제하기 
    // 총알이 화면 밖으로 나가면 삭제하기 

    std::list<FBullet>::iterator iter1 = mEnemyBulletList.begin();
    std::list<FBullet>::iterator iterEnd1 = mEnemyBulletList.end();

    for (; iter1 != iterEnd1;)
    {
        FBullet& Bullet = *iter1;
        //한 프레임당 이동량을 구한다.
        FVector2D Move = Bullet.MoveDir * 500.f * DeltaTime;	// 방향 * 속도 * 델타타임 => 이번 프레임에서 이동할 속력 
        Bullet.Pos += Move;

        //거리 제한 
        Bullet.Distance -= Move.Length();

        if (Bullet.Distance <= 0.f) // 거리제한 완료 
        {
            iter1 = mEnemyBulletList.erase(iter1);
            iterEnd1 = mEnemyBulletList.end();
            continue;
        }

        //화면밖에 나갔을때 총알 삭제하기
        // 직접 플레이어 나가는거 적용해보자 
        if (Bullet.Pos.x + Bullet.Size.x / 2.f <= 0.f ||
            Bullet.Pos.x - Bullet.Size.x / 2.f >= 1280.f ||
            Bullet.Pos.y + Bullet.Size.y / 2.f <= 0.f ||
            Bullet.Pos.y - Bullet.Size.y / 2.f >= 720.f)
        {
            iter1 = mEnemyBulletList.erase(iter1);
            iterEnd1 = mEnemyBulletList.end();
            continue;
        }
        ++iter1;
    }
}

void CGameManager::PostUpdate(float DeltaTime)
{
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::PostCollisionUpdate(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
    //// Rectangle(mhDC, (int)mRC.Left, (int)mRC.Top, (int)mRC.Right, (int)mRC.Bottom);

    //Rectangle(mhDC, (int)(mPlayerPos.x - mPlayerSize.x / 2.f),
    //    (int)(mPlayerPos.y - mPlayerSize.y / 2),
    //    (int)(mPlayerPos.x + mPlayerSize.x / 2.f),
    //    (int)(mPlayerPos.y + mPlayerSize.y / 2));

    //// 총알
    //std::list<FBullet>::iterator iter = mBulletList.begin();    // 맨 앞을 가리키는 반복자
    //std::list<FBullet>::iterator iterEnd = mBulletList.end();	// 마감 
    //for (; iter != iterEnd; ++iter)
    //{
    //    FBullet& Bullet = *iter;
    //    
    //    //Ellipse(mhDC, (int)Bullet.Left, (int)Bullet.Top, (int)Bullet.Right, (int)Bullet.Bottom);

    //    Ellipse(mhDC, (int)(Bullet.Pos.x - Bullet.Size.x / 2.f),
    //        (int)(Bullet.Pos.y - Bullet.Size.y / 2),
    //        (int)(Bullet.Pos.x + Bullet.Size.x / 2.f),
    //        (int)(Bullet.Pos.y + Bullet.Size.y / 2));
    //}

    //// 적
    ///*Rectangle(mhDC, (int)mEnemy.Left, (int)mEnemy.Top, (int)mEnemy.Right, (int)mEnemy.Bottom);*/
    ////Rectangle(mhDC, (int)(mEnemyPos.x - mEnemySize.x / 2.f),
    ////    (int)(mEnemyPos.y - mEnemySize.y / 2),
    ////    (int)(mEnemyPos.x + mEnemySize.x / 2.f),
    ////    (int)(mEnemyPos.y + mEnemySize.y / 2));

    ////std::list<FRects>::iterator iter1 = mEnemyBulletList.begin();    // 맨 앞을 가리키는 반복자
    ////std::list<FRects>::iterator iterEnd1 = mEnemyBulletList.end();	// 마감

    //Rectangle(mhDC, (int)(mEnemyPos.x - mEnemySize.x / 2.f),
    //    (int)(mEnemyPos.y - mEnemySize.y / 2),
    //    (int)(mEnemyPos.x + mEnemySize.x / 2.f),
    //    (int)(mEnemyPos.y + mEnemySize.y / 2));

    ////적 총알 발사 
    //std::list<FBullet>::iterator iter1 = mEnemyBulletList.begin();
    //std::list<FBullet>::iterator iterEnd1 = mEnemyBulletList.end();

    ///*for (; iter1 != iterEnd1; iter1++)
    //{
    //    FRects& Bullet = *iter1;

    //    Ellipse(mhDC, (int)Bullet.Left, (int)Bullet.Top, (int)Bullet.Right, (int)Bullet.Bottom);
    //}*/
    //
    //for (; iter1 != iterEnd1; ++iter1)
    //{
    //    FBullet& Bullet = *iter1;
    //    Ellipse(mhDC, (int)(Bullet.Pos.x - Bullet.Size.x / 2.f),
    //        (int)(Bullet.Pos.y - Bullet.Size.y / 2),
    //        (int)(Bullet.Pos.x + Bullet.Size.x / 2.f),
    //        (int)(Bullet.Pos.y + Bullet.Size.y / 2));
    //}

    //새로운 도화지 준비 
    static bool t = true;
    if (t)
    {
        CDevice::GetInst()->ClearBackBuffer(mClearColor);
        t = false;
    }
    else
    {
        float color[4] = { 0.f,0.f,0.f,1.f };
        CDevice::GetInst()->ClearBackBuffer(color);
        t = true;
    }

    CDevice::GetInst()->ClearBackBuffer(mClearColor);
    CDevice::GetInst()->ClearDepthStencil(1.f, 0);
    CDevice::GetInst()->SetTarget();

    CDevice::GetInst()->Render();
     
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

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;

    //    HDC hdc = BeginPaint(mhWnd, &ps);


    //    //텍스트 출력 
    //    TextOut(hdc, 10, 10, L"Output", 6);
    //    TextOut(hdc, 100, 100, TEXT("Output"), 6);

    //    //사각형 그리기 
    //    Rectangle(hdc, 100, 200, 200, 300);
    //    Ellipse(hdc, 100, 200, 200, 300);

    //    //선 그리기
    //    //선 시작점 
    //    MoveToEx(hdc, 200, 100, nullptr);   //선의 시작점 
    //    LineTo(hdc, 300, 200);
    //    LineTo(hdc, 400, 100);

    //    MoveToEx(hdc, 300, 300, nullptr);
    //    LineTo(hdc, 400, 300);

    //    

    //    EndPaint(mhWnd, &ps);
    //}
    break;
    case WM_DESTROY:
        mLoop = false;      // 윈도우를 종료하게 되면 루프를 종료 해준다.
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
