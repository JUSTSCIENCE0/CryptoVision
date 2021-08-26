#pragma once

#ifdef SOUNDGENERATELIBRARY_EXPORTS
#define SOUNDGENERATELIBRARY_API __declspec(dllexport)
#else
#define SOUNDGENERATELIBRARY_API __declspec(dllimport)
#endif

extern "C" SOUNDGENERATELIBRARY_API BYTE* GenerateSound(int type, int freq);