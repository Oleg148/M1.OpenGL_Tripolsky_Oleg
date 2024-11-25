#pragma once

#include "resource.h"

#define MAX_LOADSTRING 100

// Forward declarations of functions included in this code module:
ATOM                RegisterWndClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutProc(HWND, UINT, WPARAM, LPARAM);

int					LoadWindowDefaultFont();
void				Render(RECT&);

// Global Variables:
extern HINSTANCE hInst;
extern int idFont;

float* ÑreateArrayX(float x_max, float x_min, int points);
float* ÑreateArrayY(float x_max, float x_min, int points);
float MaxFloat(float* pmas, int size);
float MinFloat(float* pmas, int size);

typedef struct {
    char name[20];
    float vert[8];
} TButton;

BOOL PointInButton(int x, int y, TButton btn);