namespace ToolTileMap
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pnSourcePic = new System.Windows.Forms.Panel();
            this.pbSourcePic = new System.Windows.Forms.PictureBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pnSourcePic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSourcePic)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pnSourcePic
            // 
            this.pnSourcePic.Controls.Add(this.pbSourcePic);
            this.pnSourcePic.Location = new System.Drawing.Point(13, 12);
            this.pnSourcePic.Name = "pnSourcePic";
            this.pnSourcePic.Size = new System.Drawing.Size(659, 209);
            this.pnSourcePic.TabIndex = 0;
            // 
            // pbSourcePic
            // 
            this.pbSourcePic.Location = new System.Drawing.Point(3, 3);
            this.pbSourcePic.Name = "pbSourcePic";
            this.pbSourcePic.Size = new System.Drawing.Size(653, 189);
            this.pbSourcePic.TabIndex = 0;
            this.pbSourcePic.TabStop = false;
            this.pbSourcePic.Click += new System.EventHandler(this.pbSourcePic_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Location = new System.Drawing.Point(13, 240);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(656, 68);
            this.panel1.TabIndex = 1;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(3, 3);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(650, 50);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 461);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.pnSourcePic);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Tool Tile Background";
            this.pnSourcePic.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pbSourcePic)).EndInit();
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnSourcePic;
        private System.Windows.Forms.PictureBox pbSourcePic;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pictureBox1;

    }
}

