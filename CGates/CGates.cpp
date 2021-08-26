#include "pch.h"

#include "CGates.h"

static BYTE* EmTextClosed;
static BYTE* EmbedingData;

BYTE* YUYVRowData;
BYTE* WAVERowData;

static UINT32 EmTextLen;
static UINT32 EmDataLen;

static BYTE* GettingText;
static BYTE* OpenText;
static UINT16 TextLen;
static UINT16 iterator;

void PushEncryptEmbedData(BYTE* Text, BYTE* Key, UINT32 size)
{
    EmTextClosed = AESEncryption(Text, Key, size);
    UINT32 addBlock = 0;
    if (size % 16 != 0)
    {
        addBlock = 16 - size % 16;
    }
    EmTextLen = size + addBlock;
}

void ConfigEmbedData(BYTE* EncrKey)
{
    EmDataLen = EmTextLen + 32;
    EmbedingData = new BYTE[EmDataLen];
    for (int i = 0; i < 32; i++)
    {
        EmbedingData[i] = EncrKey[i];
    }
    for (int i = 0; i < EmTextLen; i++)
    {
        EmbedingData[i + 32] = EmTextClosed[i];
    }
}

void LoadFrames(BYTE* path, UINT32 pathLen, UINT32 frames)
{
    std::string FolderPath = "";
    for (int i = 0; i < pathLen; i++)
    {
        FolderPath += path[i];
    }
    BYTE* RGBRowData = LoadSourceData(FolderPath, frames);
    YUYVRowData = ConvertColorSpace(RGBRowData);
    delete RGBRowData;
    YUYVRowData = EmbedData(YUYVRowData, EmbedingData, EmDataLen);
}

void GenSound(UINT32 type, UINT32 freq, UINT32 count)
{
    WAVERowData = new BYTE[count];
    BYTE* WAVE = GenerateSound(type, freq);
    int itr = 0;
    while (count >= 44100)
    {
        for (int i = 0; i < 44100; i++)
        {
            WAVERowData[44100 * itr + i] = WAVE[i];
        }
        itr++;
        count -= 44100;
    }
    for (int i = 0; i < count; i++)
    {
        WAVERowData[44100 * itr + i] = WAVE[i];
    }
}

void LoadSound(BYTE* path, UINT32 pathLen, UINT32 count)
{
    std::string FilePath = "";
    for (int i = 0; i < pathLen; i++)
    {
        FilePath += path[i];
    }

    FILE* f = fopen(FilePath.c_str(), "rb");
    BYTE* header = new BYTE[44];
    WAVERowData = new BYTE[count];
    fread(header, sizeof(BYTE), 44, f);
    fread(WAVERowData, sizeof(BYTE), count, f);
    fclose(f);
}

void SaveAvi(BYTE* path, UINT32 pathLen)
{
    std::string FilePath = "";
    for (int i = 0; i < pathLen; i++)
    {
        FilePath += path[i];
    }
    BYTE* AVI = GetAVIStream(YUYVRowData, WAVERowData);

    int size = AVI[4] + (AVI[5] << 8) + (AVI[6] << 16) + (AVI[7] << 24) + 8;
    FILE* f = fopen(FilePath.c_str(), "wb");
    fwrite(AVI, sizeof(BYTE), size, f);
    fclose(f);
}

void LoadAviFile(BYTE* path, UINT32 pathLen)
{
    std::string FilePath = "";
    for (int i = 0; i < pathLen; i++)
    {
        FilePath += path[i];
    }
    FILE* f = fopen(FilePath.c_str(), "rb");
    UINT32 num;
    fread(&num, sizeof(UINT32), 1, f);
    fread(&num, sizeof(UINT32), 1, f);
    BYTE* AVI = new BYTE[num];
    fread(AVI, sizeof(BYTE), num, f);
    fclose(f);

    UINT32 number = AVI[40] + (AVI[41] << 8) + (AVI[42] << 16) + (AVI[43] << 24);
    UINT32 widht = AVI[56] + (AVI[57] << 8) + (AVI[58] << 16) + (AVI[59] << 24);
    UINT32 heidht = AVI[60] + (AVI[61] << 8) + (AVI[62] << 16) + (AVI[63] << 24);
    UINT32 offset = AVI[480] + (AVI[481] << 8) + (AVI[482] << 16) + (AVI[483] << 24);

    BYTE* YUYVRowData = new BYTE[number * widht * heidht * 2 + 12];

    for (int i = 0; i < 12; i++)
    {
        YUYVRowData[i] = 0;  //зарезервировано
    }

    for (UINT32 i = 0; i < number; i++)
    {
        offset += 8;
        for (UINT32 j = 0; j < widht * heidht * 2; j++)
        {
            YUYVRowData[widht * heidht * 2 * i + j + 12] = AVI[offset - 8];
            offset++;
        }
    }

    TextLen = 0;
    GettingText = GetData(YUYVRowData, TextLen);
    for (int i = 0; i < 16; i++)
    {
        int p = GettingText[i];
        p++;
    }

    iterator = 0;

}

UINT8 PullKeyByte()
{
    if (iterator > 32) return NULL;
    iterator++;
    return (UINT8)(GettingText[iterator - 1]);
}

void DecryptText(BYTE* Key)
{
    TextLen -= 32;
    BYTE* EncrText = new BYTE[TextLen];
    for (int i = 0; i < TextLen; i++)
    {
        EncrText[i] = GettingText[i + 32];
    }
    UINT32 len = (UINT32)TextLen;
    OpenText = AESDecryption(EncrText, Key, len);
    iterator = 0;
}

UINT32 PullTextSize()
{
    return (UINT32)TextLen;
}

UINT8 PullTextByte()
{
    if (iterator > TextLen) return NULL;
    iterator++;
    return (UINT8)(OpenText[iterator - 1]);
}

UINT32 forTest()
{
    return 2;
}