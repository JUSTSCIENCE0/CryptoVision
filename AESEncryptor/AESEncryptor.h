#pragma once

#ifdef AESENCRYPTOR_EXPORTS
#define AESENCRYPTOR_API __declspec(dllexport)
#else
#define AESENCRYPTOR_API __declspec(dllimport)
#endif

extern "C" AESENCRYPTOR_API BYTE* AESEncryption(BYTE* data, BYTE* key, UINT32 size);
extern "C" AESENCRYPTOR_API BYTE* AESDecryption(BYTE* data, BYTE* key, UINT32& size);