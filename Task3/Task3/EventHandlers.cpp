// LPA 2018.09.18, 2022.10.12
// glWinApp.cpp : Defines the entry point for the application.
#include "pch.h"
#include "glWinApp.h"

HGLRC hglrc;
LPCSTR s1, s2, s3;

int point = 400;
float x_max = 1.0f;
float x_min = -1.0f;

TButton btn1;
TButton btn2;
TButton btn3;
TButton btn4;
TButton btn5;
TButton btn6;
TButton btnExit;

//-- Main window event handlers -------------------------------------------------

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    PIXELFORMATDESCRIPTOR pfd;

    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER);
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.cStencilBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;

    HDC hDC = GetDC(hwnd);

    int n = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, n, &pfd);
    hglrc = wglCreateContext(hDC);

    wglMakeCurrent(hDC, hglrc);
    idFont = LoadWindowDefaultFont();
    glClearColor(0.9f, 0.9f, 0.9f, 0);

    s1 = (char*)glGetString(GL_VENDOR);
    s2 = (char*)glGetString(GL_RENDERER);
    s3 = (char*)glGetString(GL_VERSION);

    wglMakeCurrent(hDC, 0);

    ReleaseDC(hwnd, hDC);

    return TRUE;
}

void OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
    wglMakeCurrent(0, 0);
    wglDeleteContext(hglrc);
}

void OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    RECT clientRect;
    HDC dc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &clientRect);

    wglMakeCurrent(dc, hglrc);

    Render(clientRect);
    SwapBuffers(dc);

    wglMakeCurrent(dc, 0);

    EndPaint(hwnd, &ps);
}

BOOL OnMenu(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    BOOL result = FALSE;
    int wmId = LOWORD(id);
    switch (wmId) // Parse the menu selections
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, AboutProc);
        result = TRUE;
        break;
    case IDM_EXIT:
        DestroyWindow(hDlg);
        result = TRUE;
        break;
    default:
        result = DefWindowProc(hDlg, WM_COMMAND, id, codeNotify);
    }
    return result;
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
    if (x_max - x_min > 0.3f) {
        if (PointInButton(x, y, btn2)) {
            if (x_max > 0) {
                x_max = x_max - 0.1f;
            }
        }
        if (PointInButton(x, y, btn3)) {
            if (x_min < 0) {
                x_min = x_min + 0.1f;
            }
        }
    }
    if (PointInButton(x, y, btn1)) {
        x_max = x_max + 0.1f;
    }
    if (PointInButton(x, y, btn4)) {
        x_min = x_min - 0.1f;
    }
    if (PointInButton(x, y, btn5)) {
        point = point + 10;
    }
    if (PointInButton(x, y, btn6)) {
        if (point > 100) {
            point = point - 10;
        }
    }
    if (PointInButton(x, y, btnExit)) {
        PostQuitMessage(0);
    }
    InvalidateRect(hwnd, 0, 1);
}

//   ���������� �� ������������� ����� windowsx.h � �������� ��� ��������� ���������
//
//   1. ��������, ����� ��������� Windows �������� �� �������, ��������� ���������.
//		������. �� �������, ��������� � ���������� ������� ����, �������� ��������� WM_SIZE.
//
//   2. ��������� ���� windowsx.h (� ������ �� ��������� � ����� framework.h) � ��������� ����� 
//      (Ctrl+F) ������, ������� ����������� ��������� ������� �WM_� �������� �� �On�.
//      ������. WM_SIZE ������ �� OnSize � ��������� ����� ���� ������. � ���������� ������ ������ 
//      ���� ������� ������������������ ������ � ���������� �������-����������� ��������� WM_SIZE:
//		/* void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy) */
//      � ���� ��������� �������� � ���� ���� EventHandlers.cpp
//
//   3. � �������� ��������� ��������� � ��������� ���� ������� (������ ������� Cls_ �������) � 
//      ��������� ������ ������������ ��������� ��������� WndProc(...) � ������������ ����������� 
//      ������� � ������� ������� HANDLE_MSG(...):
//		void OnSize(HWND hwnd, UINT state, int cx, int cy) 
//		{
//			...
//		}
//		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//		{
//			switch (message){
//				...
//				HANDLE_MSG(hWnd, WM_SIZE, OnSize); 
//				...
//			default: 
//				return DefWindowProc(hWnd, message, wParam, lParam);
//			}
//		}
//   
//   4. ���������� ��������� � ������� �����������, ������� ������� ����������� ���������.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
        //		HANDLE_MSG(hWnd, WM_SIZE,	 OnSize);  // ��. ���������� ����
        HANDLE_MSG(hWnd, WM_COMMAND, OnMenu);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

//-- About window event handlers ------------------------------------------------

INT_PTR OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    if (LOWORD(id) == IDOK || LOWORD(id) == IDCANCEL)
    {
        EndDialog(hDlg, LOWORD(id));
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

INT_PTR OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
    HWND hOwner;
    RECT rcOwner, rcDlg; //, rc;
    if ((hOwner = GetParent(hDlg)) == NULL)
        hOwner = GetDesktopWindow();

    GetWindowRect(hOwner, &rcOwner);
    GetWindowRect(hDlg, &rcDlg);

    SetWindowPos(hDlg, HWND_TOP,
        rcOwner.left + (((rcOwner.right - rcOwner.left) - (rcDlg.right - rcDlg.left)) / 2),
        rcOwner.top + (((rcOwner.bottom - rcOwner.top) - (rcDlg.bottom - rcDlg.top)) / 2),
        0, 0, SWP_NOSIZE);          // Ignores size arguments. 

    return (INT_PTR)TRUE;
}

// Message handler for about box.
INT_PTR CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, OnInitDialog);//&& TRUE;
        HANDLE_MSG(hDlg, WM_COMMAND, OnCommand);//&& TRUE;
    default:
        return (INT_PTR)FALSE;
    }
    return (INT_PTR)TRUE;
}

