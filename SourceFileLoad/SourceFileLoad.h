#pragma once

#include "pch.h"

#ifdef SOURCEFILELOAD_EXPORTS
#define SOURCEFILELOAD_API __declspec(dllexport)
#else
#define SOURCEFILELOAD_API __declspec(dllimport)
#endif

extern "C" SOURCEFILELOAD_API BYTE* LoadSourceData(std::string Path, int number);