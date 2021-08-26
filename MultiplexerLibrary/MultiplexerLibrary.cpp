#include "pch.h"
#include "MultiplexerLibrary.h"
#include <cstdlib>

BYTE* ConvertINT32toBYTE(UINT32 num)
{
    BYTE* res = new BYTE[4];
    for (int i = 0; i < 4; i++)
    {
        res[i] = (BYTE)num;
        num >>= 8;
    }
    return res;
}

void WriteToStream(BYTE*& rs, BYTE* data, int offset, int size)
{
    for (int i = offset; i < offset + size; i++)
    {
        rs[i] = data[i - offset];
    }
}


BYTE* GetAVIStream(BYTE* YUYVStream, BYTE* WAVEStream)
{
    UINT32 number = YUYVStream[0] + (YUYVStream[1] << 8) + (YUYVStream[2] << 16) + (YUYVStream[3] << 24);
    UINT32 widht = YUYVStream[4] + (YUYVStream[5] << 8) + (YUYVStream[6] << 16) + (YUYVStream[7] << 24);
    UINT32 heidht = YUYVStream[8] + (YUYVStream[9] << 8) + (YUYVStream[10] << 16) + (YUYVStream[11] << 24);

    BYTE blockRIFF[] = { 0x52, 0x49, 0x46, 0x46 }; //RIFF
    BYTE* word = new BYTE[4];
    UINT32 size = 524 + (widht * heidht * 2 + 8) * number + 1772 * number + number * 16; //Размер AVI RIFF

    BYTE* resultStream = new BYTE[size + 8];
    WriteToStream(resultStream, blockRIFF, 0, 4);
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 4, 8);

    BYTE blockHDRL1[] = {
        0x41, 0x56, 0x49, 0x20,  //AVI
        0x4C, 0x49, 0x53, 0x54,  //LIST
        0xB4, 0x01, 0x00, 0x00,  //Размер LIST hdrl - 436 - константа
        0x68, 0x64, 0x72, 0x6C,  //hdrl
        0x61, 0x76, 0x69, 0x68,  //avih
        0x38, 0x00, 0x00, 0x00,  //размер avih = 56 - константа
        0x40, 0x9C, 0x00, 0x00,  //обновление раз в 40000 мкСек (25 fps) - константа
        0x7B, 0xA7, 0x52, 0x00,  //максимальное количество данных в секунду - константа
        0x01, 0x00, 0x00, 0x00,  //файл должен быть кратен данному числу - 1 - константа
        0x00, 0x00, 0x00, 0x00   //флаги, нам не интересны - 0 - константа
    };
    WriteToStream(resultStream, blockHDRL1, 8, 40);
    //std::free(blockHDRL1);

    word = ConvertINT32toBYTE(number);
    WriteToStream(resultStream, word, 48, 4); //количество кадров в файле

    BYTE NextBlock[] = {
        0x00, 0x00, 0x00, 0x00,  //Ignore that (c) спецификация AVI
        0x02, 0x00, 0x00, 0x00   //Количество потоков в файле (два - аудио и видео) - константа
    };
    WriteToStream(resultStream, NextBlock, 52, 8);
    //std::free(NextBlock);

    size = widht * heidht * 2 + 8;  //размер буфера для хранения кадра
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 60, 4);

    word = ConvertINT32toBYTE(widht);  //ширина кадра
    WriteToStream(resultStream, word, 64, 4);

    word = ConvertINT32toBYTE(heidht);  //высота кадра
    WriteToStream(resultStream, word, 68, 4);

    size = 0;
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 72, 4);  //зарезервировано
    WriteToStream(resultStream, word, 76, 4);  //зарезервировано
    WriteToStream(resultStream, word, 80, 4);  //зарезервировано
    WriteToStream(resultStream, word, 84, 4);  //зарезервировано

    BYTE blockSTRL1[] = {
        0x4C, 0x49, 0x53, 0x54,  //LIST
        0xA4, 0x00, 0x00, 0x00,  //Размер LIST strl - 164 - константа
        0x73, 0x74, 0x72, 0x6C,  //strl
        0x73, 0x74, 0x72, 0x68,  //strh
        0x38, 0x00, 0x00, 0x00,  //размер strh = 56 - константа
        0x76, 0x69, 0x64, 0x73,  //что лежит в потоке (vids - видео)
        0x59, 0x55, 0x59, 0x32,  //кодек (YUY2 - YUYV)
        0x00, 0x00, 0x00, 0x00,  //флаги, нам не интересны - 0
        0x00, 0x00, 0x00, 0x00,  //флаги, нам не интересны - 0
        0x00, 0x00, 0x00, 0x00,  //номер первого кадра - 0
        0x80, 0x1A, 0x06, 0x00,  //dwScale - 400000, обновлять кадр каждые n юнитов
        0x80, 0x96, 0x98, 0x00,  //dwRate - 10000000, количество юнитов в секунду
        0x00, 0x00, 0x00, 0x00  //стартовая позиция
    };
    WriteToStream(resultStream, blockSTRL1, 88, 52);
    //std::free(blockSTRL1);

    word = ConvertINT32toBYTE(number);
    WriteToStream(resultStream, word, 140, 4); //количество кадров в потоке

    size = widht * heidht * 2 + 8;  //размер буфера для хранения кадра
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 144, 4);

    size = 0;
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 148, 4);  //качество видео - не важно
    WriteToStream(resultStream, word, 152, 4);  //количество байт в сэмпле - не важно
    WriteToStream(resultStream, word, 156, 4);  //прямоугольник кадра - начало

    size = widht + (heidht << 16);  //прямоугольник кадра - конец
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 160, 4);

    BYTE blockSTRF[] = {
        0x73, 0x74, 0x72, 0x66,  //strf
        0x28, 0x00, 0x00, 0x00,  //размер strf - 40 - константа
        0x28, 0x00, 0x00, 0x00   //размер блока опять - 40 - константа
    };
    WriteToStream(resultStream, blockSTRF, 164, 12);
    //std::free(blockSTRF);

    word = ConvertINT32toBYTE(widht);  //ширина кадра
    WriteToStream(resultStream, word, 176, 4);

    word = ConvertINT32toBYTE(heidht);  //высота кадра
    WriteToStream(resultStream, word, 180, 4);

    BYTE NextBlock2[] = {
        0x01, 0x00, 0x10, 0x00,  //1 плоскость и 16 бит на точку
        0x59, 0x55, 0x59, 0x32,  //кодек (YUY2 - YUYV)
    };
    WriteToStream(resultStream, NextBlock2, 184, 8);
    //std::free(NextBlock2);

    size = widht * heidht * 2;  //бит на кадр
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 192, 4);

    BYTE blockINDX1[] = {
        0x27, 0x07, 0x00, 0x00,  //dpi по горизонтали - константа
        0xD0, 0x07, 0x00, 0x00,  //dpi по вертикали - константа
        0x00, 0x00, 0x00, 0x00,  //используем дефолтную палитру
        0x00, 0x00, 0x00, 0x00,  //все цвета равны
        0x69, 0x6E, 0x64, 0x78,  //indx
        0x28, 0x00, 0x00, 0x00,  //размер indx - 40 - константа
        0x04, 0x00, 0x00, 0x00,  //wLongsPerEntry, bIndexType, bIndexSubType
        0x01, 0x00, 0x00, 0x00,  //nEntriesInUse - количество в сампле
        0x30, 0x30, 0x64, 0x62,  //00db
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0xD4, 0x01, 0x00, 0x00,  //смещение начала
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x30, 0x00, 0x00, 0x00   //размер indx - 48 - константа
    };
    WriteToStream(resultStream, blockINDX1, 196, 60);
    //std::free(blockINDX1);

    word = ConvertINT32toBYTE(number);
    WriteToStream(resultStream, word, 256, 4); //количество кадров в потоке

    BYTE blockINDX2[] = {
        0x4C, 0x49, 0x53, 0x54,  //LIST
        0xA4, 0x00, 0x00, 0x00,  //Размер LIST strl - 164 - константа
        0x73, 0x74, 0x72, 0x6C,  //strl
        0x73, 0x74, 0x72, 0x68,  //strh
        0x38, 0x00, 0x00, 0x00,  //размер strh = 56 - константа
        0x61, 0x75, 0x64, 0x73,  //что лежит в потоке auds
        0x00, 0x00, 0x00, 0x00,  //нет кодирования
        0x00, 0x00, 0x00, 0x00,  //флаги, нам не интересны - 0
        0x00, 0x00, 0x00, 0x00,  //флаги, нам не интересны - 0
        0x00, 0x00, 0x00, 0x00,  //номер первого кадра - 0
        0x01, 0x00, 0x00, 0x00,  //dwScale - 1, обновлять кадр каждые n юнитов
        0x44, 0xAC, 0x00, 0x00,  //dwRate - 44100, количество юнитов в секунду
        0x00, 0x00, 0x00, 0x00   //стартовая позиция - РАССЧИТЫВАЕТСЯ
    };
    WriteToStream(resultStream, blockINDX2, 260, 52);
    //std::free(blockINDX2);

    size = 1764 * number;  //количество сэмплов в потоке
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 312, 4);

    BYTE blockSTRF2[] = {
        0xEC, 0x06, 0x00, 0x00,  //размер буфера для хранения кадра
        0x00, 0x00, 0x00, 0x00,  //качество видео - не важно
        0x01, 0x00, 0x00, 0x00,  //количество байт в сэмпле - константа
        0x00, 0x00, 0x00, 0x00,  //прямоугольник кадра
        0x00, 0x00, 0x00, 0x00,  //0,0,0,0
        0x73, 0x74, 0x72, 0x66,  //strf
        0x28, 0x00, 0x00, 0x00,  //размер strf - 40 - константа
        0x01, 0x00, 0x01, 0x00,  //без сжатия - один канал
        0x44, 0xAC, 0x00, 0x00,  //частота дискретизации - 44100
        0x44, 0xAC, 0x00, 0x00,  //размер буфера для хранения кадра
        0x01, 0x00, 0x08, 0x00,  //длина блока и битрэйт
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x69, 0x6E, 0x64, 0x78,  //indx
        0x28, 0x00, 0x00, 0x00,  //размер indx - 40 - константа
        0x04, 0x00, 0x00, 0x00,  //wLongsPerEntry, bIndexType, bIndexSubType
        0x01, 0x00, 0x00, 0x00,  //nEntriesInUse - количество в сампле
        0x30, 0x31, 0x77, 0x62,  //01wb
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00,  //зарезервировано
        0x00, 0x00, 0x00, 0x00   //зарезервировано
    };
    WriteToStream(resultStream, blockSTRF2, 316, 100);
    //std::free(blockSTRF2);

    size = 500 + number * 8;  //смещение начала
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 416, 4);

    size = 0;
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 420, 4);  //зарезервировано

    size = 30;  //общий размер indx - 48 - константа
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 424, 4);

    size = 1764 * number;  //количество сэмплов в потоке
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 428, 4);

    BYTE blockODML[] = {
        0x4C, 0x49, 0x53, 0x54,  //LIST
        0x10, 0x00, 0x00, 0x00,  //Размер LIST odml - 16 - константа
        0x6F, 0x64, 0x6D, 0x6C,  //odml
        0x64, 0x6D, 0x6C, 0x68,  //dmlh
        0x01, 0x00, 0x00, 0x00   //Размер dmlh - 1 - константа
    };
    WriteToStream(resultStream, blockODML, 432, 20);
    //std::free(blockODML);

    size = number;  //количество кадров в потоке
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 452, 4);

    size = 0x5453494C;  //LIST
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 456, 4);

    size = 68 + (widht * heidht * 2 + 8) * number + 1772 * number + number * 16; //Размер LIST movi
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 460, 4);

    BYTE blockMOVI1[] = {
        0x6D, 0x6F, 0x76, 0x69,  //movi
        0x69, 0x78, 0x30, 0x30   //ix00
    };
    WriteToStream(resultStream, blockMOVI1, 464, 8);
    //std::free(blockMOVI1);

    size = 24 + number * 8;  //Размер ix00
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 472, 4);

    size = 0x01000002;  //wLongsPerEntry,  bIndexSubType, bIndexType
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 476, 4);

    word = ConvertINT32toBYTE(number);  //количество кадров в потоке
    WriteToStream(resultStream, word, 480, 4);

    size = 0x62643030;  //00db
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 484, 4);

    size = 532 + 16 * number;  //стандартный сдвиг
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 488, 4);

    size = 0;
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, 492, 4);  //зарезервировано
    WriteToStream(resultStream, word, 496, 4);  //зарезервировано

    int ofset = 500;
    for (int i = 0; i < number; i++)
    {
        size = (widht * heidht * 2) * i + 8 * (i + 1);
        word = ConvertINT32toBYTE(size);
        WriteToStream(resultStream, word, ofset, 4);
        size = widht * heidht * 2;
        word = ConvertINT32toBYTE(size);
        WriteToStream(resultStream, word, ofset + 4, 4);
        ofset += 8;
    }

    size = 0x31307869;  //ix01
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, ofset, 4);
    ofset += 4;

    size = 24 + number * 8;  //Размер ix01
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, ofset, 4);
    ofset += 4;

    size = 0x01000002;  //wLongsPerEntry,  bIndexSubType, bIndexType
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, ofset, 4);
    ofset += 4;

    word = ConvertINT32toBYTE(number);  //количество кадров в потоке
    WriteToStream(resultStream, word, ofset, 4);
    ofset += 4;

    size = 0x62773130;  //01wb
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, ofset, 4);
    ofset += 4;

    size = (widht * heidht * 2 + 8) * number;  //стандартный сдвиг
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, ofset, 4);
    ofset += 4;

    size = 0;
    word = ConvertINT32toBYTE(size);
    WriteToStream(resultStream, word, ofset, 4);  //зарезервировано
    WriteToStream(resultStream, word, ofset, 4);  //зарезервировано
    ofset += 8;

    for (int i = 0; i < number; i++)
    {
        size = 1764 * i + 8 * (i + 1);
        word = ConvertINT32toBYTE(size);
        WriteToStream(resultStream, word, ofset, 4);
        size = 1764;
        word = ConvertINT32toBYTE(size);
        WriteToStream(resultStream, word, ofset + 4, 4);
        ofset += 8;
    }

    for (int i = 0; i < number; i++)
    {
        BYTE* Video = new BYTE[widht * heidht * 2 + 8];
        Video[0] = 0x30;  Video[1] = 0x30;  Video[2] = 0x64;  Video[3] = 0x62;
        //Video[4] = 0x00;  Video[5] = 0x18;  Video[6] = 0x03;  Video[7] = 0x00;

        size = widht * heidht * 2;
        word = ConvertINT32toBYTE(size);
        WriteToStream(Video, word, 4, 4);

        for (int j = 0; j < widht * heidht * 2; j++)
        {
            Video[j + 8] = YUYVStream[widht * heidht * 2 * i + j + 12];
        }
        WriteToStream(resultStream, Video, ofset, widht* heidht * 2 + 8);
        ofset += (widht * heidht * 2 + 8);
        std::free(Video);
    }

    for (int i = 0; i < number; i++)
    {
        BYTE* Video = new BYTE[1764 + 8];
        Video[0] = 0x30;  Video[1] = 0x31;  Video[2] = 0x77;  Video[3] = 0x62;
        Video[4] = 0xE4;  Video[5] = 0x06;  Video[6] = 0x00;  Video[7] = 0x00;
        for (int j = 0; j < 1764; j++)
        {
            Video[j + 8] = WAVEStream[1764 * i + j];
        }
        WriteToStream(resultStream, Video, ofset, 1772);
        ofset += 1772;
        std::free(Video);
    }

    return resultStream;
}