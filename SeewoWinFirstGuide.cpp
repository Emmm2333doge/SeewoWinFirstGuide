// SeewoWinFirstGuide.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "SeewoWinFirstGuide.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
const WCHAR* szWndTitC = L"希沃 Windows 系统首次使用向导";

const int WW = 400, WH = 560;//窗口的大小

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SEEWOWINFIRSTGUIDE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEEWOWINFIRSTGUIDE));

    MSG msg;

    // 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SEEWOWINFIRSTGUIDE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle,
       WS_OVERLAPPEDWINDOW^(WS_THICKFRAME|WS_MAXIMIZEBOX),
       (GetSystemMetrics(SM_CXSCREEN) - WW) / 2,
       (GetSystemMetrics(SM_CYSCREEN) - WH) / 2,
       WW,
       WH,
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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtnOK,hStWelcome,hStVer;
    HPEN hPenCtl=NULL;
    WCHAR szVer[400];
    switch (message)
    {
    case WM_CREATE: {
        SetWindowText(hWnd,szWndTitC);

        hBtnOK = CreateWindow(L"button", L"完成", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            (WW - 200) / 2, WH - 100, 200, 30, hWnd, (HMENU)IDM_EXIT, hInst, NULL);
        hStWelcome = CreateWindow(L"static", L"欢迎使用 Seewo 定制 Windows 系统！\n作者：bilibili@不会起名的emmm",
            WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 10, WW, 60, hWnd, (HMENU)1, hInst, NULL);
        hStVer = CreateWindow(L"static", L"hStVer", WS_VISIBLE | WS_CHILD | SS_CENTER,
            0, 64, WW, 60, hWnd, (HMENU)2, hInst, NULL);

        //得到系统版本并存入szVer
        static DWORD ver1, ver2, ver3, verdisp;
            GetNtVersionNumbers(&ver1, &ver2, &ver3);
            if (ver1 == 10) {
                if (ver3 < 22000) {
                    verdisp = 10;
                }
                else {
                    verdisp = 11;
                }
            }
            else if (ver1 == 6) {
                if (ver2 == 1) {
                    verdisp = 8;
                }
                if (ver2 == 1) {
                    verdisp = 7;
                }
            }
            else {
                verdisp = -1;
            }
            if (verdisp != -1) {
                wsprintf(szVer, L"当前 Windows 系统版本：%d.%d.%d\n(Windows %d)", ver1, ver2, ver3, verdisp);
            }
            else {
                wsprintf(szVer, L"当前 Windows 系统版本：%d.%d.%d\n(早期或未知版本的 Windows)", ver1, ver2, ver3);
            }
            //处理并显示系统版本
            SetWindowText(hStVer, szVer);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLORBTN:
    case WM_CTLCOLOREDIT: {
        HDC hdcCtl = (HDC)wParam;
        HFONT hf = FastFont(L"微软雅黑", 18, 0, 0);
        SelectObject(hdcCtl, hf);
        return (LRESULT)hPenCtl;
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
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
