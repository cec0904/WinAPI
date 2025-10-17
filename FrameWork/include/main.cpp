// 중간 디렉터리 -> 부산물
// debug -> 개발용
// release -> 배포용(대신 프로그램 속도가 빨라짐, 가벼워지고)

#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    if (!CGameManager::GetInst()->Init(hInstance))
    {
        return 0;
    }

    CGameManager::GetInst()->Run();

    return 0;
}




