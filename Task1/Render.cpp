// glWinApp.cpp : Defines the entry point for the application.
#include "pch.h"
#include "glWinApp.h"

extern LPCSTR s1, s2, s3;

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

void Render(RECT& clientRect)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    int Height = clientRect.bottom - clientRect.top;
    int Width = clientRect.right - clientRect.left;

    glViewport(0, 0, Width, Height);
    gluOrtho2D(-9.5, 2.5, -5.5, 1.5);

    /*glColor3d(1, 1, 1);

    glBegin(GL_TRIANGLES);

        glVertex2d(-1, 1);
        glVertex2d(1, -1);
        glVertex2d(1, 1);

    glEnd();*/

    glLineWidth(1);
    glColor3d(0, 0, 0);

    glLineStipple(1, 0xF0F0);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);

        for (float i = -7.5; i < 1.6; i++) {
            glVertex2d(i, 0.8);
            glVertex2d(i, -4.5);
        }

        for (float i = -3.5; i < 0.6; i++) {
            glVertex2d(-8.5, i);
            glVertex2d(1.8, i);
        }

    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glLineWidth(3);
    glColor3d(0, 0, 0);

    glBegin(GL_LINES);

        glVertex2d(-8.5, -3.6);
        glVertex2d(-8.5, 0.8);

        glVertex2d(-7.6, -4.5);
        glVertex2d(1.8, -4.5);

        glVertex2d(-8.4, 0.6);
        glVertex2d(-8.5, 0.8);

        glVertex2d(-8.6, 0.6);
        glVertex2d(-8.5, 0.8);

        glVertex2d(1.6, -4.6);
        glVertex2d(1.8, -4.5);

        glVertex2d(1.6, -4.4);
        glVertex2d(1.8, -4.5);

    glEnd();

    glLineWidth(3);
    glColor3d(0, 0, 0);

    glBegin(GL_LINE_LOOP);

        glVertex2d(-7.5, -3.5);
        glVertex2d(-7.5, -0.5);
        glVertex2d(-6.5, 0.5);
        glVertex2d(-4.5, -0.5);
        glVertex2d(-4.5, -2.5);
        glVertex2d(-6.5, -3.5);

    glEnd();

    glColor3d(0, 0, 0);
    glPointSize(10);
    glBegin(GL_POINTS);

        glVertex2d(-2.5, -3.5);
        glVertex2d(-2.5, -0.5);
        glVertex2d(-1.5, 0.5);
        glVertex2d(0.5, -0.5);
        glVertex2d(0.5, -2.5);
        glVertex2d(-1.5, -3.5);

    glEnd();
}
