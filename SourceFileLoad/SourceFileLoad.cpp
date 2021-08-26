#include "pch.h"
#include "SourceFileLoad.h"

typedef struct { int W; int H; } ImgRect;

BYTE* readBMP(std::string filename, int& sz, ImgRect& rct)
{
    int i, j;
    const int lk = 54;
    FILE* f = fopen(filename.c_str(), "rb");
    if (f == NULL)
    {
        return NULL;
    }
    BYTE info[lk];
    fread(info, sizeof(BYTE), lk, f);
    int width = *(int*)& info[18];
    int height = *(int*)& info[22];
    sz = 3 * width * height;
    rct.W = width;
    rct.H = height;
    BYTE* dt = new BYTE[sz];
    fread(dt, sizeof(BYTE), sz, f);
    fclose(f);
    /*
    � ������� dt ������ ����������� ����� �������, ��� ����������� ������������ ���������� �� ���������
    ����� ����������� ��������� ����������� �� ���������
    */
    BYTE* data = new BYTE[sz];
    for (j = 0; j < height; j++)
        for (i = 0; i < width * 3; i++) data[i + width * j * 3] = dt[i + width * (height - 1 - j) * 3];
    return data;
}

BYTE* LoadSourceData(std::string Path, int number)
{
    if (number < 1)
    {
        //������ ������������ ������ ����� ��������
        return NULL;
    }

    //���������� �������� ������, �� ������� ������
    std::string* names = new std::string[number];
    for (int n = 1; n <= number; n++)
    {
        std::string s = std::to_string(n);
        while (s.length() < 4)
        {
            s = "0" + s;
        }
        names[n - 1] = Path + s + ".bmp";
    }
    
    //������ ������ ����
    int size;
    ImgRect rect;

    BYTE* fromBMP = readBMP(names[0], size, rect);

    //�� ������� ����� �������� ������, ������ � ������
    //��� ��������� ����� ���������� � � ���� ����� ������������ ��� ������ �����
    BYTE* data = new BYTE[12 + size*number];

    int numn = number;
    int wh = rect.W;
    int hh = rect.H;

    //���������� ���������� ������ � �� �����������
    for (int i = 0; i < 4; i++)
    {
        data[i] = (BYTE)numn;
        data[i + 4] = (BYTE)wh;
        data[i + 8] = (BYTE)hh;
        numn >>= 8;
        wh >>= 8;
        hh >>= 8;
    }

    //���������� ������ �����������
    for (int i = 0; i < size; i++)
    {
        data[12 + i] = fromBMP[i];
    }

    //��������� � ���������� �����������
    for (int n = 1; n < number; n++)
    {
        int t_size;
        ImgRect t_rect;
        fromBMP = readBMP(names[n], t_size, t_rect);
        if ((t_size == size) && (t_rect.W == rect.W) && (t_rect.H == rect.H))
        {
            for (int i = 0; i < size; i++)
            {
                data[12 + n*size + i] = fromBMP[i];
            }
        }
        else
        {
            //��� ����� ������ ���� ������ �������
            return NULL;
        }
    }

    return data;
}