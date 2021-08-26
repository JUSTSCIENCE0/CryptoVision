#pragma once

#include "pch.h"

#ifdef COLORSPACECONVERTER_EXPORTS
#define COLORSPACECONVERTER_API __declspec(dllexport)
#else
#define COLORSPACECONVERTER_API __declspec(dllimport)
#endif

typedef struct { int R; int G; int B; } RGBpoint;
typedef struct { int Y; int U; int V; } YUVpoint;

extern "C" COLORSPACECONVERTER_API BYTE* ConvertColorSpace(BYTE* RGBdata);
