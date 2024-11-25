// glWinApp.cpp : Defines the entry point for the application.
#include "pch.h"
#include "glWinApp.h"
#include <string>
#include <cmath>

extern LPCSTR s1, s2, s3;
extern TButton btn1, btn2, btn3, btn4, btn5, btn6, btnExit;
extern float x_max, x_min;
extern int point;

const float PI = 3.141592653589793238;

float W = 784;
float W1 = 784;
float H = 541;

float* arrX;
float* arrY;
char* points_text;
char* x_max_text;
char* x_min_text;
float arr_background[8] = { -1,1, 1,1, 1,-1, -1,-1 };
float arr_background1[8] = { -0.999f,0.999f, 0.999f,0.999f, 0.999f,-0.999f, -0.999f,-0.999f };
float arr_background2[8] = { -0.9f,0.7f, 0.46f,0.7f, 0.46f,-0.86f, -0.9f,-0.86f };

char text1[5] = "Xmax";
char text2[5] = "Xmin";
char text3[7] = "Points";
char text4[14] = "Cart Y = f(x)";
float line1[4] = { -1,0.9f, 1,0.9f };
float step;

void ShowCircle(float r, float a = 0, float b = 0, GLenum mode = GL_LINE_LOOP, float scale_x = 1, float scale_y = 1) {
    float x, y;
    float cnt = 300;
    float M_PI = 3.1415926535;
    float k = M_PI * 2 / cnt;

    glBegin(mode);
    //glVertex2d(0, 0);
    for (int i = -1; i < cnt; i++) {
        x = sin(k * i) * r * scale_x;
        y = cos(k * i) * r * scale_y;
        glVertex2d(x + a, y + b);
    }
    glEnd();
}

char* FloatToChar(float num) {
    std::string str;

    str = std::to_string(num);

    const int len = str.length();

    char arr[100];

    for (int i = 0; i <= len; i++) {
        arr[i] = str[i];
    }
    return arr;
}

float* —reateArrayX(float x_max, float x_min, int points) {
    float* arr1 = new float[points];
    float h = (x_max - x_min) / points;

    for (int i = 0; i < points; i++) {
        arr1[i] = x_min + (h * i);
    }
    return arr1;
}

float* —reateArrayY(float x_max, float x_min, int points) {
    float* arr2 = new float[points];
    float h = (x_max - x_min) / points;
    float x;

    for (int i = 0; i < points; i++) {
        x = x_min + (h * i);
        arr2[i] = cos((PI * x) + (PI / 4)) / pow(sin((7 * PI * x) / 5) + 1.01f, 0.5f);
    }
    return arr2;
}

void ArrayX(float*& arr, float x_max, float x_min, int points) {
    float* new_arr = —reateArrayX(x_max, x_min, points);
    delete[] arr;
    arr = new_arr;
}

void ArrayY(float*& arr, float x_max, float x_min, int points) {
    float* new_arr = —reateArrayY(x_max, x_min, points);
    delete[] arr;
    arr = new_arr;
}

float MaxFloat(float* pmas, int size) {
    float max = pmas[0];
    for (int i = 1; i < size; i++) {
        if (max < pmas[i]) {
            max = pmas[i];
        }
    }
    return max;
}

float MinFloat(float* pmas, int size) {
    float min = pmas[0];
    for (int i = 1; i < size; i++) {
        if (min > pmas[i]) {
            min = pmas[i];
        }
    }
    return min;
}

void TButton_Show(TButton btn) {
    glEnableClientState(GL_VERTEX_ARRAY);
    if (strcmp(btn.name, "Exit") == 0) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2d(btn.vert[0], btn.vert[1]);
        glVertex2d(btn.vert[2], btn.vert[3]);
        glColor3f(0.65f, 0.65f, 0.65f);
        glVertex2d(btn.vert[4], btn.vert[5]);
        glVertex2d(btn.vert[6], btn.vert[7]);
        glEnd();

        glColor3f(0.55f, 0.55f, 0.55f);
        glVertexPointer(2, GL_FLOAT, 0, btn.vert);
        glDrawArrays(GL_LINE_LOOP, 0, 4);

        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2d(btn.vert[0] + 13, btn.vert[1] + 8);
        glVertex2d(btn.vert[4] - 13, btn.vert[5] - 8);

        glVertex2d(btn.vert[2] - 13, btn.vert[3] + 8);
        glVertex2d(btn.vert[6] + 13, btn.vert[7] - 8);
        glEnd();
        glLineWidth(1);
    }
    else
    {
        glColor3f(0.75f, 0.75f, 0.75f);
        glVertexPointer(2, GL_FLOAT, 0, btn.vert);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        if (strcmp(btn.name, "Xmax+") == 0 || strcmp(btn.name, "Xmin+") == 0 || strcmp(btn.name, "point+") == 0) {
            glColor3d(0.3f, 0.3f, 0.3f);
            float x2 = btn.vert[2] - ((btn.vert[2] - btn.vert[0]) / 2);
            float arr[6] = { btn.vert[6] + 3,btn.vert[7] - 3, x2,btn.vert[3] + 3, btn.vert[4] - 3,btn.vert[5] - 3 };
            glVertexPointer(2, GL_FLOAT, 0, arr);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        if (strcmp(btn.name, "Xmax-") == 0 || strcmp(btn.name, "Xmin-") == 0 || strcmp(btn.name, "point-") == 0) {
            glColor3d(0.3f, 0.3f, 0.3f);
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

int LoadWindowDefaultFont()
{
    int id = glGenLists(256);
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, id);
    return id;
}

void OutText(char* arr, double x, double y, double z = 0)
{
    LPCSTR str = arr;
    glRasterPos3d(x, y, z);
    glListBase(idFont);
    glCallLists(strlen(str), GL_UNSIGNED_BYTE, &str[0]);
}

void Background(float* arr, GLenum mode, int point) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, arr);
    glDrawArrays(mode, 0, point);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void function(float scale_x) {
    float mas[4];
    for (int i = 0; i < point - 1; i++) {
        mas[0] = arrX[i];
        mas[1] = arrY[i];
        mas[2] = arrX[i + 1];
        mas[3] = arrY[i + 1];
        glColor3f(0, 0, 0);
        Background(mas, GL_LINES, 2);
        if (i != 0) {
            if (fabs(arrY[i]) < fabs(arrY[i + 1]) && fabs(arrY[i]) < fabs(arrY[i - 1])) {
                glColor3f(1, 1, 0);
                ShowCircle(0.1f, arrX[i], 0, GL_TRIANGLE_FAN, scale_x);
                glLineWidth(2);
                glColor3f(0, 0, 0);
                ShowCircle(0.12f, arrX[i], 0, GL_LINE_LOOP, scale_x);
                glLineWidth(1);
            }
        }
    }
}
void grid(float x_min, float x_max, float y_min, float y_max, float step_x = 0.1, float step_y = 0.1) {
    float mas[4];
    for (float i = 0; i < x_max + step_x; i = i + step_x) {
        mas[0] = i;
        mas[1] = y_min;
        mas[2] = i;
        mas[3] = y_max;
        Background(mas, GL_LINES, 2);
    }
    for (float i = 0; i > x_min - step_x; i = i - step_x) {
        mas[0] = i;
        mas[1] = y_min;
        mas[2] = i;
        mas[3] = y_max;
        Background(mas, GL_LINES, 2);
    }
    for (float i = 0; i < y_max + step_y; i = i + step_y) {
        mas[0] = x_max;
        mas[1] = i;
        mas[2] = x_min;
        mas[3] = i;
        Background(mas, GL_LINES, 2);
    }
    for (float i = 0; i > y_min - step_y; i = i - step_y) {
        mas[0] = x_max;
        mas[1] = i;
        mas[2] = x_min;
        mas[3] = i;
        Background(mas, GL_LINES, 2);
    }
}

void CoordinateAxis(float x_min, float x_max, float y_min, float y_max, float step_x = 0.1, float step_y = 0.1) {
    float axisX[4] = { x_min,0, x_max,0 };
    float axisY[4] = { 0,y_min, 0,y_max };
    float arrowX[6] = { x_max - step_x / 3, -step_y / 7, x_max,0, x_max - step_x / 3, step_y / 7 };
    float arrowY[6] = { -step_x / 7, y_max - step_y / 3, 0,y_max, step_x / 7, y_max - step_y / 3 };
    float mas[4];
    char* num_arr;

    glLineWidth(2);
    Background(axisX, GL_LINES, 2);
    Background(axisY, GL_LINES, 2);
    Background(arrowX, GL_LINE_STRIP, 3);
    Background(arrowY, GL_LINE_STRIP, 3);

    for (float i = 0; i < x_max; i = i + step_x) {
        mas[0] = i;
        mas[1] = step_y / 7;
        mas[2] = i;
        mas[3] = -step_y / 7;
        Background(mas, GL_LINES, 2);
        if (i != 0) {
            num_arr = FloatToChar(i);
            char num_str[4] = { num_arr[0], num_arr[1], num_arr[2] };
            OutText(num_str, i, -step_y / 2);
        }
    }
    for (float i = 0; i > x_min; i = i - step_x) {
        mas[0] = i;
        mas[1] = step_y / 7;
        mas[2] = i;
        mas[3] = -step_y / 7;
        Background(mas, GL_LINES, 2);
        if (i != 0) {
            num_arr = FloatToChar(i);
            char num_str[5] = { num_arr[0], num_arr[1], num_arr[2], num_arr[3] };
            OutText(num_str, i, -step_y / 2);
        }
        else
        {
            num_arr = FloatToChar(i);
            char num_str[2] = { num_arr[0] };
            OutText(num_str, step_x / 4, -step_y / 2);
        }
    }
    for (float i = 0; i < y_max; i = i + step_y) {
        mas[0] = -step_x / 7;
        mas[1] = i;
        mas[2] = step_x / 7;
        mas[3] = i;
        Background(mas, GL_LINES, 2);
        if (i != 0) {
            num_arr = FloatToChar(i);
            char num_str[2] = { num_arr[0] };
            OutText(num_str, step_x / 2, i);
        }
    }
    for (float i = 0; i > y_min; i = i - step_y) {
        mas[0] = step_x / 7;
        mas[1] = i;
        mas[2] = -step_x / 7;
        mas[3] = i;
        Background(mas, GL_LINES, 2);
        if (i != 0) {
            num_arr = FloatToChar(i);
            char num_str[3] = { num_arr[0], num_arr[1] };
            OutText(num_str, step_x / 2, i);
        }
    }

    glLineWidth(1);
}

void ShowGraph(float* x, float* y, int size, float x_min = -1, float x_max = 1, float step_x = 0.1, float step_y = 0.1) {
    glPushMatrix();
    glLoadIdentity();

    float y_max = MaxFloat(arrY, point);
    float y_min = MinFloat(arrY, point);

    gluOrtho2D(x_min, x_max, y_min, y_max);
    glColor3f(0.85f, 0.85f, 0.85f);
    grid(x_min, x_max, y_min, y_max, step_x, step_y);
    glColor3f(0, 0, 0);
    CoordinateAxis(x_min, x_max, y_min, y_max, step_x, step_y);
    function(step_x);
    glPopMatrix();
}

void Render(RECT& clientRect)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    int Height = clientRect.bottom - clientRect.top;
    int Width = clientRect.right - clientRect.left;
    W = Width * 0.95;
    W1 = Width;
    H = Height / 21.64;

    btn1 = { "Xmax+", {W - 20,75, W,75, W,90, W - 20,90} };
    btn2 = { "Xmax-", {W - 20,95, W,95, W,110, W - 20,110} };
    btn3 = { "Xmin+", {W - 20,115, W,115, W,130, W - 20,130} };
    btn4 = { "Xmin-", {W - 20,135, W,135, W,150, W - 20,150} };
    btn5 = { "point+", {W - 20,170, W,170, W,185, W - 20,185} };
    btn6 = { "point-", {W - 20,190, W,190, W,205, W - 20,205} };
    btnExit = { "Exit", {W1 * (float)0.9489 ,0, W1,0, W1,H, W1 * (float)0.9489,H} };

    // „Î‡‚ÌÓÂ ÓÍÌÓ
    glViewport(0, 0, Width, Height);

    glColor3f(0, 0, 0);
    x_max_text = FloatToChar(x_max);
    char a[4] = { x_max_text[0], x_max_text[1], x_max_text[2] };
    OutText(a, 0.75f, 0.63f);

    x_min_text = FloatToChar(x_min);
    char a1[5] = { x_min_text[0], x_min_text[1], x_min_text[2], x_min_text[3] };
    OutText(a1, 0.74f, 0.5f);

    points_text = FloatToChar(point);
    char a2[4] = { points_text[0], points_text[1], points_text[2] };
    OutText(a2, 0.75f, 0.3f);

    OutText(text1, 0.6f, 0.63f);
    OutText(text2, 0.6f, 0.5f);
    OutText(text3, 0.6f, 0.3f);
    OutText(text4, -0.9f, 0.92f);

    Background(line1, GL_LINES, 2);
    glColor3f(1, 1, 1);
    Background(arr_background2, GL_TRIANGLE_FAN, 4);
    glColor3f(0.75f, 0.75f, 0.75f);
    Background(arr_background2, GL_LINE_LOOP, 4);

    ShowMenu(Width, Height, btn1);
    ShowMenu(Width, Height, btn2);
    ShowMenu(Width, Height, btn3);
    ShowMenu(Width, Height, btn4);
    ShowMenu(Width, Height, btn5);
    ShowMenu(Width, Height, btn6);
    ShowMenu(Width, Height, btnExit);


    // „‡ÙËÍ
    glViewport(Width / 15.68, Height / 10.82, Width * 0.65, Height * 0.74);

    glColor3f(1, 1, 1);
    Background(arr_background, GL_TRIANGLE_FAN, 4);
    glColor3f(0.85f, 0.85f, 0.85f);
    Background(arr_background1, GL_LINE_LOOP, 4);

    ArrayX(arrX, x_min, x_max, point);
    ArrayY(arrY, x_min, x_max, point);

    step = x_max - x_min;
    if (step <= 2.5f) {
        ShowGraph(arrX, arrY, point, x_min, x_max, 0.1f, 1.0f);
    }
    else if (2 < step && step <= 5)
    {
        ShowGraph(arrX, arrY, point, x_min, x_max, 0.2f, 1.0f);
    }
    else
    {
        ShowGraph(arrX, arrY, point, x_min, x_max, 0.3f, 1.0f);
    }

    //glColor3d(1, 1, 1);
    //OutText(s1, 20, 30);
    //OutText(s2, 20, 50);
    //OutText(s3, 20, 70);

    //// Rectangle example
    //glColor3d(1, 0, 0);
    //glLineWidth(3);
    //glBegin(GL_LINE_LOOP);
    //glVertex2d(4, 100);
    //glVertex2d(Width - 5.0, 100);
    //glColor3d(1, 1, 0);
    //glVertex2d(Width - 5.0, Height - 5.0);
    //glVertex2d(4, Height - 5.0);
    //glEnd();
}
