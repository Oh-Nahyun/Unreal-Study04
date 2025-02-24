// 02_Omok.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "02_Omok.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

///// ==============================
///// 가로, 세로 줄이 19개인 바둑판 사용
#define X_COUNT         19
#define Y_COUNT         19

///// 바둑판의 여백
#define START_X         50
#define START_Y         50

///// 줄 사이의 간격
#define INTERVAL        26

///// 바둑돌의 반지름
#define HALF_INTERVAL   INTERVAL/2

///// 실제로 놓일 위치값 (매크로 함수)
#define XPOS(x)         (START_X + (x) * INTERVAL)
#define YPOS(y)         (START_Y + (y) * INTERVAL)
///// ==============================
///// 바둑판 데이터 (0 = 빈곳, 1 = 검은돌, 2 = 흰돌)
unsigned char g_dol[Y_COUNT][X_COUNT];

///// 현재 어떤 돌을 놓을 차례인지를 결정하는 턴 (0 = 검은돌, 1 = 흰돌)
unsigned char g_step;
///// ==============================
///// 배경색으로 사용할 브러쉬
HBRUSH h_bk_brush;

///// 마우스 클릭 영역 체크 함수
void OnLButtonDown(HWND hWnd, int _x, int _y);

///// 승패 처리 함수 (착점할 때마다 확인하는 방법!!)
int CheckPointer(HWND hWnd, int _x, int _y, int _Stone);
///// ==============================

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY02OMOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY02OMOK));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    ///// ==============================
    ///// 배경색으로 사용할 브러쉬
    h_bk_brush = CreateSolidBrush(RGB(242, 176, 109));
    ///// ==============================

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY02OMOK));
    //wcex.hCursor      = LoadCursor(nullptr, IDC_ARROW);
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);   /////
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.hbrBackground    = h_bk_brush;                     /////
    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY02OMOK);
    wcex.lpszMenuName   = NULL;                             /////
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, 
                            szTitle, 
                            WS_OVERLAPPEDWINDOW, 
                            400, 100, 580, 600, 
                            nullptr, nullptr, 
                            hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            ///// ==============================
            ///// [ 바둑판 선그리는 부분 ]
            
            ///// 수직으로 19개의 선을 그린다.
            for (int x = 0; x < X_COUNT; x++)
            {
                MoveToEx(hdc, XPOS(x), YPOS(0), NULL);
                LineTo(hdc, XPOS(x), YPOS(Y_COUNT - 1));
            }

            ///// 수평으로 19개의 선을 그린다.
            for (int y = 0; y < Y_COUNT; y++)
            {
                MoveToEx(hdc, XPOS(0), YPOS(y), NULL);
                LineTo(hdc, XPOS(X_COUNT - 1), YPOS(y));
            }
            ///// ==============================
            ///// [ 바둑판 위 바둑돌 그리는 부분 ]
            
            ///// ------------------------------
            ///// TEST DATA
            g_dol[0][0] = 1;
            g_dol[1][1] = 2;
            g_dol[2][2] = 0;
            g_dol[3][3] = 2;
            g_dol[4][4] = 1;
            ///// ------------------------------

            for (int y = 0; y < Y_COUNT; y++)
            {
                for (int x = 0; x < X_COUNT; x++)
                {
                    ///// 바둑돌이 놓여져 있는 경우 (바둑판 데이터 : 0 = 빈곳, 1 = 검은돌, 2 = 흰돌) -> 브러쉬 색 변경
                    if (g_dol[y][x] > 0)
                    {
                        ///// 바둑돌 색 변경하기
                        if (g_dol[y][x] == 1)   ///// 흑돌
                        {
                            SelectObject(hdc, GetStockObject(BLACK_BRUSH));
                        }
                        else                    ///// 백돌
                        {
                            SelectObject(hdc, GetStockObject(WHITE_BRUSH));
                        }

                        ///// 바둑돌이 놓여질 위치를 계산한다.
                        ///// x, y를 중심으로 변경. 원을 출력해보자.
                        Ellipse(hdc,
                            /////XPOS(x), YPOS(y), XPOS(x) + INTERVAL, YPOS(y) + INTERVAL);
                            XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL, XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL);
                    }
                }
            }
            ///// ==============================

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void OnLButtonDown(HWND hWnd, int _x, int _y)
{
}

int CheckPointer(HWND hWnd, int _x, int _y, int _Stone)
{
    return 0;
}

