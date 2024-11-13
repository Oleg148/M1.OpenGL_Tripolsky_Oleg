// LPA 2018.09.18, 2022.10.12
// glWinApp.cpp : Defines the entry point for the application.
#include "pch.h"
#include "glWinApp.h"

HGLRC hglrc;
LPCSTR s1, s2, s3;

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
            glClearColor(0.39f, 0.47f, 0.59f, 1.0f);

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

//   Инструкция по использованию файла windowsx.h и макросов для обработки сообщений
//
//   1. Выяснить, какое сообщение Windows отвечает за событие, требующее обработки.
//		Пример. За событие, связанное с изменением размера окна, отвечает сообщение WM_SIZE.
//
//   2. Открываем файл windowsx.h (в проект он подключен в файле framework.h) и выполняем поиск 
//      (Ctrl+F) строки, которая формируется следующим образом «WM_» заменяем на «On».
//      Пример. WM_SIZE меняем на OnSize и выполняем поиск этой строки. В результате поиска должна 
//      быть найдена закомментированная строка с прототипом функции-обработчика сообщения WM_SIZE:
//		/* void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy) */
//      и этот заголовок копируем в свой файл EventHandlers.cpp
//
//   3. В основной программе добавляем к заголовку тело функции (обычно префикс Cls_ удаляют) и 
//      выполняем связку подпрограммы обработки сообщений WndProc(...) и подпрограммы обработчика 
//      события с помощью макроса HANDLE_MSG(...):
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
//   4. Аналогично поступаем с другими сообщениями, которые требуют программной обработки.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        //		HANDLE_MSG(hWnd, WM_SIZE,	 OnSize);  // см. инструкцию выше
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

