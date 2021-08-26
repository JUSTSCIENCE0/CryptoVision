#include "pch.h"
#include "ColorSpaceConverter.h"

RGBpoint* RowToBitmap(BYTE* data, int left, int right)
{
    RGBpoint* output = new RGBpoint[(right - left) / 3];
    int i;
    for (i = 0; i < (right - left); i += 3)
    {
        output[i / 3].B = (int)data[i + left];
        output[i / 3].G = (int)data[i + 1 + left];
        output[i / 3].R = (int)data[i + 2 + left];
    }
    return output;
}

void RGBtoYUV(RGBpoint* data, YUVpoint*& out, int left, int right)
{
    float* YR = new float[8]; float* YG = new float[8]; float* YB = new float[8];
    float* CR = new float[8]; float* CB = new float[8]; float* UVNULL = new float[8];
    float* MINUS = new float[8];
    for (int i = 0; i < 8; i++)
    {
        //сохранение коэффициентов для преобразования в массивы по 8 элементов
        //для получения возможности использования в SIMD функциях
        YR[i] = 0.299f; YG[i] = 0.587f; YB[i] = 0.114f;
        CR[i] = 1.402f; CB[i] = 1.772f; UVNULL[i] = 128; MINUS[i] = -1;
    }
    float* Y = new float[right - left];
    float* U = new float[right - left];
    float* V = new float[right - left];
    __m256 yr = _mm256_load_ps(YR);
    __m256 yg = _mm256_load_ps(YG);
    __m256 yb = _mm256_load_ps(YB);
    __m256 cr = _mm256_load_ps(CR);
    __m256 cb = _mm256_load_ps(CB);
    __m256 uvnull = _mm256_load_ps(UVNULL);
    __m256 minus = _mm256_load_ps(MINUS);
    for (int i = left; i < right; i += 8, Y += 8, U += 8, V += 8)
    {
        //загрузка информации о цвете в блоки по 8 элеметров
        __m256 r = _mm256_set_ps((float)data[i + 7].R, (float)data[i + 6].R, (float)data[i + 5].R,
            (float)data[i + 4].R, (float)data[i + 3].R, (float)data[i + 2].R, (float)data[i + 1].R, (float)data[i].R);
        __m256 g = _mm256_set_ps((float)data[i + 7].G, (float)data[i + 6].G, (float)data[i + 5].G,
            (float)data[i + 4].G, (float)data[i + 3].G, (float)data[i + 2].G, (float)data[i + 1].G, (float)data[i].G);
        __m256 b = _mm256_set_ps((float)data[i + 7].B, (float)data[i + 6].B, (float)data[i + 5].B,
            (float)data[i + 4].B, (float)data[i + 3].B, (float)data[i + 2].B, (float)data[i + 1].B, (float)data[i].B);
        /*
        выполнение арифметики:
        Y = 0.299 * R + 0.587 * G + 0.114 * B;
        V = (R - Y) / 1.402 + 128;
        U = (B - Y) / 1.772 + 128;
        */
        __m256 m1 = _mm256_mul_ps(yr, r);
        __m256 m2 = _mm256_mul_ps(yg, g);
        __m256 m3 = _mm256_mul_ps(yb, b);
        __m256 sum = _mm256_add_ps(m1, m2);
        __m256 y = _mm256_add_ps(sum, m3);
        __m256 negY = _mm256_mul_ps(y, minus);
        m1 = _mm256_add_ps(r, negY);
        m2 = _mm256_div_ps(m1, cr);
        __m256 v = _mm256_add_ps(m2, uvnull);
        m1 = _mm256_add_ps(b, negY);
        m2 = _mm256_div_ps(m1, cb);
        __m256 u = _mm256_add_ps(m2, uvnull);
        _mm256_store_ps(Y, y);
        _mm256_store_ps(U, u);
        _mm256_store_ps(V, v);
    }
    Y -= (right - left); U -= (right - left); V -= (right - left);
    for (int i = left; i < right; i++)
    {
        out[i].Y = (int)Y[i - left];
        out[i].U = (int)U[i - left];
        out[i].V = (int)V[i - left];
    }
}

YUVpoint RGBtoYUVWithoutOptimization(RGBpoint data)
{
    YUVpoint out;
    out.Y = 0.299 * data.R + 0.587 * data.G + 0.114 * data.B;
    out.V = (data.R - out.Y) / 1.402 + 128;
    out.U = (data.B - out.Y) / 1.772 + 128;
    return out;
}

void YUV444toRowYUYV(YUVpoint* data, int widht, int height, int frame, BYTE*& outdata)
{
    int size = 2 * widht * height;
    for (int i = 0; i < size; i += 2)
    {
        outdata[i + frame * size] = data[i / 2].Y;
    }
    for (int i = 0; i < size; i += 4)
    {
        outdata[i + 1 + frame * size] = data[i / 2].U;
        outdata[i + 3 + frame * size] = data[i / 2].V;
    }
}

void YUV444toRowYUV(YUVpoint* data, int widht, int height, int frame, BYTE*& outdata)
{
    int size = widht * height;
    for (int i = 0; i < size; i++)
    {
        outdata[i * 3] = data[i].Y;
        outdata[i * 3 + 1] = data[i].U;
        outdata[i * 3 + 2] = data[i].V;
    }
}

void Processing(BYTE* RGBdata, BYTE*& outYUV, int frame, int widht, int heidht)
{
    int size = 3 * widht * heidht;
    RGBpoint* data = RowToBitmap(RGBdata, 12 + frame * size, 12 + (frame + 1) * size);

    YUVpoint* YUVdata = new YUVpoint[widht * heidht];
    if ((widht * heidht) % 8 == 0)
    {
        RGBtoYUV(data, YUVdata, 0, widht * heidht);
    }
    else
    {
        for (int i = 0; i < widht * heidht; i++)
        {
            YUVdata[i] = RGBtoYUVWithoutOptimization(data[i]);
        }
    }
    YUV444toRowYUYV(YUVdata, widht, heidht, frame, outYUV);
    free(data);
    free(YUVdata);
}

BYTE* ConvertColorSpace(BYTE* RGBdata)
{
    UINT32 number = RGBdata[0] + (RGBdata[1] << 8) + (RGBdata[2] << 16) + (RGBdata[3] << 24);
    UINT32 widht = RGBdata[4] + (RGBdata[5] << 8) + (RGBdata[6] << 16) + (RGBdata[7] << 24);
    UINT32 heidht = RGBdata[8] + (RGBdata[9] << 8) + (RGBdata[10] << 16) + (RGBdata[11] << 24);

    int outsize = 2 * widht * heidht * number;
    BYTE* YUVdata = new BYTE[outsize];

    std::thread* thr = new std::thread[number];

    for (int i = 0; i < number; i++)
    {
        //Processing(RGBdata, YUVdata, i, widht, heidht);
        thr[i] = std::thread(Processing, RGBdata, std::ref(YUVdata), i, widht, heidht);
        thr[i].join();
    }

    BYTE* result = new BYTE[(outsize + 12)];

    for (int i = 0; i < 12; i++)
    {
        result[i] = RGBdata[i];
    }

    for (int i = 0; i < outsize; i++)
    {
        result[i + 12] = YUVdata[i];
    }

    return result;
}

