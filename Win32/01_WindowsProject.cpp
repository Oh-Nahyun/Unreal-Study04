// 01_WindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "01_WindowsProject.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

///// ==============================

///// 클래스 : 객체를 만들기 위한 설계도
///// 객체 (Object) : 소프트웨어 (구현할 대상), 클래스의 인스턴스 (Instance)
///// 인스턴스 (Instance) : 구현된 구체적인 실체.
/////                       OOP의 관점에서 객체가 메모리에 할당되어 실제 사용될 때, 이를 '인스턴스'라 한다.
/////                       원본 (추상적인 개념) 으로 부터 '생성된 복제본'을 의미한다.

///// ------------------------------

///// (((윈도우에서 실행하는 프로그램 마다 인스턴스 아이디는 같은 값을 가진다.)))
///// (((만약, 같은 프로그램을 여러 창으로 열면 인스턴스 아이디는 같지만, 프로세스 아이디는 모두 다른 것이다.)))

///// ==============================

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,             ///// 프로그램의 인스턴트 핸들, Instance Handle 값이 전달된다.
                     _In_opt_ HINSTANCE hPrevInstance,      ///// 바로 앞에 실행된 프로그램의 인스턴트 핸들
                     _In_ LPWSTR    lpCmdLine,              ///// argv 인수 (도스) 프로그램에 인수와 같다. (int main(int ver) -windows, -debug)
                     _In_ int       nCmdShow)               ///// 프로그램이 실행될 형태 (보통 모양 등이 전달된다.)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY01WINDOWSPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY01WINDOWSPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))                         ///// 시스템이 유지하는 메시지 큐에서 메시지를 읽어들인다. ((예시) WM_QUIT)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);                                 ///// 키보드 입력 메시지를 가공하여 프로그램에서 쓸 수 있도록 해준다.
                                                                    ///// 전달된 메시지가 WM_KEYDOWN 인지 또는 문자 키인지 검사 후 맞을 경우, 메시지 큐에 전달한다.
            DispatchMessage(&msg);                                  ///// 문자 입력이 아닌 경우, 디스패쳐를 통해 Proc(프로시저)로 전해진다.
        }
    }

    ///// ==============================

    ///// Message structure

    /*
    typedef struct tagMSG {
        HWND        hwnd;           ///// 메시지를 받을 윈도우 핸들
        UINT        message;        ///// 어떤 종류의 메시지인지 나타낸다. (가장 중요!!)
        WPARAM      wParam;         ///// 32비트 값. 부가적인 정보를 나타낸다. (메시지마다 다르다.)
        LPARAM      lParam;         ///// 32비트 값. 부가적인 정보를 나타낸다. (메시지마다 다르다.)
        DWORD       time;           ///// 메시지가 발생한 시간
        POINT       pt;             ///// 메시지가 발생했을 때 마우스 위치
    } MSG, * PMSG, NEAR* NPMSG, FAR* LPMSG;
    */

    ///// ------------------------------

    ///// 메시지 예시

    ///// WM_QUIT;                  ///// 프로그램을 끝낼 때 발생하는 메시지
    ///// WM_LBUTTONDOWN;           ///// 마우스 좌측 버튼을 누를 경우 발생하는 메시지
    ///// WM_CHAR;                  ///// 키보드로부터 문자가 입력 되었을 때 발생하는 메시지
    ///// WM_PAINT;                 ///// 화면을 다시 그려야 할 필요가 있을 때 발생하는 메시지
    ///// WM_DESTROY;               ///// 윈도우가 메모리에서 파괴될 때 발생하는 메시지
    ///// WM_CREATE;                ///// 윈도우가 처음 만들어질 때 발생하는 메시지

    ///// ==============================

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

    //wcex.style        = CS_HREDRAW | CS_VREDRAW;                  ///// 윈도우 스타일. 수직/수평 크기가 변할 경우, 다시 그린다.
    ///// #9. 더블클릭
    ///// wcex.cbSize   = CS_DBLCLKS;                               ///// 더블 클릭 마우스 이벤트 추가
    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;     /////
    wcex.lpfnWndProc    = WndProc;                                  ///// 메시지 처리 함수를 지정한다.
    wcex.cbClsExtra     = 0;                                        ///// 사용될 클래스의 보조 메모리를 할당할 때 사용한다.
    wcex.cbWndExtra     = 0;                                        ///// 사용될 윈도우 보조 메모리를 할당한다.
    wcex.hInstance      = hInstance;                                ///// 이 윈도우 클래스를 사용하는 프로그램의 번호!!! (많이 사용한다.)
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY01WINDOWSPROJECT)); ///// 사용할 아이콘
    //wcex.hCursor      = LoadCursor(nullptr, IDC_ARROW);           ///// 사용할 마우스 커서!!
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);           /////
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);               ///// 윈도우 배경색
    wcex.hbrBackground  = (HBRUSH)GetStockObject(LTGRAY_BRUSH);     /////
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY01WINDOWSPROJECT); ///// 윈도우 메뉴
    ///// wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;                            ///// 윈도우 클래스 이름. CreateWindows 함수로 전달된다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));         ///// 작은 아이콘

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

   HWND hWnd = CreateWindowW(szWindowClass,                             ///// 생성하는 윈도우 클래스를 지정!!!
                            //szTitle,                                  ///// 타이틀 바에 나오는 이름 ((( (아래 예시)   L"테스트윈도우",   로 변경 가능)))
                            L"테스트윈도우",                            /////
                            //WS_OVERLAPPEDWINDOW,                      ///// 윈도우 형태를 지정하는 함수
                            ///// WS_OVERLAPPEDWINDOW | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_MAXIMIZE,  ///// ((( 윈도우 형태 | 테두리 | 가로 스크롤 | 세로 스크롤 | 최대 크기)))
                            WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,                                  /////
                            //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,       ///// 윈도우 크기와 시작값
                            500, 200, 1400, 800,                        /////
                            nullptr,                                    ///// 부모 윈도우가 있을 경우, 부모 윈도우의 핸들을 지정해준다. (특수)
                            nullptr,                                    ///// 윈도우에서 사용 메뉴의 핸들
                            hInstance,                                  ///// 프로그램의 핸들
                            nullptr);                                   ///// 구조체의 번지, 특수 목적에 사용한다. (보통 NULL)

   if (!hWnd)                   ///// 윈도우 핸들이 없으면 안된다!! (중요)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);  ///// 화면으로 출력하고자 하는 윈도우의 핸들
   UpdateWindow(hWnd);          ///// WM_PAINT 메시지가 대기 상태에 있다면 즉시 수행한다.

   return TRUE;
}

///// ==============================

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)    /////
{
    HDC hdc;
    hdc = GetDC(hWnd);

    ///// 점을 100개씩 랜덤하게 찍는다.
    for (int i = 0; i < 100; i++)
    {
        SetPixel(hdc, rand() % 500, rand() % 100, RGB(rand() % 256, rand() % 256, rand() % 256));
    }

    ReleaseDC(hWnd, hdc);
}

///// ==============================

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
    ///// 기본 DC
    HDC hdc;

    ///// #05. 메시지 박스 (메시지 ID 선언)
    int msgID = 0;

    ///// #06. 문자 입력 변수
    int len = 0;
    static TCHAR m_str[256];

    ///// #07. 키보드 액션 (글자 이동하기)
    static int nX = 0, nY = 0;

    ///// #08. 마우스로 그림 그리기
    static bool m_bDraw = false;            ///// 마우스가 눌린 상태인지 확인할 수 있는 bool 변수 (flag)
    static int m_iX, m_iY;                  ///// 마우스 PosX, PosY 좌표값

    ///// #10. 윈도우 타이머
    static time_t myTime;
    static HANDLE hTimer;
    static HANDLE hTimer2;                  ///// 타이머 추가
    static TCHAR str_time[256];
    SYSTEMTIME st;

    ///// #11. GDI 사용 (색 채우기, 선 색 변경)
    HBRUSH MyBrush, OldBrush;               ///// 브러쉬

    ///// #12. PEN 사용
    HPEN MyPen, OldPen;                     ///// 펜

    ///// #13. 패턴 출력 (PEN, BRUSH)
    RECT testRT = {};
    int nWidth = 100;
    int nHeight = 100;
    ///// ==============================

    switch (message)
    {
    ///// ==============================
    case WM_CREATE: ///// 윈도우 애플리케이션의 시작에 가장 처음으로 발생한다.
        {
            ///// #10. 윈도우 타이머 (생성)

            ///// 타이머 생성 (ID = 1)
            hTimer = (HANDLE)SetTimer(hWnd, 1, 1000, NULL);
            ///// 굳이 시작부터... 1번 타이머를 구동하고 싶다!!!??
            SendMessage(hWnd, WM_TIMER, 1, 0);

            ///// 타이머 생성 (ID = 2)
            hTimer2 = (HANDLE)SetTimer(hWnd, 2, 3000, NULL);
            ///// 굳이 시작부터... 2번 타이머를 구동하고 싶다!!!?? (시작하자마자 사운드 출력!!)
            SendMessage(hWnd, WM_TIMER, 2, 0);

            ///// ------------------------------

            ///// 타이머 프로시저 추가!! 반복 처리를 위한 기능
            SetTimer(hWnd, 3, 100, TimerProc);
        }
        break;
    case WM_TIMER:
        {
            ///// #10. 윈도우 타이머
            switch (wParam)     ///// 타이머 인덱스 (ID)
            {
            case 1:
                ///// 타이머 1번의 발동 지점
                GetLocalTime(&st);
                _stprintf_s(str_time, _T("%d:%d:%d"), st.wHour, st.wMinute, st.wSecond);
                
                ///// WM_PAINT 호출
                InvalidateRect(hWnd, NULL, FALSE);        ///// 화면 갱신 (WM_PAINT) - 지우지 않고, 업데이트 - 작은 부하!
                break;
            case 2:
                ///// 타이머 2번의 발동 지점 (3초마다)
                MessageBeep(0xFFFFFFFF);
                break;
            }
        }
        break;
    ///// ==============================
    case WM_LBUTTONDOWN:
        {
            ///// #01. (TEST) 글자 출력
            hdc = GetDC(hWnd);
            TextOut(hdc, 100, 100, L"Mouse", 5);
            ///// ReleaseDC(hWnd, hdc);

            ///// ------------------------------

            ///// #08. 마우스로 그림 그리기
            ///// lParam (32 bit >> 앞쪽 16 bit = Y Pos, 뒷쪽 16 bit = X Pos)
            ///// wParam (마우스 버튼 상태와 키보드 조합의 상태가 전달된다.)
            ///// MK_CONTROL : Ctrl 키가 눌려져 있다.
            ///// MK_LBUTTON : 마우스 왼쪽 버튼이 눌려져 있다.
            ///// MK_RBUTTON : 마우스 오른쪽 버튼이 눌려져 있다.
            ///// MK_MBUTTON : 마우스 가운데 버튼이 눌려져 있다.
            ///// MK_SHIFT   : Shift 키가 눌려져 있다.

            ///// 마우스 눌림
            m_bDraw = true;

            ///// 마우스 좌표를 업데이트
            m_iY = HIWORD(lParam);
            m_iX = LOWORD(lParam);

            ///// (TEST) 마우스 좌표 테스트
            ///// TextOut(hdc, m_iX, m_iY, L"MouseXY", 7);

            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_MOUSEMOVE:
        {
            ///// #08. 마우스로 그림 그리기

            ///// (TEST) 마우스 좌표 테스트 (텍스트)
            /////hdc = GetDC(hWnd);

            ///// 마우스 좌표를 업데이트
            /////m_iY = HIWORD(lParam);
            /////m_iX = LOWORD(lParam);

            ///// 문자 출력
            /////TextOut(hdc, m_iX, m_iY, L"MOUSEMOVE", 9);

            ///// DC 해제하기
            /////ReleaseDC(hWnd, hdc);

            ///// ------------------------------

            ///// 선 그리기
            if (m_bDraw)
            {
                ///// DC 얻어오기
                hdc = GetDC(hWnd);

                ///// 선 그리기의 시작점을 세팅한다.
                MoveToEx(hdc, m_iX, m_iY, NULL);

                ///// 마우스 좌표를 업데이트
                m_iY = HIWORD(lParam);
                m_iX = LOWORD(lParam);

                ///// 선 긋기
                LineTo(hdc, m_iX, m_iY);

                ///// DC 해제하기
                ReleaseDC(hWnd, hdc);
            }
        }
        break;
    case WM_LBUTTONUP:
        {
            ///// #08. 마우스로 그림 그리기
            ///// 마우스가 눌려있다가 떼진 경우, 그리는 동작이 끝났음을 의미
            m_bDraw = false;
        }
        break;
    case WM_LBUTTONDBLCLK:
        {
            ///// #09. 더블 클릭 (화면 지우기)
            ///// 윈도우 스타일에 CS_DBLCLKS 이 추가되어야 한다! ((( wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; )))
            InvalidateRect(hWnd, NULL, TRUE);                 ///// 화면 갱신 (CLS + WM_PAINT) - 지우고, 업데이트
        }
        break;
    ///// ==============================
    case WM_RBUTTONUP:      ///// 윈도우 마우스 액션에서 결정으로 사용된다!! (((UX 내용)))
        {
            ///// #05. 메시지 박스
            ///// MB_ICONEXCLAMATION 또는 MB_ICONWARNING : ! 느낌표
            ///// MB_ICONHAND, MB_ICONSTOP, MB_ICONERROR : X 표시
            ///// MB_ICONQUESTION                        : ? 표시
            ///// MB_ICONASTERISK, MB_ICONINFORMATION    : ! 표시

            ///// 기본
            ///// MessageBox(hWnd, L"TEST", L"TEST_Caption", MB_ICONINFORMATION | MB_CANCELTRYCONTINUE);

            ///// 버튼 처리
            hdc = GetDC(hWnd);
            ///// msgID = MessageBox(hWnd, L"TEST", L"TEST_Caption", MB_ICONWARNING | MB_CANCELTRYCONTINUE);
            msgID = MessageBox(hWnd, L"TEST", L"TEST_Caption", MB_ICONWARNING | MB_YESNO);  ///// 테스트 : MB_OKCANCEL, MB_YESNO
            MessageBeep(MB_ICONERROR);                                                      ///// 비프음 출력
            switch (msgID)
            {
            case IDYES:
                TextOut(hdc, 100, 100, L"YES", 3);
                break;
            case IDNO:
                TextOut(hdc, 100, 100, L"NO", 2);
                break;
            case IDOK:
                TextOut(hdc, 100, 100, L"OK", 2);
                break;
            case IDCANCEL:
                TextOut(hdc, 100, 100, L"CANCEL", 6);
                break;
            case IDTRYAGAIN:
                TextOut(hdc, 100, 100, L"TRYAGAIN", 8);
                break;
            case IDCONTINUE:
                TextOut(hdc, 100, 100, L"CONTINUE", 8);
                break;
            }
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_CHAR:           ///// 아스키 코드 값을 체크한다... (키보드로 문자를 받고자 하는 경우)
        {
            ///// #06. 입력된 키(((보드))) 값들을 화면으로 출력해보자!!!
            ///// len = lstrlen(m_str);
            ///// m_str[len] = (TCHAR)wParam;
            ///// m_str[len + 1] = 0;
            ///// InvalidateRect(hWnd, NULL, FALSE);          ///// 화면 갱신 (WM_PAINT)       - 지우지 않고, 업데이트 - 작은 부하!
            ///// InvalidateRect(hWnd, NULL, TRUE);           ///// 화면 갱신 (CLS + WM_PAINT) - 지우고, 업데이트

            ///// 글자 지우기 (전체)
            if (wParam == 8)                                  ///// 스페이스 키 : 32, 백스페이스 키 : 8
            {
                m_str[0] = 0;
            }
            else
            {
                len = lstrlen(m_str);
                m_str[len] = (TCHAR)wParam;
                m_str[len + 1] = 0;
            }
            InvalidateRect(hWnd, NULL, TRUE);                 ///// 화면 갱신 (CLS + WM_PAINT) - 지우고, 업데이트
        }
        break;
    ///// #07. 키보드 액션
    /////case WM_KEYUP:     ///// 윈도우 기본은 UP이 release!!!
    case WM_KEYDOWN:        ///// 하지만 키보드는 DOWN이 우선시 된다!!! 누르고 있으면 연속적으로 발생한다!!!
        {
            switch (wParam)
            {
            case VK_LEFT:
                nX -= 10;   ///// (((픽셀)))
                break;
            case VK_RIGHT:
                nX += 10;
                break;
            case VK_UP:
                nY -= 10;
                break;
            case VK_DOWN:
                nY += 10;
                break;
            case VK_ESCAPE:                                 ///// ESC 키
                /////PostMessage(hWnd, WM_CLOSE, 0, 0);     ///// 윈도우 메시지 보내기 가능. 윈도우 정상 종료
                PostMessage(hWnd, WM_DESTROY, 0, 0);
                /////PostQuitMessage(0);
                break;
            }
            ///// InvalidateRect(hWnd, NULL, FALSE);        ///// 화면 갱신 (WM_PAINT)       - 지우지 않고, 업데이트 - 작은 부하!
            InvalidateRect(hWnd, NULL, TRUE);               ///// 화면 갱신 (CLS + WM_PAINT) - 지우고, 업데이트
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            ///// ==============================
            ///// #02. TextOut (단문 출력)
            TextOut(hdc, 100, 200, L"Mouse2", 6);
            ///// ------------------------------
            SetTextAlign(hdc, TA_CENTER);
            TextOut(hdc, 100, 250, L"Mouse3", 6);
            TextOut(hdc, 100, 300, L"is 4", 4);
            TextOut(hdc, 100, 350, L"MouseMouse5", 11);
            ///// ==============================
            ///// #03. DrawText (장문 출력)
            RECT rt;
            rt.left = 400;
            rt.top = 100;
            rt.right = 600;
            rt.bottom = 500;
            ///// RECT rt = { 400, 100, 600, 500 };         ///// (((위 코드와 같은 코드)))
            TCHAR str[] = L"가나다라마바사아자차카타파하가나다라마바사아자차카타파하가나다라마바사아자차카타파하";
            DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
            ///// ==============================
            ///// #04. 그래픽 출력
            ///// (1) 선긋기
            MoveToEx(hdc, 150, 150, NULL);
            LineTo(hdc, 450, 450);
            LineTo(hdc, 600, 450);
            ///// ------------------------------
            ///// (2) 사각형
            Rectangle(hdc, 200, 100, 300, 200);
            ///// ------------------------------
            ///// (3) 원
            Rectangle(hdc, 500, 100, 600, 200);
            Ellipse(hdc, 500, 100, 600, 200);               ///// (((사각형을 그리고 원을 그려야 둘 다 보인다. 원을 먼저 그리면 사각형만 보인다.)))
            ///// ==============================
            ///// #06. 글자 출력 (WM_CHAR 에서 입력받은 글자를 출력한다.)
            SetTextAlign(hdc, TA_LEFT);                     ///// 왼쪽 정렬
            TextOut(hdc, 100, 50, m_str, lstrlen(m_str));
            ///// ==============================
            ///// #07. 키보드 액션 (WM_KEYDOWN 에서 위치값을 받아와서 출력한다.)
            TextOut(hdc, nX, nY, L"☆", lstrlen(L"☆"));    ///// (((lstrlen(L"☆") 대신 1을 넣어도 된다.)))
            ///// ==============================
            ///// #10. 윈도우 타이머 (WM_TIMER 에서 시간을 받아와서 출력한다.)
            TextOut(hdc, 100, 150, str_time, lstrlen(str_time));
            ///// ==============================
            ///// #11. GDI 사용 (색 채우기, 선 색 변경)
            MyBrush  = (HBRUSH)GetStockObject(GRAY_BRUSH);  ///// StockObject는 삭제 안해줘도 괜찮다. 하지만 가급적 삭제하는 것이 좋다.
            OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);  ///// 이전에 사용하던 브러쉬를 리턴해준다. 저장해놓아야 한다.

            Rectangle(hdc, 100, 300, 400, 400);
            Ellipse(hdc, 120, 400, 220, 500);

            ///// 색 변경 복구하기!!!
            SelectObject(hdc, OldBrush);

            ///// 복구 확인하기 (원래 흰색)
            Ellipse(hdc, 120, 500, 220, 600);
            
            DeleteObject(MyBrush);                          ///// 생성 후 다 사용했다면 필히 삭제해줘야 한다.
            DeleteObject(OldBrush);                         ///// 생성 후 다 사용했다면 필히 삭제해줘야 한다.
            ///// ==============================
            ///// #12. PEN 사용 (HPEN CreatePen([in] int iStyle, [in] int cWidth, [in] COLORREF color);)
            MyPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0)); ///// 녹색
            OldPen = (HPEN)SelectObject(hdc, MyPen);
            
            Rectangle(hdc, 100, 600, 400, 700);

            SelectObject(hdc, OldPen);
            DeleteObject(MyPen);
            DeleteObject(OldPen);
            ///// ==============================
            ///// #13. 패턴 출력 (PEN, BRUSH)
            for (int i = 0; i < 6; i++)                     ///// PEN
            {
                MyPen  = CreatePen(i, 1, RGB(255, 0, 0));
                OldPen = (HPEN)SelectObject(hdc, MyPen);

                testRT.left   = 800 + ((i % 3) * (nWidth + 10));
                testRT.top    = 100 + ((i / 3) * (nHeight + 10));
                testRT.right  = testRT.left + nWidth;
                testRT.bottom = testRT.top + nHeight;

                Rectangle(hdc, testRT.left, testRT.top, testRT.right, testRT.bottom);

                SelectObject(hdc, OldPen);
                DeleteObject(MyPen);
                DeleteObject(OldPen);
            }

            for (int i = 0; i < 6; i++)                     ///// BRUSH
            {
                MyBrush = CreateHatchBrush(i, RGB(255, 0, 0));
                OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

                testRT.left   = 800 + ((i % 3) * (nWidth + 10));
                testRT.top    = 400 + ((i / 3) * (nHeight + 10));
                testRT.right  = testRT.left + nWidth;
                testRT.bottom = testRT.top + nHeight;

                Rectangle(hdc, testRT.left, testRT.top, testRT.right, testRT.bottom);

                SelectObject(hdc, OldBrush);
                DeleteObject(MyBrush);
                DeleteObject(OldBrush);
            }
            ///// ==============================
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        ///// ==============================
        ///// #10. 윈도우 타이머 (제거)
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        KillTimer(hWnd, 3);
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
