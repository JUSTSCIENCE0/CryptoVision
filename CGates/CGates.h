#pragma once

#ifdef CGATES_EXPORTS
#define CGATES_API __declspec(dllexport)
#else
#define CGATES_API __declspec(dllimport)
#endif

extern "C" CGATES_API void PushEncryptEmbedData(BYTE* Text, BYTE* Key, UINT32 size);
extern "C" CGATES_API void ConfigEmbedData(BYTE* EncrKey);
extern "C" CGATES_API void LoadFrames(BYTE * path, UINT32 pathLen, UINT32 frames);
extern "C" CGATES_API void GenSound(UINT32 type, UINT32 freq, UINT32 count);
extern "C" CGATES_API void LoadSound(BYTE * path, UINT32 pathLen, UINT32 count);
extern "C" CGATES_API void SaveAvi(BYTE* path, UINT32 pathLen);
extern "C" CGATES_API void LoadSound(BYTE * path, UINT32 pathLen, UINT32 count);
extern "C" CGATES_API void LoadAviFile(BYTE * path, UINT32 pathLen);
extern "C" CGATES_API UINT8 PullKeyByte();
extern "C" CGATES_API void DecryptText(BYTE * Key);
extern "C" CGATES_API UINT32 PullTextSize();
extern "C" CGATES_API UINT8 PullTextByte();

extern "C" CGATES_API UINT32 forTest();

