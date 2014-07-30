using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Map_Editor
{
    public partial class MainForm : Form
    {
        Bitmap Main_Image;
        PictureBox z = new PictureBox();
        Cursor myCur;
        Bitmap currentCursor;
        public MainForm()
        {
            InitializeComponent();
            Bitmap map = new Bitmap("background1.png");
            GlobalFunction.ClearAlphaColor(map);
            Main_Image = new Bitmap("background1.png");
            GlobalFunction.ClearAlphaColor(Main_Image);
            panel1.AutoScroll = true;
            panel1.HorizontalScroll.Enabled = false;
            this.pictureBox1.SizeMode = PictureBoxSizeMode.AutoSize;
            pictureBox1.Image = map;
            
            
            //_newButton.BackgroundImage = new Bitmap("simon.png");
            
            
            //flowLayoutPanel1.Controls.Add(_newButton);
            
            //pictureBox1.Controls.Add((Control)z);
            z.Image = Image.FromFile("2.png");
            z.Size = new Size(32, 32);
            Bitmap amc = new Bitmap("mousecursor.png");
            GlobalFunction.ClearAlphaColor(amc);
            //tabPage1.Controls.Add(_newButton);
            //Bitmap cs = GlobalFunction.SetImageOpacity(amc, 0.7f);

            myCur = GlobalFunction.CreateCursor(amc, 0, 0);
            InitializeTabPage();
        }

        public void InitializeTabPage()
        {
            tabPage1.AutoScroll = true;
            tabPage2.AutoScroll = true;
            tabPage3.AutoScroll = true;
            tabPage4.AutoScroll = true;

            LoadTabPage(tabPage1, "simon");
            LoadTabPage(tabPage2, "enemy");
            LoadTabPage(tabPage3, "boss");
            LoadTabPage(tabPage4, "ground");
        }

        public void LoadTabPage(TabPage _TabPage, string _type)
        {
            string[] filePathsPNG = Directory.GetFiles(Directory.GetCurrentDirectory() + "\\image\\" + _type, "*.png", SearchOption.AllDirectories);

            for (int i = 0; i < filePathsPNG.Length; i++)
            {
                Bitmap _newButtonIcon = new Bitmap(filePathsPNG[i]);
                GlobalFunction.ClearAlphaColor(_newButtonIcon);

                Button _newButton = new Button();
                _newButton.Location = new Point(i * 50, 0);
                _newButton.BackgroundImage = _newButtonIcon;
                _newButton.Size = new System.Drawing.Size(50, 50);
                _newButton.BackgroundImageLayout = ImageLayout.Zoom;
                _newButton.Name = filePathsPNG[i];
                _newButton.Click += new EventHandler(this.Button_Click);
                _TabPage.Controls.Add(_newButton);
            }
        }

        

        public void Button_Click(object _obj, EventArgs e)
        {
            Button current = (Button)_obj;
            Bitmap x = new Bitmap(current.BackgroundImage);
            Bitmap cs = GlobalFunction.SetImageOpacity(x, 0.7f);
            currentCursor = x;
            myCur = GlobalFunction.CreateCursor(cs, 0, 0);
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
            string _output = "X: " + mouse_location.X + " Y: " + mouse_location.Y;
            Graphics g = Graphics.FromImage(Main_Image);
            g.DrawImage(currentCursor, mouse_location);
            pictureBox1.Image = Main_Image;
        }
        
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            Cursor.Current = myCur;
            label1.Text = pictureBox1.PointToClient(Control.MousePosition).ToString();
        }

        private void pictureBox1_MouseHover(object sender, EventArgs e)
        {
               
        }

        private void MainForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 'w')
            {
                Cursor.Position = new Point(Cursor.Position.X, Cursor.Position.Y - 1);
                //Control.MousePosition = new Point(Control.MousePosition.X, Control.MousePosition.Y - 1); 
            }
            if (e.KeyChar == 'a')
            {
                Cursor.Position = new Point(Cursor.Position.X - 1, Cursor.Position.Y);
                //Control.MousePosition = new Point(Control.MousePosition.X, Control.MousePosition.Y - 1); 
            }
            if (e.KeyChar == 's')
            {
                Cursor.Position = new Point(Cursor.Position.X, Cursor.Position.Y + 1);
                //Control.MousePosition = new Point(Control.MousePosition.X, Control.MousePosition.Y - 1); 
            }
            if (e.KeyChar == 'd')
            {
                Cursor.Position = new Point(Cursor.Position.X + 1, Cursor.Position.Y);
                //Control.MousePosition = new Point(Control.MousePosition.X, Control.MousePosition.Y - 1); 
            }
            if (e.KeyChar == 'c')
            {
                Cursor.Position = new Point(Cursor.Position.X + currentCursor.Width, Cursor.Position.Y);
                //Control.MousePosition = new Point(Control.MousePosition.X, Control.MousePosition.Y - 1); 
            }
            if (e.KeyChar == 'x')
            {
                Cursor.Position = new Point(Cursor.Position.X - currentCursor.Width, Cursor.Position.Y);
                //Control.MousePosition = new Point(Control.MousePosition.X, Control.MousePosition.Y - 1); 
            }
            if (e.KeyChar == 'z')
            {
                Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
                string _output = "X: " + mouse_location.X + " Y: " + mouse_location.Y;
                //Bitmap img = new Bitmap("background1.png");
                Graphics g = Graphics.FromImage(Main_Image);
                g.DrawImage(currentCursor, mouse_location);
                pictureBox1.Image = Main_Image;
            }
        }
    }
}
