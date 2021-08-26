#include "pch.h"
#include "AESEncryptor.h"

class AESEncryptor
{
private:
    BYTE Sbox[256] = {
            0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };
    BYTE InvSbox[256] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };
    BYTE Rcon[4] = { 0x01, 0x00, 0x00, 0x00 };
    BYTE State[16];
    BYTE InputBlock[16];
    BYTE OutputBlock[16];
    BYTE RoundKey[16];
    BYTE StartKey[16];
    BYTE** Keys = new BYTE * [10];

    void NextRcon()
    {
        switch (Rcon[0])
        {
        case 0x00:
            Rcon[0] = 0x01;
            break;
        case 0x80:
            Rcon[0] = 0x1b;
            break;
        case 0x36:
            Rcon[0] = 0x01;
            break;
        default:
            Rcon[0] *= 2;
        }
    }

    void SubBytes()
    {
        for (int i = 0; i < 16; i++)
        {
            State[i] = Sbox[(int)State[i]];
        }
    }

    void InvSubBytes()
    {
        for (int i = 0; i < 16; i++)
        {
            State[i] = InvSbox[(int)State[i]];
        }
    }

    void ShiftRows()
    {
        BYTE OS[16];

        OS[0] = State[0];   OS[4] = State[4];   OS[8] = State[8];   OS[12] = State[12];
        OS[1] = State[5];   OS[5] = State[9];   OS[9] = State[13];  OS[13] = State[1];
        OS[2] = State[10];  OS[6] = State[14];  OS[10] = State[2];  OS[14] = State[6];
        OS[3] = State[15];  OS[7] = State[3];   OS[11] = State[7];  OS[15] = State[11];

        for (int i = 0; i < 16; i++)
        {
            State[i] = OS[i];
        }
    }

    void InvShiftRows()
    {
        BYTE OS[16];

        OS[0] = State[0];   OS[4] = State[4];   OS[8] = State[8];   OS[12] = State[12];
        OS[1] = State[13];  OS[5] = State[1];   OS[9] = State[5];   OS[13] = State[9];
        OS[2] = State[10];  OS[6] = State[14];  OS[10] = State[2];  OS[14] = State[6];
        OS[3] = State[7];   OS[7] = State[11];  OS[11] = State[15]; OS[15] = State[3];

        for (int i = 0; i < 16; i++)
        {
            State[i] = OS[i];
        }
    }

    void MixColumns()
    {
        BYTE** C = new BYTE * [4];
        for (int i = 0; i < 4; i++)
        {
            C[i] = new BYTE[4];
        }
        C[0][0] = 0x02; C[0][1] = 0x03; C[0][2] = 0x01; C[0][3] = 0x01;
        C[1][0] = 0x01; C[1][1] = 0x02; C[1][2] = 0x03; C[1][3] = 0x01;
        C[2][0] = 0x01; C[2][1] = 0x01; C[2][2] = 0x02; C[2][3] = 0x03;
        C[3][0] = 0x03; C[3][1] = 0x01; C[3][2] = 0x01; C[3][3] = 0x02;

        BYTE OS[16];

        for (int i = 0; i < 4; i++)
        {
            BYTE SWord[4];
            for (int j = 0; j < 4; j++)
            {
                SWord[j] = State[i * 4 + j];
            }
            for (int j = 0; j < 4; j++)
            {
                int s = C[j][0] * SWord[0] + C[j][1] * SWord[1] + C[j][2] * SWord[2] + C[j][3] * SWord[3];
                OS[i * 4 + j] = s % 256;
            }
        }

        for (int i = 0; i < 16; i++)
        {
            State[i] = OS[i];
        }
    }

    void InvMixColumns()
    {
        BYTE** C = new BYTE * [4];
        for (int i = 0; i < 4; i++)
        {
            C[i] = new BYTE[4];
        }
        C[0][0] = 0xD4; C[0][1] = 0xA1; C[0][2] = 0x07; C[0][3] = 0x3B;
        C[1][0] = 0x3B; C[1][1] = 0xD4; C[1][2] = 0xA1; C[1][3] = 0x07;
        C[2][0] = 0x07; C[2][1] = 0x3B; C[2][2] = 0xD4; C[2][3] = 0xA1;
        C[3][0] = 0xA1; C[3][1] = 0x07; C[3][2] = 0x3B; C[3][3] = 0xD4;

        BYTE OS[16];

        for (int i = 0; i < 4; i++)
        {
            BYTE SWord[4];
            for (int j = 0; j < 4; j++)
            {
                SWord[j] = State[i * 4 + j];
            }
            for (int j = 0; j < 4; j++)
            {
                int s = C[j][0] * SWord[0] + C[j][1] * SWord[1] + C[j][2] * SWord[2] + C[j][3] * SWord[3];
                OS[i * 4 + j] = s % 256;
            }
        }

        for (int i = 0; i < 16; i++)
        {
            State[i] = OS[i];
        }
    }

    void AddRoundKey()
    {
        BYTE OS[16];
        for (int i = 0; i < 16; i++)
        {
            OS[i] = State[i] ^ RoundKey[i];
        }
        for (int i = 0; i < 16; i++)
        {
            State[i] = OS[i];

        }
    }

    void NextRoundKey()
    {
        UINT startKey[4];
        UINT endKey[4];
        BYTE w3[4];
        for (int i = 0; i < 4; i++)
        {
            startKey[i] = (RoundKey[4 * i] << 24) + (RoundKey[4 * i + 1] << 16) + (RoundKey[4 * i + 2] << 8) + RoundKey[4 * i + 3];
            w3[i] = RoundKey[i + 12];
        }
        BYTE tmp = w3[0];
        w3[0] = w3[1]; w3[1] = w3[2]; w3[2] = w3[3]; w3[3] = tmp;

        for (int i = 0; i < 4; i++)
        {
            w3[i] = Sbox[(int)w3[i]];
            w3[i] = w3[i] ^ Rcon[i];
        }
        NextRcon();
        UINT word3 = (w3[0] << 24) + (w3[1] << 16) + (w3[2] << 8) + w3[3];
        endKey[0] = startKey[0] ^ word3;
        for (int i = 1; i < 4; i++)
        {
            endKey[i] = endKey[i - 1] ^ startKey[i];
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 3; j >= 0; j--)
            {
                BYTE num = endKey[i] & (BYTE)255;
                RoundKey[4 * i + j] = num;
                endKey[i] >>= 8;
            }
        }
    }

    void SetState(BYTE* st)
    {
        for (int i = 0; i < 16; i++)
        {
            State[i] = st[i];
        }
    }

    void SetRoundKey(int num)
    {
        for (int i = 0; i < 16; i++)
        {
            RoundKey[i] = Keys[num][i];
        }
    }
public:
    AESEncryptor(BYTE* IK)
    {
        for (int i = 0; i < 16; i++)
        {
            StartKey[i] = IK[i];
        }
    }

    BYTE* EncryptionWord(BYTE* wrd)
    {
        SetState(wrd);
        for (int i = 0; i < 16; i++)
        {
            RoundKey[i] = StartKey[i];
        }
        for (int i = 0; i < 10; i++)
        {
            NextRoundKey();
            SubBytes();
            ShiftRows();
            MixColumns();
            AddRoundKey();
        }
        return State;
    }

    BYTE* DecryptionWord(BYTE* wrd)
    {
        SetState(wrd);
        for (int i = 0; i < 16; i++)
        {
            RoundKey[i] = StartKey[i];
        }
        for (int j = 0; j < 10; j++)
        {
            NextRoundKey();
            Keys[j] = new BYTE[16];
            for (int i = 0; i < 16; i++)
            {
                Keys[j][i] = RoundKey[i];
            }
        }
        for (int i = 9; i >= 0; i--)
        {
            SetRoundKey(i);
            AddRoundKey();
            InvMixColumns();
            InvShiftRows();
            InvSubBytes();
        }
        return State;
    }
};

BYTE* AESEncryption(BYTE* data, BYTE* key, UINT32 size)
{
    UINT32 addBlock = 0;
    if (size % 16 != 0)
    {
        addBlock = 16 - size % 16;
    }
    
    size = size + addBlock;
    BYTE* OpenText = new BYTE[size];

    for (int i = 0; i < size - addBlock; i++)
    {
        OpenText[i] = data[i];
    }
    for (int i = size - addBlock; i < size; i++)
    {
        OpenText[i] = (BYTE)0;
    }
    
    BYTE* ClosedText = new BYTE[size];
    AESEncryptor Encr = AESEncryptor(key);
    UINT32 numBlocks = size / 16;

    for (int n = 0; n < numBlocks; n++)
    {
        BYTE* OpenWord = new BYTE[16];
        BYTE* ClosedWord;
        for (int i = 0; i < 16; i++)
        {
            OpenWord[i] = OpenText[16 * n + i];
        }
        ClosedWord = Encr.EncryptionWord(OpenWord);
        for (int i = 0; i < 16; i++)
        {
            ClosedText[16 * n + i] = ClosedWord[i];
        }
    }

    return ClosedText;
}

BYTE* AESDecryption(BYTE* data, BYTE* key, UINT32& size)
{
    UINT32 numBlocks = size / 16;
    BYTE* ClosedText = new BYTE[size];
    BYTE* OpenText = new BYTE[size];
    AESEncryptor Encr = AESEncryptor(key);
    for (int i = 0; i < size; i++)
    {
        ClosedText[i] = data[i];
    }
    for (int n = 0; n < numBlocks; n++)
    {
        BYTE* ClosedWord = new BYTE[16];
        BYTE* OpenWord;
        for (int i = 0; i < 16; i++)
        {
            ClosedWord[i] = ClosedText[16 * n + i];
        }
        OpenWord = Encr.DecryptionWord(ClosedWord);
        for (int i = 0; i < 16; i++)
        {
            OpenText[16 * n + i] = OpenWord[i];
        }
    }

    return OpenText;
}