// glWinApp.cpp : Defines the entry point for the application.
#include "pch.h"
#include "glWinApp.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <string>


extern LPCSTR s1, s2, s3;
extern TButton btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btnExit;
extern double x11, x21, y11, y21, a1, b1;

float arr_background[8] = { -10,10, 10,10, 10,-10, -10,-10 };
float arr_background1[8] = { -9.999f,9.999f, 9.999f,9.999f, 9.999f,-9.999f, -9.999f,-9.999f };
float arr_background2[8] = { -9.0f,7.0f, 4.6f,7.0f, 4.6f,-8.6f, -9.0f,-8.6f };
float line1[4] = { -10,9.0f, 10,9.0f };

char* x1_text;
char* x2_text;
char* y1_text;
char* y2_text;

char text1[4] = "X1:";
char text2[4] = "X2:";
char text3[4] = "Y1:";
char text4[4] = "Y2:";
char text5[14] = "Cart Y = f(x)";

struct Point {
    double x1;
    double y1;
    double x2;
    double y2;
};

void drawHyperbola(double a, double b) {
    glBegin(GL_LINE_STRIP); // Начинаем рисовать линию
    for (double t = -2.0; t <= 2.0; t += 0.01) {
        double x = a * cosh(t);
        double y = b * sinh(t);
        glVertex2d(x, y); // Добавляем вершину
    }
    glEnd();

    glBegin(GL_LINE_STRIP); // Рисуем вторую ветвь гиперболы
    for (double t = -2.0; t <= 2.0; t += 0.01) {
        double x = -a * cosh(t);
        double y = b * sinh(t);
        glVertex2d(x, y); // Добавляем вершину
    }
    glEnd();
}

void drawParabola() {
    glBegin(GL_LINE_STRIP);
    for (double x = -2.0; x <= 2.0; x += 0.01) {
        double y = x * x;
        glVertex2d(x, y);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (double x = -5.0; x <= 5.0; x += 0.01) {
        double y = x * x;
        glVertex2d(-x, y);
    }
    glEnd();
}

void drawLine(double x1, double y1, double x2, double y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void Background(float* arr, GLenum mode, int point) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, arr);
    glDrawArrays(mode, 0, point);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int LoadWindowDefaultFont()
{
    int id = glGenLists(256);
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, id);
    return id;
}

void intToCharArray(int number, char* buffer, size_t bufferSize) {
    snprintf(buffer, bufferSize, "%d", number);
}

void OutText(char* arr, double x, double y, double z = 0)
{
    LPCSTR str = arr;
    glRasterPos3d(x, y, z);
    glListBase(idFont);
    glCallLists(strlen(str), GL_UNSIGNED_BYTE, &str[0]);
}

std::vector<Point> findIntersection(double x1, double x2, double y1, double y2, double a, double b) {
    std::vector<Point> intersections;
    double k = 0;

    if (x2 - x1 != 0) {
        k = (y2 - y1) / (x2 - x1);
    }

    double c = y1 - k * x1;

    if (a * k - b != 0)
    {
        double l1 = (-c - std::sqrt(-a * a * k * k + c * c + b * b)) / (a * k - b);
        if (l1 < 0)
        {
            double t = log(-l1);
            x1 = a * cosh(t);
            y1 = b * sinh(t);
        }
        else
        {
            double t = log(l1);
            x1 = a * cosh(t);
            y1 = b * sinh(t);
        }
    }

    if (a * k + b != 0)
    {
        double l1 = (c + std::sqrt(-a * a * k * k + c * c + b * b)) / (a * k + b);
        if (l1 < 0)
        {
            double t = log(-l1);
            x2 = a * cosh(t);
            y2 = b * sinh(t);
        }
        else
        {
            double t = log(l1);
            x2 = a * cosh(t);
            y2 = b * sinh(t);
        }
    }

    intersections.push_back({ x1,y1, -x2,y2 });
    return intersections;
}

// Функция для отображения
void display() {
    double x1 = x11;
    double y1 = y11;
    double x2 = x21;
    double y2 = y21;
    double a = a1;
    double b = b1;

    glBegin(GL_LINE_STRIP);
    for (float i = -5; i < 5; i = i + 0.01f) {
        float yi = i * i;
        glVertex2d(i, yi);
    }
    glEnd();

    // Прямая
    glBegin(GL_LINES);
    glVertex2d(x1, y1); // x1, y1
    glVertex2d(x2, y2);    // x2, y2
    glEnd();

    // Гипербола
    glBegin(GL_LINE_STRIP);
    for (double t = -2; t <= 2; t += 0.01) {
        double x = a * cosh(t);
        double y = b * sinh(t);
        glVertex2d(x, y);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (double t = -2; t <= 2; t += 0.01) {
        double x = -a * cosh(t);
        double y = b * sinh(t);
        glVertex2d(x, y);
    }
    glEnd();

    // Точки пересечения
    auto intersections = findIntersection(x1, x2, y1, y2, a, b);
    glPointSize(10);
    glBegin(GL_POINTS);
    for (const auto& point : intersections) {
        if (x2 > point.x1 && x1 < point.x1) {
            glVertex2d(point.x1, point.y1);
        }
        if (x1 < point.x2 && x2 > point.x2) {
            glVertex2d(point.x2, point.y2);
        }
    }
    glEnd();

    glFlush();
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

void Render(RECT& clientRect)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    int Height = clientRect.bottom - clientRect.top;
    int Width = clientRect.right - clientRect.left;

    float W = Width * 0.95;
    float W1 = Width;
    float H = Height / 21.64;

    btn1 = { "X1+", {W - 20,75, W,75, W,90, W - 20,90} };
    btn2 = { "X1-", {W - 20,95, W,95, W,110, W - 20,110} };
    btn3 = { "x2+", {W - 20,115, W,115, W,130, W - 20,130} };
    btn4 = { "x2-", {W - 20,135, W,135, W,150, W - 20,150} };
    btn5 = { "y1+", {W - 20,155, W,155, W,170, W - 20,170} };
    btn6 = { "y1-", {W - 20,175, W,175, W,190, W - 20,190} };
    btn7 = { "y2+", {W - 20,195, W,195, W,210, W - 20,210} };
    btn8 = { "y2-", {W - 20,215, W,215, W,230, W - 20,230} };
    btnExit = { "Exit", {W1 * (float)0.9489 ,0, W1,0, W1,H, W1 * (float)0.9489,H} };

    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Устанавливаем 2D проекцию
    glViewport(0, 0, Width, Height); // главное окно

    glColor3f(0, 0, 0);
    OutText(text1, 6.0f, 6.3f);
    OutText(text2, 6.0f, 5.0f);
    OutText(text3, 6.0f, 3.5f);
    OutText(text4, 6.0f, 2.0f);
    OutText(text5, -9.0f, 9.2f);

    glColor3f(0, 0, 0);
    x1_text = FloatToChar(x11);
    char arr1[4] = { x1_text[0], x1_text[1], x1_text[2] };
    OutText(arr1, 7.5f, 6.3f);

    x2_text = FloatToChar(x21);
    char arr2[4] = { x2_text[0], x2_text[1], x2_text[2] };
    OutText(arr2, 7.5f, 5.0f);

    y1_text = FloatToChar(y11);
    char arr3[4] = { y1_text[0], y1_text[1], y1_text[2] };
    OutText(arr3, 7.5f, 3.5f);

    y2_text = FloatToChar(y21);
    char arr4[4] = { y2_text[0], y2_text[1], y2_text[2] };
    OutText(arr4, 7.5f, 2.0f);

    glColor3f(0, 0, 0);
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
    ShowMenu(Width, Height, btn7);
    ShowMenu(Width, Height, btn8);
    ShowMenu(Width, Height, btnExit);

    glViewport(Width / 15.68, Height / 10.82, Width * 0.65, Height * 0.74);  // график

    glColor3f(1, 1, 1);
    Background(arr_background, GL_TRIANGLE_FAN, 4);

    glColor3f(0.85f, 0.85f, 0.85f);
    Background(arr_background1, GL_LINE_LOOP, 4);

    float k = Width / Height;
    if (Width >= Height) {
        glOrtho(-k, k, -1.0, 1.0, -1.0, 1.0);
    }
    else {
        glOrtho(-1.0, 1.0, -1.0 / k, 1.0 / k, -1.0, 1.0);
    }

    glColor3f(0.85f, 0.85f, 0.85f);
    grid(-10.0, 10.0, -10.0, 10.0, 1, 1);

    glColor3f(0, 0, 0);
    CoordinateAxis(-10.0, 10.0, -10.0, 10.0, 1, 1);

    glColor3f(0.0, 0.0, 0.0); // Устанавливаем цвет линий
    display();
}
