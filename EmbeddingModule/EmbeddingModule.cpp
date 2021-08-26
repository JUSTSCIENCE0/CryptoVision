#include "pch.h"
#include "EmbeddingModule.h"


bool* BYTEStoBOOLS(BYTE* data, UINT16 dataSize)
{
    bool* result = new bool[8 * dataSize + 16];
    UINT16 sz = dataSize;
    for (int n = 0; n < dataSize; n++)
    {
        for (int i = 0; i < 8; i++)
        {
            result[16 + 8 * n + i] = data[n] & 0x0001;
            data[n] >>= 1;
        }
    }
    BYTE first = (BYTE)sz;
    sz >>= 8;
    BYTE second = (BYTE)sz;
    for (int i = 0; i < 8; i++)
    {
        result[i] = first & 0x0001;
        result[i + 8] = second & 0x0001;
        first >>= 1;
        second >>= 1;
    }
    return result;
}

BYTE PutIn(BYTE data, bool bit)
{
    BYTE res = data & 0xFE;
    res = res ^ (int)bit;
    return res;
}

bool GetBit(BYTE data)
{
    return ((data & 0x01) == 1);
}

BYTE* EmbedData(BYTE* Stream, BYTE* data, UINT16 dataSize)
{
    bool* bits = BYTEStoBOOLS(data, dataSize);

    for (int i = 12; i < 8 * dataSize + 28; i++)
    {
        Stream[i] = PutIn(Stream[i], bits[i - 12]);
    }

    return Stream;
}

BYTE* GetData(BYTE* Stream, UINT16& dataSize)
{
    for (int i = 15; i >= 0; i--)
    {
        int test = Stream[i + 12];
        dataSize <<= 1;
        dataSize += (int)GetBit(Stream[i + 12]);
    }
    BYTE* data = new BYTE[dataSize];
    for (int n = 0; n < dataSize; n++)
    {
        data[n] = 0;
        for (int i = 7; i >= 0; i--)
        {
            data[n] <<= 1;
            data[n] += (int)GetBit(Stream[8 * n + i + 28]);
        }
    }

    return data;
}