#pragma once

#ifdef MULTIPLEXERLIBRARY_EXPORTS
#define MULTIPLEXERLIBRARY_API __declspec(dllexport)
#else
#define MULTIPLEXERLIBRARY_API __declspec(dllimport)
#endif

extern "C" MULTIPLEXERLIBRARY_API BYTE* GetAVIStream(BYTE* YUYVStream, BYTE* WAVEStream);
