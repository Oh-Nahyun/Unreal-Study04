// 04_Poop.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

///// ==============================
///// [ 구성 요소 ]
///// 1. 게임 매니저 구성하기 
///// 2. 이미지 출력하기
///// 3. 물리(수학) 처리하기
///// 4. 플레이어 관련 클래스
///// 5. 오브젝트 관련 클래스
///// 6. 적(똥) 클래스
///// ==============================

#include "framework.h"
#include "04_Poop.h"

#define MAX_LOADSTRING 100

///// 전역 변수:
HWND		g_hWnd;
HINSTANCE	g_hInst;

LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

///// wWinMain  : 유니코드 버전의 Winmain
///// _tWinMain : 매크로 이며 유니코드인 경우에는 wWinMain, 아닌 경우에는 WinMain 으로 전처리 된다.
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    ///// 이름
    TCHAR szWindowsName[128] = TEXT("Game Windows");
    TCHAR szClassName[128] = TEXT("My Class");

    ///// 윈도우 사이즈
    int nWidth = WINSIZEX + GetSystemMetrics(SM_CXBORDER) * 2;
    int nHeight = WINSIZEY + GetSystemMetrics(SM_CYBORDER) * 2 + GetSystemMetrics(SM_CYCAPTION);

    ///// 윈도우 클래스 정의
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)MsgProc;    ///// WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY04POOP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;               ///// MAKEINTRESOURCEW(IDC_MY04POOP);
    wcex.lpszClassName = szClassName;       ///// szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    ///// 윈도우 클래스 등록하기
    RegisterClassExW(&wcex);

    ///// 메모리 상에 윈도우 만들기
    HWND hWnd = CreateWindow(szClassName, szWindowsName, WS_OVERLAPPEDWINDOW,
                            0, 0, nWidth, nHeight, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    g_hWnd = hWnd;
    g_hInst = hInstance;
    
    ///// 게임 매니저 생성!!! ( + 초기화 )
    CGameManager GameManager;
    if (!GameManager.Init())
        return FALSE;

    ///// 모니터 화면의 중앙 좌표로 이동하기
    RECT rcWindowsBounds;
    GetWindowRect(g_hWnd, &rcWindowsBounds);

    int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    int iDestX = (iScreenWidth  - (rcWindowsBounds.right - rcWindowsBounds.left)) / 2;
    int iDestY = (iScreenHeight - (rcWindowsBounds.bottom - rcWindowsBounds.top)) / 2;

    MoveWindow(hWnd, iDestX, iDestY, rcWindowsBounds.right - rcWindowsBounds.left, rcWindowsBounds.bottom - rcWindowsBounds.top, true);
    
    ///// 윈도우를 화면에 표시하기
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    ///// 사용자로부터 메시지 처리하기
    MSG msg;

    ///// 메시지 루프 (튜닝)
    while (true)
    {
        ///// 메시지 큐에 메시지가 있다면 메시지 처리하기
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        ///// 메시지가 없는 경우, 항상 실행하기
        else
        {
            ///// 게임 그리기 (Rendering)
            GameManager.Render();

            ///// 게임 정보 업데이트 (Data Update)
            GameManager.Update();
        }
    }

    return (int) msg.wParam;
}



// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
