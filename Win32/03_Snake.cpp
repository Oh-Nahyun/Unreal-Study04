// 03_Snake.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "03_Snake.h"

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
///// [ 정의 부분 ]

#define SEC                 1000            ///// 타이머 시간 1초

///// 씬 부분 설정
#define LOGO                0               ///// 로고
#define SETTING             1               ///// 설정
#define COUNTDOWN           2               ///// 카운트 다운
#define GAME                3               ///// 게임
#define GAMEOVER            4               ///// 게임오버

#define REGAME              0               ///// 다시 시작 (게임오버 메뉴)
#define EXIT                1               ///// 나가기 (게임오버 메뉴)

///// 타이머
#define LOGO_TIMER          1               ///// 로고 타이머 (뱀이 지나가는 속도 처리)
#define COUNTDOWN_TIMER     2               ///// 카운트 다운 타이머 (게임 시작 전 사용)
#define GAME_TIMER          3               ///// 게임 타이머 (게임에서 사용)

///// 난이도 설정
#define EASY                80              ///// 쉬움 (속도)
#define MEDIUM              60              ///// 보통 (속도)
#define DIFFICULT           40              ///// 어려움 (속도)

///// 초기화 함수 선언
///// void Start_Setting(HWND, int(*)[2], int(*)[2], int*, int*, int*, int*, int*, int*, int*);
void Start_Setting(HWND hwnd, int(*coordinates)[2], int(*items)[2], int* status, int* difficulty, 
    int* menu, int* direction, int* score, int* cnt_circle, int* cnt_item);

///// 게임 종료 함수 선언
void End_Game(HWND hwnd, int score, int* status);
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
    LoadStringW(hInstance, IDC_MY03SNAKE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY03SNAKE));

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

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY03SNAKE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;  ///// MAKEINTRESOURCEW(IDC_MY03SNAKE);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       300, 100, 800, 500,  ///// CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
       nullptr, nullptr, hInstance, nullptr);

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
    ///// ==============================
    HDC hdc, memdc;                 ///// 디바이스 컨텍스트, 메모리 디바이스 컨텍스트
    HFONT hFont, oldFont;           ///// 폰트
    HBRUSH hBrush = nullptr, oldBrush = nullptr;        ///// 브러쉬
    HPEN hPen, oldPen;              ///// 펜
    HBITMAP hBit, oldBit;           ///// 비트맵

    static RECT rectView;           ///// 화면 사이즈 & 체크 용도
    static TCHAR buffer[100];       ///// 문자, 설명, 점수 등등 문자 출력에 사용할 문자열
    
    ///// 게임 데이터
    static int coordinates[12][2] = { 0, };    ///// 캐릭터 좌표
    static int items[10][2] = { 0, };          ///// 아이템 좌표
    
    static int status;              ///// 게임 상태 (씬)
    static int difficulty;          ///// 난이도 (속도)
    static int minus;               ///// 감소폭
    static int cnt_time = 3;        ///// 카운트 다운 시간 조정 (기본 3초)
    static int cnt_item;            ///// 아이템의 갯수
    static int cnt_circle;          ///// 몸통의 길이 (원의 갯수)
    static int score;               ///// 점수
    static int direction;           ///// 방향
    static int menu;                ///// 메뉴
    
    int i, x;                       ///// 반복문 사용, x좌표를 담는 용도
    
    srand((unsigned)time(NULL));    ///// 랜덤 초기화
    ///// ==============================

    switch (message)
    {
    ///// ==============================
    case WM_CREATE:
        {
            ///// 윈도우 사이즈 가져오기
            GetClientRect(hWnd, &rectView);

            ///// 게임 데이터 초기화!!! (+ 시작)
            Start_Setting(hWnd, coordinates, items, &status, &difficulty, &menu, &direction, &score, &cnt_circle, &cnt_item);
        }
        break;
    ///// ==============================
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
    ///// ==============================
    ///// WM_PAINT
    case WM_PAINT:
        {
            PAINTSTRUCT ps;                     //
            HDC hdc = BeginPaint(hWnd, &ps);    //
            
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            ///// 상태에 따라 처리하는 부분..
            switch (status)
            {
                case LOGO:                      ///// 게임 시작 화면
                    {
                        ///// 뱀 그리기 & 애니메이션
                        for (i = 0; i < cnt_circle; i++)
                        {
                            hBrush = CreateSolidBrush(RGB(0, 90 + (i * 15), 0));    ///// 점점 진해지는 연두색
                            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

                            Ellipse(hdc, coordinates[i][0] - 10, coordinates[i][i] - 10, coordinates[i][0] + 10, coordinates[i][i] + 10);
                        }

                        SelectObject(hdc, oldBrush);
                        DeleteObject(hBrush);
                        DeleteObject(oldBrush);
                        
                        ///// ------------------------------
                        ///// 글자 출력하기
                        hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, _T("새굴림"));    ///// (((..., HANGUL_CHARSET, ..., L"새굴림"으로 변경 가능)))
                        oldFont = (HFONT)SelectObject(hdc, hFont);

                        TextOut(hdc, 270, 250, _T("스네이크 게임"), _tcslen(_T("스네이크 게임")));

                        hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, _T("새굴림"));
                        SelectObject(hdc, hFont);

                        TextOut(hdc, 330, 320, _T("Press Any Key"), _tcslen(_T("Press Any Key")));

                        SelectObject(hdc, oldFont);
                        DeleteObject(hFont);
                        DeleteObject(oldFont);
                    }
                    break;
                case SETTING:                   ///// 게임 세팅
                    {

                    }
                    break;
                case COUNTDOWN:                 ///// 카운트 다운 보여주기
                    {

                    }
                    break;
                case GAME:                      ///// 게임 플레이 화면 그리기
                    {

                    }
                    break;
                case GAMEOVER:                  ///// 게임 오버 & 메뉴 선택 화면
                    {

                    }
                    break;
            }

            EndPaint(hWnd, &ps);                //
        }
        break;
    ///// ==============================
    ///// WM_KEYDOWN
    case WM_KEYDOWN:
        {
            ///// 상태에 따라 처리하는 부분..
            switch (status)
            {
                case LOGO:                      ///// 로고 상태일 경우 입력이 있다면..
                    {
                        
                    }
                    break;
                case SETTING:                   ///// 게임 세팅. 난이도 설정, 엔터키가 눌리면 설정 적용 -> 다음 씬으로 이동
                    {
                        
                    }
                    break;
                case GAME:                      ///// 게임 입력 받은 후 -> GAME_TIMER 에서 후처리
                    {
                        
                    }
                    break;
                case GAMEOVER:                  ///// 게임 오버 메뉴 선택창 (엔터로 설정 적용)
                    {
                        
                    }
                    break;
            }
        }
        break;
    ///// ==============================
    ///// WM_TIMER
    case WM_TIMER:
        {
            ///// 상태에 따라 처리하는 부분..
            switch (status)
            {
                case LOGO_TIMER:                ///// 뱀의 이동 처리 (게임의 킥. loading을 나타낸다.)
                    {
                        InvalidateRect(hWnd, NULL, TRUE);   ///// 다시 그려라
                    }
                    break;
                case COUNTDOWN_TIMER:           ///// 카운트 다운 타이머
                    {
                        
                    }
                    break;
                case GAME_TIMER:                ///// 게임 속도, 방향에 따른 처리
                    {
                        
                    }
                    break;
            }
        }
        break;
    ///// ==============================
    case WM_DESTROY:
        ///// ==============================
        ///// 임시...
        KillTimer(hWnd, LOGO_TIMER);
        ///// ==============================

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

///// <summary>
///// 게임 시작할 때 세팅해주는 함수
///// </summary>
void Start_Setting(HWND hwnd, int(*coordinates)[2], int(*items)[2], int* status, int* difficulty, int* menu, int* direction, int* score, int* cnt_circle, int* cnt_item)
{
    int i = 0, x = 0;

    *status = LOGO;                 ///// 처음 화면은 로고
    /////*status = GAME;            ///// 게임만 테스트 하는 경우 사용

    *difficulty = EASY;             ///// 난이도는 '쉬움'으로 초기화
    *menu = REGAME;                 ///// 메뉴는 '다시 시작'으로 초기화

    *score = 10000;                 ///// 게임 시작 시 기본 점수
    *direction = VK_RIGHT;          ///// 게임 시작 시 진행 방향

    *cnt_item = 10;                 ///// 게임 아이템의 갯수
    *cnt_circle = 12;               ///// 로고 화면에 나오는 뱀의 길이

    ///// 아이템 랜덤 배치하기
    for (i = 0; i < 10; i++)
    {
        items[i][0] = (rand() % 36) * 20 + 30;
        items[i][1] = (rand() % 20) * 20 + 30;
    }

    ///// 로고에서 뱀 보여주기
    for (i = *cnt_circle - 1; i >= 0; i--)
    {
        coordinates[i][0] = x;
        coordinates[i][1] = 100;    ///// (((y)))
        x += 20;
    }

    ///// 타이머 발동하기
    SetTimer(hwnd, LOGO_TIMER, 200, NULL);
}

///// <summary>
///// 
///// </summary>
void End_Game(HWND hwnd, int score, int* status)
{

}
