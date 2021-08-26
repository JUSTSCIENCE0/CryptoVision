using System;
using System.IO;
using System.Numerics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CryptoVisionGUI
{
    public partial class Form1 : Form
    {
        private ulong Ek;
        private ulong Dk;
        private ulong Nk;
        private byte[] AESKey;
        private byte[] AESClosedKey;
        private byte[] EmTextOpen;
        
        [DllImport("CGates.dll")]
        private static extern void PushEncryptEmbedData(byte[] Text, byte[] Key, UInt32 size);

        [DllImport("CGates.dll")]
        private static extern void ConfigEmbedData(byte[] EncrKey);

        [DllImport("CGates.dll")]
        private static extern void LoadFrames(byte[] path, UInt32 pathLen, UInt32 frames);

        [DllImport("CGates.dll")]
        private static extern void GenSound(UInt32 type, UInt32 freq, UInt32 count);

        [DllImport("CGates.dll")]
        private static extern void LoadSound(byte[] path, UInt32 pathLen, UInt32 count);

        [DllImport("CGates.dll")]
        private static extern void SaveAvi(byte[] path, UInt32 pathLen);

        [DllImport("CGates.dll")]
        private static extern void LoadAviFile(byte[] path, UInt32 pathLen);

        [DllImport("CGates.dll")]
        private static extern byte PullKeyByte();

        [DllImport("CGates.dll")]
        private static extern void DecryptText(byte[] Key);

        [DllImport("CGates.dll")]
        private static extern UInt32 PullTextSize();

        [DllImport("CGates.dll")]
        private static extern byte PullTextByte();

        [DllImport("CGates.dll")]
        private static extern uint forTest();

        public Form1()
        {
            InitializeComponent();
        }

        private void GenerateAudio_CheckedChanged(object sender, EventArgs e)
        {
            if (GenerateAudio.Checked)
            {
                LoadAudioFile.Enabled = false;
                AudioPath.Enabled = false;
                GenerationSettings.Enabled = true;
            }
            else
            {
                LoadAudioFile.Enabled = true;
                AudioPath.Enabled = true;
                GenerationSettings.Enabled = false;
            }
        }

        private byte[] Generate16Bytes()
        {
            byte[] data = new byte[16];
            Random rnd = new Random();
            rnd.NextBytes(data);
            return data;
        }

        private UInt32[] BytesToInts(byte[] data)
        {
            UInt32[] nums = new uint[4];
            for (int i=0; i<4; i++)
            {
                nums[i] = BitConverter.ToUInt32(data, 4 * i);
            }
            return nums;
        }

        private byte[] StringToBytes(string text) 
        {
            byte[] res = new byte[text.Length * 2];
            for (int i=0; i<text.Length; i++)
            {
                byte[] tmp = BitConverter.GetBytes(text[i]);
                res[2 * i] = tmp[0];
                res[2 * i + 1] = tmp[1];
            }
            return res;
        }

        private byte[] Int64ToBytes(UInt64[] data)
        {
            byte[] res = new byte[32];
            for (int i=0; i<4; i++)
            {
                byte[] tmp = BitConverter.GetBytes(data[i]);
                for (int j=0; j<8; j++)
                {
                    res[8 * i + j] = tmp[j];
                }
            }
            return res;
        }
        private UInt64 RSAEncryption(UInt32 word)
        {
            return (UInt64)BigInteger.ModPow(word, Ek, Nk);
        }

        private UInt64 RSADecryption(UInt64 word)
        {
            return (UInt64)BigInteger.ModPow(word, Dk, Nk);
        }

        private string ConvertFormat(string Path)
        {
            string res = Path;
            res = res.Replace((char)92, '/');
            return res;
        }

        private byte[] UnicodeToUTF8(string Path)
        {
            Encoding utf8 = Encoding.UTF8;
            Encoding unicode = Encoding.Unicode;
            byte[] unicodeBytes = unicode.GetBytes(Path);
            byte[] res = Encoding.Convert(unicode, utf8, unicodeBytes);

            return res;
        }

        private void DoneVideo_Click(object sender, EventArgs e)
        {

            string EPath = "../keys/friends/E_" + IDAddress.Text;
            string NPath = "../keys/friends/N_" + IDAddress.Text;
            BinaryReader rd = new BinaryReader(File.Open(EPath, FileMode.Open));
            Ek = rd.ReadUInt64();
            rd.Close();
            rd = new BinaryReader(File.Open(NPath, FileMode.Open));
            Nk = rd.ReadUInt64();
            rd.Close();

            AESKey = Generate16Bytes();

            UInt32[] AESWords = BytesToInts(AESKey);
            UInt64[] ClosedAESKey = new UInt64[4];
            for (int i=0; i<4; i++)
            {
                ClosedAESKey[i] = RSAEncryption(AESWords[i]);
            }
            AESClosedKey = Int64ToBytes(ClosedAESKey);

            EmTextOpen = StringToBytes(EmbedText.Text);

            PushEncryptEmbedData(EmTextOpen, AESKey, (UInt32)EmTextOpen.Length);
            ConfigEmbedData(AESClosedKey);

            LoadFrames(UnicodeToUTF8(RGBdataPath.Text), (UInt32)RGBdataPath.Text.Length, (UInt32)numFrames.Value);

            UInt32 cnt = (UInt32)numFrames.Value;
            double perc = ((double)cnt) / 25;
            cnt = (UInt32)(44100 * perc);

            if (GenerateAudio.Checked)
            {
                UInt32 tp=0;
                if (SoundType.Text == "Noise") tp = 5;
                GenSound(tp, (UInt32)Freqwency.Value, cnt);
            }
            else
            {
                LoadSound(UnicodeToUTF8(AudioPath.Text), (UInt32)(AudioPath.Text.Length), cnt);
            }

            string aviPath="";
            SaveFileDialog aviFile = new SaveFileDialog();
            aviFile.Filter = "Video files(*.avi)|*.avi|All files(*.*)|*.*";
            aviFile.Title = "Сохранить видео";
            DialogResult result = aviFile.ShowDialog();
            if (result == DialogResult.OK)
            {
                aviPath = ConvertFormat(aviFile.FileName);
            }

            SaveAvi(UnicodeToUTF8(aviPath), (UInt32)(aviPath.Length));
        }

        private void SetRGBData_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog openDialog = new FolderBrowserDialog();
            openDialog.Description = "Выберите папку с кадрами";
            openDialog.ShowNewFolderButton = false;
            DialogResult result = openDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                RGBdataPath.Text = ConvertFormat(openDialog.SelectedPath + "/");
            }
        }

        private void LoadAudioFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog wavFile = new OpenFileDialog();
            wavFile.Filter = "Audio files(*.wav)|*.wav|All files(*.*)|*.*";
            wavFile.Title = "Выберите аудио файл";
            DialogResult result = wavFile.ShowDialog();
            if (result == DialogResult.OK)
            {
                AudioPath.Text = ConvertFormat(wavFile.FileName);
            }
        }

        private byte[] GetOpenKey(UInt64 Part1, UInt64 Part2, UInt64 Part3, UInt64 Part4)
        {
            byte[] res = new byte[16];

            byte[] tmp = BitConverter.GetBytes(Part1);
            for (int i=0; i<4; i++)
            {
                res[i] = tmp[i];
            }
            tmp = BitConverter.GetBytes(Part2);
            for (int i=4; i<8; i++)
            {
                res[i] = tmp[i-4];
            }
            tmp = BitConverter.GetBytes(Part3);
            for (int i = 8; i < 12; i++)
            {
                res[i] = tmp[i-8];
            }
            tmp = BitConverter.GetBytes(Part4);
            for (int i = 12; i < 16; i++)
            {
                res[i] = tmp[i - 12];
            }

            return res;
        }

        private string ConvertBytes(byte[] data)
        {
            string res = "";
            for (int i=0; i<(data.Length / 2); i++)
            {
                res += BitConverter.ToChar(data, i*2);
            }
            return res;
        }

        private void LoadAvi_Click(object sender, EventArgs e)
        {
            string DPath = "../keys/localhost/D_local";
            string NPath = "../keys/localhost/N_local";
            BinaryReader rd = new BinaryReader(File.Open(DPath, FileMode.Open));
            Dk = rd.ReadUInt64();
            rd.Close();
            rd = new BinaryReader(File.Open(NPath, FileMode.Open));
            Nk = rd.ReadUInt64();
            rd.Close();

            OpenFileDialog aviFile = new OpenFileDialog();
            aviFile.Filter = "Audio files(*.avi)|*.avi|All files(*.*)|*.*";
            aviFile.Title = "Выберите аудио файл";
            DialogResult result = aviFile.ShowDialog();
            if (result == DialogResult.OK)
            {
                AviPathText.Text = ConvertFormat(aviFile.FileName);
            }

            LoadAviFile(UnicodeToUTF8(AviPathText.Text), (UInt32)(AviPathText.Text.Length));

            AESClosedKey = new byte[32];
            for (int i=0; i<32; i++)
            {
                AESClosedKey[i] = PullKeyByte();
            }

            UInt64 Part1 = BitConverter.ToUInt64(AESClosedKey, 0);
            UInt64 Part2 = BitConverter.ToUInt64(AESClosedKey, 8);
            UInt64 Part3 = BitConverter.ToUInt64(AESClosedKey, 16);
            UInt64 Part4 = BitConverter.ToUInt64(AESClosedKey, 24);

            UInt64 Part1Open = RSADecryption(Part1);
            UInt64 Part2Open = RSADecryption(Part2);
            UInt64 Part3Open = RSADecryption(Part3);
            UInt64 Part4Open = RSADecryption(Part4);

            AESKey = GetOpenKey(Part1Open, Part2Open, Part3Open, Part4Open);

            DecryptText(AESKey);

            UInt32 TxtSz = PullTextSize();
            EmTextOpen = new byte[TxtSz];
            for (UInt32 i=0; i<TxtSz; i++)
            {
                EmTextOpen[i] = PullTextByte();
            }

            GettingText.Text = ConvertBytes(EmTextOpen);
        }
    }
}
