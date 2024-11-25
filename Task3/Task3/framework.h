#pragma once

#include "targetver.h"
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN             

// Windows Header Files
#include <windows.h>
#include <windowsx.h>

// OpenGL headers files
#include <GL\GL.h>
#include <GL\GLU.h>

// OpenGL link files
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "glu32.lib")