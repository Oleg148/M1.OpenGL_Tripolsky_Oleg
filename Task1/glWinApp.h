#pragma once

#include "resource.h"

#define MAX_LOADSTRING 100

// Forward declarations of functions included in this code module:
ATOM                RegisterWndClass(HINSTANCE );
BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutProc(HWND, UINT, WPARAM, LPARAM);

int					LoadWindowDefaultFont();
void				Render(RECT& );

// Global Variables:
extern HINSTANCE hInst; 
extern int idFont;
