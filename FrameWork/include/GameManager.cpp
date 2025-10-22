#include "GameManager.h"
#include "resource.h"

#include "Share/Timer.h"
#include "Device.h"

#include "Asset/AssetManager.h"
#include "Asset/Mesh/MeshManager.h"
#include "Asset/Mesh/Mesh.h"

#include "Shader/ShaderManager.h"
#include "Shader/Shader.h"

#include "Shader/TransformCBuffer.h"

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
}

void CGameManager::Update(float DeltaTime)
{
   
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
    // 새로운 도화지 준비
    CDevice::GetInst()->ClearBackBuffer(mClearColor);
    CDevice::GetInst()->ClearDepthStencil(1.f, 0);
    CDevice::GetInst()->SetTarget();

    // 준비된 도화지에 출력
    static CTransformCBuffer buffer;
    static FVector3D Pos, Rot;

    Pos.z = 5.f;

    if (GetAsyncKeyState('W') & 0x8000)
    {
        Pos.y += 1.f * DeltaTime;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        Pos.y -= 1.f * DeltaTime;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        Rot.y += 90.f * DeltaTime;
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        Rot.y -= 90.f * DeltaTime;
    }

    buffer.Init();

    FMatrix matWorld, matProj;
    FMatrix matScale, matRot, matTranslate;

    matScale.Scaling(5.f, 5.f, 5.f);
    matRot.Rotation(Rot);
    matTranslate.Translation(Pos);

    matWorld = matScale * matRot * matTranslate;
    // 원근 투영 행렬을 만들어준다.
    // 시야각, 종횡비, 근평원, 원평원
    matProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90.f), 1280.f / 720.f, 0.5f, 1000.f);

    buffer.SetWorldMatrix(matWorld);
    buffer.SetProjMatrix(matProj);
    buffer.UpdateBuffer();


    CSharedPtr<CShader> Shader = CShaderManager::GetInst()->FindShader("ColorMeshShader");
    CSharedPtr<CMesh> Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("CenterRect");

    Shader->SetShader();
    Mesh->Render();


    // 도화지에 다 그렸으면 출력할거다. 
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
