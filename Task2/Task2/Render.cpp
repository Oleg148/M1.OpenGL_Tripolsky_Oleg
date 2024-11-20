// glWinApp.cpp : Defines the entry point for the application.
#include "pch.h"
#include "glWinApp.h"
#include "math.h"
#include <string>

extern LPCSTR s1, s2, s3;
extern TButton btn1, btn2, btn3, btn4, btn_Radio[3], btnExit;
extern int W, H, mod;

int LoadWindowDefaultFont()
{
    int id = glGenLists(256);
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, id);
    return id;
}

void OutText(LPCSTR str, double x, double y, double z = 0)
{
    glRasterPos3d(x, y, z);
    glListBase(idFont);
    glCallLists(strlen(str), GL_UNSIGNED_BYTE, &str[0]);
}

void sample(GLenum type, int points, float arr[]) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, arr);
    glDrawArrays(type, 0, points);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void figureColor() {
    float h = pow(300, 0.5);

    float square1[8] = { -20,10, -20,-10, 0,10, 0,-10, };
    glColor3d(0.5, 0.5, 0.5);
    sample(GL_QUAD_STRIP, 4, square1);

    /*float square2[8] = { 0,10, 0,-10, 20,10, 20,-10, };
    glColor3d(0.5, 0.5, 0.5);
    sample(GL_QUAD_STRIP, 4, square2);*/

    float triangle1[6] = { -20,10, 0,10, -10,10 + h };
    glColor3d(1, 0, 0);
    sample(GL_TRIANGLES, 3, triangle1);

    float triangle2[6] = { 20,10, 0,10, 10,10 + h };
    glColor3d(1, 0, 0);
    sample(GL_TRIANGLES, 3, triangle2);

    float triangle3[6] = { 10,10 + h, 0,10, -10,10 + h };
    glColor3d(0, 0, 1);
    sample(GL_TRIANGLES, 3, triangle3);

    float triangle4[6] = { 10,10 + h, 20,10, 30,10 + h };
    glColor3d(0, 0, 1);
    sample(GL_TRIANGLES, 3, triangle4);

    float triangle5[6] = { -20,-10, -10,-10 - h, 0,-10 };
    glColor3d(1, 1, 0);
    sample(GL_TRIANGLES, 3, triangle5);

    float triangle6[6] = { 0,-10, 10,-10 - h, 20,-10 };
    glColor3d(1, 1, 0);
    sample(GL_TRIANGLES, 3, triangle6);

    float triangle7[6] = { 0,-10, -10,-10 - h, 10,-10 - h };
    glColor3d(0, 1, 0);
    sample(GL_TRIANGLES, 3, triangle7);

    float triangle8[6] = { 20,-10, 10,-10 - h, 30,-10 - h };
    glColor3d(0, 1, 0);
    sample(GL_TRIANGLES, 3, triangle8);
}

void figure(GLenum mode) {
    float h = pow(300, 0.5);

    float square1[8] = { -20,10, 0,10, 0,-10, -20,-10, };
    glColor3d(0, 0, 0);
    sample(mode, 4, square1);

    float square2[8] = { 0,10, 20,10, 20,-10, 0,-10, };
    sample(mode, 4, square2);

    /*float square2[8] = { 0,10, 0,-10, 20,10, 20,-10, };
    glColor3d(0.5, 0.5, 0.5);
    sample(GL_QUAD_STRIP, 4, square2);*/

    float triangle1[6] = { -20,10, 0,10, -10,10 + h };
    sample(mode, 3, triangle1);

    float triangle2[6] = { 20,10, 0,10, 10,10 + h };
    sample(mode, 3, triangle2);

    float triangle3[6] = { 10,10 + h, 0,10, -10,10 + h };
    sample(mode, 3, triangle3);

    float triangle4[6] = { 10,10 + h, 20,10, 30,10 + h };
    sample(mode, 3, triangle4);

    float triangle5[6] = { -20,-10, -10,-10 - h, 0,-10 };
    sample(mode, 3, triangle5);

    float triangle6[6] = { 0,-10, 10,-10 - h, 20,-10 };
    sample(mode, 3, triangle6);

    float triangle7[6] = { 0,-10, -10,-10 - h, 10,-10 - h };
    sample(mode, 3, triangle7);

    float triangle8[6] = { 20,-10, 10,-10 - h, 30,-10 - h };
    sample(mode, 3, triangle8);
}

void funMod1(int W) {
    glTranslatef(-40, 0, 0);

    glTranslatef(-20 * (W - 1), 0, 0);

    for (int i = 0; i < W; i++) {
        figureColor();
        figure(GL_LINE_LOOP);
        glTranslatef(40, 0, 0);
    }
}
void funMod2(int W) {
    glTranslatef(-40, 0, 0);

    glTranslatef(-20 * (W - 1), 0, 0);

    for (int i = 0; i < W; i++) {
        figure(GL_LINE_LOOP);
        glTranslatef(40, 0, 0);
    }
}

void funMod3(int W) {
    glTranslatef(-40, 0, 0);

    glTranslatef(-20 * (W - 1), 0, 0);

    for (int i = 0; i < W; i++) {
        glPointSize(5);
        figure(GL_POINTS);
        glTranslatef(40, 0, 0);
    }
}

void fun1(int W, int H) {
    float h = pow(300, 0.5);

    glScalef(1.2, 1.2, 1.2);

    glScalef(2 / (float)W, 2 / (float)H, 0);
    glTranslatef(20, -20 * (H - 1), 0);

    for (int i = 0; i < H; i++) {
        funMod1(W);
        glTranslatef(-20 * (W - 1), 20 + h * 2, 0);
    }
}

void fun2(int W, int H) {
    float h = pow(300, 0.5);

    glScalef(1.2, 1.2, 1.2);

    glScalef(2 / (float)W, 2 / (float)H, 0);
    glTranslatef(20, -20 * (H - 1), 0);

    for (int i = 0; i < H; i++) {
        funMod2(W);
        glTranslatef(-20 * (W - 1), 20 + h * 2, 0);
    }
}

void fun3(int W, int H) {
    float h = pow(300, 0.5);

    glScalef(1.2, 1.2, 1.2);

    glScalef(2 / (float)W, 2 / (float)H, 0);
    glTranslatef(20, -20 * (H - 1), 0);

    for (int i = 0; i < H; i++) {
        funMod3(W);
        glTranslatef(-20 * (W - 1), 20 + h * 2, 0);
    }
}

char* intToChar(int num) {
    std::string str;

    str = std::to_string(num);

    const int len = str.length();

    char arr[100];

    for (int i = 0; i <= len; i++) {
        arr[i] = str[i];
    }
    return arr;
}

void ShowCircle(float r, float a = 0, float b = 0, GLenum mode = GL_LINE_LOOP) {
    float x, y;
    float cnt = 100;
    float M_PI = 3.1415926535;
    float k = M_PI * 2 / cnt;

    glBegin(mode);
    //glVertex2d(0, 0);
    for (int i = -1; i < cnt; i++) {
        x = sin(k * i) * r;
        y = cos(k * i) * r;
        glVertex2d(x + a, y + b);
    }
    glEnd();
}

void TButton_Show(TButton btn) {
    glEnableClientState(GL_VERTEX_ARRAY);

    if (btn.radio == 1) {
        glColor3d(0, 0, 0);
        float r = (btn.vert[2] - btn.vert[0]) / 2;
        float a = btn.vert[2] - r;
        float b = btn.vert[5] - ((btn.vert[5] - btn.vert[1]) / 2);
        ShowCircle(r, a, b);

        ShowCircle(r - 5, a, b);

        if (btn.color == 1) {
            glColor3d(0.5, 0.5, 1);
        }
        else
        {
            glColor3d(1, 1, 1);
        }
        ShowCircle(r - 5, a, b, GL_TRIANGLE_FAN);
    }
    else
    {
        glColor3d(0.85, 0.85, 0.85);
        glVertexPointer(2, GL_FLOAT, 0, btn.vert);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        if (strcmp(btn.name, "Exit") == 0) {
            glColor3d(0, 0, 0);
            glLineWidth(2);
            float line1[4] = { btn.vert[0],btn.vert[1], btn.vert[4], btn.vert[5] };
            glVertexPointer(2, GL_FLOAT, 0, line1);
            glDrawArrays(GL_LINES, 0, 2);
            float line2[4] = { btn.vert[2],btn.vert[3], btn.vert[6], btn.vert[7] };
            glVertexPointer(2, GL_FLOAT, 0, line2);
            glDrawArrays(GL_LINES, 0, 2);
        }

        if (strcmp(btn.name, "W = W + 1") == 0 || strcmp(btn.name, "H = H + 1") == 0) {
            glColor3d(0, 0, 0);
            float x2 = btn.vert[2] - ((btn.vert[2] - btn.vert[0]) / 2);
            float arr[6] = { btn.vert[6] + 3,btn.vert[7] - 3, x2,btn.vert[3] + 3, btn.vert[4] - 3,btn.vert[5] - 3 };
            glVertexPointer(2, GL_FLOAT, 0, arr);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        if (strcmp(btn.name, "W = W - 1") == 0 || strcmp(btn.name, "H = H - 1") == 0) {
            glColor3d(0, 0, 0);
            float x2 = btn.vert[2] - ((btn.vert[2] - btn.vert[0]) / 2);
            float arr[6] = { btn.vert[0] + 3,btn.vert[1] + 3, x2,btn.vert[5] - 3, btn.vert[2] - 3,btn.vert[3] + 3 };
            glVertexPointer(2, GL_FLOAT, 0, arr);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void ShowMenu(int Width, int Height, TButton btn) {
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, Width, Height, 0, -1, 1);
    TButton_Show(btn);
    glPopMatrix();
}

BOOL PointInButton(int x, int y, TButton btn) {
    return (x > btn.vert[0]) && (x < btn.vert[4]) &&
        (y > btn.vert[1]) && (y < btn.vert[5]);
}

void Render(RECT& clientRect)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    int Height = clientRect.bottom - clientRect.top;
    int Width = clientRect.right - clientRect.left;

    glViewport(0, 0, Width, Height);

    LPCSTR text1 = (char*)"OpenGL Application";
    LPCSTR text2 = (char*)"Tile count:";
    LPCSTR text3 = (char*)"horizontal";
    LPCSTR text4 = (char*)"vertical";
    LPCSTR text5 = (char*)"Fill mode";
    LPCSTR text6 = (char*)"line mode";
    LPCSTR text7 = (char*)"Point mode";

    glViewport(0, 0, Width, Height);

    glColor3d(0, 0, 0);
    OutText(text1, -0.95, 0.93);
    OutText(text2, 0.69, 0.77);
    OutText(text3, 0.55, 0.65);
    OutText(text4, 0.55, 0.50);
    OutText(text5, 0.69, -0.5);
    OutText(text6, 0.69, -0.6);
    OutText(text7, 0.69, -0.7);

    char* a = intToChar(W);
    LPCSTR text8 = (char*)a;
    OutText(text8, 0.75, 0.65);

    char* arr = intToChar(H);
    LPCSTR text9 = (char*)arr;
    OutText(text9, 0.75, 0.50);

    ShowMenu(Width, Height, btn1);
    ShowMenu(Width, Height, btn2);
    ShowMenu(Width, Height, btn3);
    ShowMenu(Width, Height, btn4);
    ShowMenu(Width, Height, btnExit);

    for (int i = 0; i < 3; i++) {
        ShowMenu(Width, Height, btn_Radio[i]);
    }

    float line1[4] = { -1,0.9, 1,0.9 };

    glColor3d(0, 0, 0);
    glLineWidth(2);
    sample(GL_LINES, 2, line1);


    glViewport(10, 10, Width * 0.75, Height - 50);
    gluOrtho2D(-100, 100, -100, 100);

    float square1[8] = { -100,100, -100,-100, 100,100, 100,-100 };
    float square2[8] = { -100,100, 100,100, 100,-100, -100,-100 };

    glColor3d(0.85, 0.85, 0.85);
    sample(GL_TRIANGLE_STRIP, 4, square1);
    glColor3d(0.65, 0.65, 0.65);
    glLineWidth(2);
    sample(GL_LINE_LOOP, 4, square2);

    if (mod == 1) {
        fun1(W, H);
    }
    else if (mod == 2) {
        fun2(W, H);
    }
    else if (mod == 3) {
        fun3(W, H);
    }
}
