namespace CryptoVisionGUI
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.SetRGBData = new System.Windows.Forms.Button();
            this.RGBdataPath = new System.Windows.Forms.Label();
            this.GenerateAudio = new System.Windows.Forms.RadioButton();
            this.LoadAudio = new System.Windows.Forms.RadioButton();
            this.AudioPath = new System.Windows.Forms.Label();
            this.LoadAudioFile = new System.Windows.Forms.Button();
            this.GenerationSettings = new System.Windows.Forms.GroupBox();
            this.Freqwency = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.SoundType = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.numFrames = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.IDAddress = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.DoneVideo = new System.Windows.Forms.Button();
            this.EmbedText = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.GettingText = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.LoadAvi = new System.Windows.Forms.Button();
            this.AviPathText = new System.Windows.Forms.Label();
            this.GenerationSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Freqwency)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numFrames)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // SetRGBData
            // 
            this.SetRGBData.Location = new System.Drawing.Point(6, 23);
            this.SetRGBData.Name = "SetRGBData";
            this.SetRGBData.Size = new System.Drawing.Size(131, 35);
            this.SetRGBData.TabIndex = 0;
            this.SetRGBData.Text = "Выбрать папку кадров";
            this.SetRGBData.UseVisualStyleBackColor = true;
            this.SetRGBData.Click += new System.EventHandler(this.SetRGBData_Click);
            // 
            // RGBdataPath
            // 
            this.RGBdataPath.AutoSize = true;
            this.RGBdataPath.Location = new System.Drawing.Point(143, 34);
            this.RGBdataPath.Name = "RGBdataPath";
            this.RGBdataPath.Size = new System.Drawing.Size(121, 13);
            this.RGBdataPath.TabIndex = 1;
            this.RGBdataPath.Text = "C:/RowDataCubeColor/";
            // 
            // GenerateAudio
            // 
            this.GenerateAudio.AutoSize = true;
            this.GenerateAudio.Checked = true;
            this.GenerateAudio.Location = new System.Drawing.Point(6, 64);
            this.GenerateAudio.Name = "GenerateAudio";
            this.GenerateAudio.Size = new System.Drawing.Size(128, 17);
            this.GenerateAudio.TabIndex = 2;
            this.GenerateAudio.TabStop = true;
            this.GenerateAudio.Text = "Генерировать аудио";
            this.GenerateAudio.UseVisualStyleBackColor = true;
            this.GenerateAudio.CheckedChanged += new System.EventHandler(this.GenerateAudio_CheckedChanged);
            // 
            // LoadAudio
            // 
            this.LoadAudio.AutoSize = true;
            this.LoadAudio.Location = new System.Drawing.Point(6, 87);
            this.LoadAudio.Name = "LoadAudio";
            this.LoadAudio.Size = new System.Drawing.Size(109, 17);
            this.LoadAudio.TabIndex = 3;
            this.LoadAudio.Text = "Загрузить аудио";
            this.LoadAudio.UseVisualStyleBackColor = true;
            // 
            // AudioPath
            // 
            this.AudioPath.AutoSize = true;
            this.AudioPath.Enabled = false;
            this.AudioPath.Location = new System.Drawing.Point(143, 121);
            this.AudioPath.Name = "AudioPath";
            this.AudioPath.Size = new System.Drawing.Size(35, 13);
            this.AudioPath.TabIndex = 5;
            this.AudioPath.Text = "NULL";
            // 
            // LoadAudioFile
            // 
            this.LoadAudioFile.Enabled = false;
            this.LoadAudioFile.Location = new System.Drawing.Point(6, 110);
            this.LoadAudioFile.Name = "LoadAudioFile";
            this.LoadAudioFile.Size = new System.Drawing.Size(131, 35);
            this.LoadAudioFile.TabIndex = 4;
            this.LoadAudioFile.Text = "Выбрать аудио";
            this.LoadAudioFile.UseVisualStyleBackColor = true;
            this.LoadAudioFile.Click += new System.EventHandler(this.LoadAudioFile_Click);
            // 
            // GenerationSettings
            // 
            this.GenerationSettings.Controls.Add(this.Freqwency);
            this.GenerationSettings.Controls.Add(this.label2);
            this.GenerationSettings.Controls.Add(this.label1);
            this.GenerationSettings.Controls.Add(this.SoundType);
            this.GenerationSettings.Location = new System.Drawing.Point(6, 151);
            this.GenerationSettings.Name = "GenerationSettings";
            this.GenerationSettings.Size = new System.Drawing.Size(186, 117);
            this.GenerationSettings.TabIndex = 6;
            this.GenerationSettings.TabStop = false;
            this.GenerationSettings.Text = "Параметры генерации";
            // 
            // Freqwency
            // 
            this.Freqwency.Location = new System.Drawing.Point(6, 91);
            this.Freqwency.Maximum = new decimal(new int[] {
            20000,
            0,
            0,
            0});
            this.Freqwency.Name = "Freqwency";
            this.Freqwency.Size = new System.Drawing.Size(166, 20);
            this.Freqwency.TabIndex = 3;
            this.Freqwency.Value = new decimal(new int[] {
            400,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 68);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Частота";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Тип звука";
            // 
            // SoundType
            // 
            this.SoundType.FormattingEnabled = true;
            this.SoundType.Items.AddRange(new object[] {
            "Wave",
            "Noise"});
            this.SoundType.Location = new System.Drawing.Point(6, 40);
            this.SoundType.Name = "SoundType";
            this.SoundType.Size = new System.Drawing.Size(166, 21);
            this.SoundType.TabIndex = 0;
            this.SoundType.Text = "Wave";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.numFrames);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.IDAddress);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.DoneVideo);
            this.groupBox2.Controls.Add(this.EmbedText);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.SetRGBData);
            this.groupBox2.Controls.Add(this.GenerationSettings);
            this.groupBox2.Controls.Add(this.RGBdataPath);
            this.groupBox2.Controls.Add(this.AudioPath);
            this.groupBox2.Controls.Add(this.GenerateAudio);
            this.groupBox2.Controls.Add(this.LoadAudioFile);
            this.groupBox2.Controls.Add(this.LoadAudio);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(334, 438);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Генерация файла";
            // 
            // numFrames
            // 
            this.numFrames.Location = new System.Drawing.Point(240, 80);
            this.numFrames.Maximum = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.numFrames.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numFrames.Name = "numFrames";
            this.numFrames.Size = new System.Drawing.Size(63, 20);
            this.numFrames.TabIndex = 5;
            this.numFrames.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(223, 64);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(105, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Количество кадров";
            // 
            // IDAddress
            // 
            this.IDAddress.Location = new System.Drawing.Point(12, 407);
            this.IDAddress.Name = "IDAddress";
            this.IDAddress.Size = new System.Drawing.Size(125, 20);
            this.IDAddress.TabIndex = 11;
            this.IDAddress.Text = "UYA";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 391);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(68, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "ID адресата";
            // 
            // DoneVideo
            // 
            this.DoneVideo.Location = new System.Drawing.Point(184, 391);
            this.DoneVideo.Name = "DoneVideo";
            this.DoneVideo.Size = new System.Drawing.Size(131, 35);
            this.DoneVideo.TabIndex = 9;
            this.DoneVideo.Text = "Сгенерировать";
            this.DoneVideo.UseVisualStyleBackColor = true;
            this.DoneVideo.Click += new System.EventHandler(this.DoneVideo_Click);
            // 
            // EmbedText
            // 
            this.EmbedText.Location = new System.Drawing.Point(12, 292);
            this.EmbedText.Multiline = true;
            this.EmbedText.Name = "EmbedText";
            this.EmbedText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.EmbedText.Size = new System.Drawing.Size(303, 93);
            this.EmbedText.TabIndex = 8;
            this.EmbedText.Text = "secret";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 275);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(114, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Встраиваемый текст";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.GettingText);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.LoadAvi);
            this.groupBox1.Controls.Add(this.AviPathText);
            this.groupBox1.Location = new System.Drawing.Point(353, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(325, 437);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Извлечение из файла";
            // 
            // GettingText
            // 
            this.GettingText.Location = new System.Drawing.Point(6, 85);
            this.GettingText.Multiline = true;
            this.GettingText.Name = "GettingText";
            this.GettingText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.GettingText.Size = new System.Drawing.Size(303, 341);
            this.GettingText.TabIndex = 13;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 68);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(100, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "Встроенный текст";
            // 
            // LoadAvi
            // 
            this.LoadAvi.Location = new System.Drawing.Point(6, 22);
            this.LoadAvi.Name = "LoadAvi";
            this.LoadAvi.Size = new System.Drawing.Size(131, 35);
            this.LoadAvi.TabIndex = 12;
            this.LoadAvi.Text = "Выбрать файл";
            this.LoadAvi.UseVisualStyleBackColor = true;
            this.LoadAvi.Click += new System.EventHandler(this.LoadAvi_Click);
            // 
            // AviPathText
            // 
            this.AviPathText.AutoSize = true;
            this.AviPathText.Location = new System.Drawing.Point(143, 33);
            this.AviPathText.Name = "AviPathText";
            this.AviPathText.Size = new System.Drawing.Size(35, 13);
            this.AviPathText.TabIndex = 13;
            this.AviPathText.Text = "NULL";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(690, 458);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Name = "Form1";
            this.Text = "CryptoVision";
            this.GenerationSettings.ResumeLayout(false);
            this.GenerationSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Freqwency)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numFrames)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button SetRGBData;
        private System.Windows.Forms.Label RGBdataPath;
        private System.Windows.Forms.RadioButton GenerateAudio;
        private System.Windows.Forms.RadioButton LoadAudio;
        private System.Windows.Forms.Label AudioPath;
        private System.Windows.Forms.Button LoadAudioFile;
        private System.Windows.Forms.GroupBox GenerationSettings;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox SoundType;
        private System.Windows.Forms.NumericUpDown Freqwency;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox EmbedText;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button DoneVideo;
        private System.Windows.Forms.TextBox IDAddress;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox GettingText;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button LoadAvi;
        private System.Windows.Forms.Label AviPathText;
        private System.Windows.Forms.NumericUpDown numFrames;
        private System.Windows.Forms.Label label7;
    }
}

