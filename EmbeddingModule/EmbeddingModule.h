#pragma once

#ifdef EMBEDDINGMODULE_EXPORTS
#define EMBEDDINGMODULE_API __declspec(dllexport)
#else
#define EMBEDDINGMODULE_API __declspec(dllimport)
#endif

extern "C" EMBEDDINGMODULE_API BYTE* EmbedData(BYTE* Stream, BYTE* data, UINT16 dataSize);
extern "C" EMBEDDINGMODULE_API BYTE* GetData(BYTE* Stream, UINT16& dataSize);
