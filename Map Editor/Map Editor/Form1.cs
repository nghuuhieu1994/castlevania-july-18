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
            this.SetStyle(ControlStyles.DoubleBuffer | ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint, true);
            Bitmap map = new Bitmap("background2.png");
            GlobalFunction.ClearAlphaColor(map);
            Main_Image = new Bitmap("background2.png");
            GlobalFunction.ClearAlphaColor(Main_Image);
            //panel1.AutoScroll = true;
            //panel1.HorizontalScroll.Enabled = false;
            this.pictureBox1.SizeMode = PictureBoxSizeMode.AutoSize;
            pictureBox1.Image = map;

            z.Image = Image.FromFile("2.png");
            z.Size = new Size(32, 32);
            Bitmap amc = new Bitmap("mousecursor.png");
            GlobalFunction.ClearAlphaColor(amc);

            myCur = GlobalFunction.CreateCursor(amc, 0, 0);
            InitializeTabPage();
            ScrollPanel smart = new ScrollPanel();
            this.Controls.Add(smart);
            smart.Size = new Size(750, 400);
            smart.Location = new Point(20, 150);
            smart.Controls.Add(pictureBox1);
            smart.AutoScroll = true;
            pictureBox1.Location = new Point(0, 0);
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
            Bitmap cs = GlobalFunction.SetImageOpacity(x, 0.8f);
            currentCursor = x;
            myCur = GlobalFunction.CreateCursor(cs, 0, 0);
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            // if (myCur.Tag == null)
            // {
                // MessageBox.Show("Error!");
                // return;
            // }
            Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
            string _output = "X: " + mouse_location.X + " Y: " + mouse_location.Y;
            
            PictureBox temp = new PictureBox();
            temp.Location = mouse_location;
            temp.Image = currentCursor;
            temp.Size = currentCursor.Size;
            temp.MouseClick += temp_MouseClick;
            temp.MouseMove +=temp_MouseMove;
            temp.MouseHover += temp_MouseMove;
            temp.MouseLeave += temp_MouseMove;
            temp.MouseDown += temp_MouseMove;
            temp.BackColor = Color.Transparent;
            
            pictureBox1.Controls.Add(temp);
            Console.WriteLine(pictureBox1.Controls.Count.ToString());
        }
        
        private void temp_MouseMove(object _obj, EventArgs e)
        {
            
        }

        private void temp_MouseClick(object _obj, EventArgs e)
        {
            pictureBox1.Controls.Remove(_obj as PictureBox);
            
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
            }
            if (e.KeyChar == 'a')
            {
                Cursor.Position = new Point(Cursor.Position.X - 1, Cursor.Position.Y);
            }
            if (e.KeyChar == 's')
            {
                Cursor.Position = new Point(Cursor.Position.X, Cursor.Position.Y + 1);
            }
            if (e.KeyChar == 'd')
            {
                Cursor.Position = new Point(Cursor.Position.X + 1, Cursor.Position.Y);
            }
            if (e.KeyChar == 'c')
            {
                Cursor.Position = new Point(Cursor.Position.X + currentCursor.Width, Cursor.Position.Y);
            }
            if (e.KeyChar == 'x')
            {
                Cursor.Position = new Point(Cursor.Position.X - currentCursor.Width, Cursor.Position.Y);
            }
            if (e.KeyChar == 'z')
            {
                Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
                string _output = "X: " + mouse_location.X + " Y: " + mouse_location.Y;

                // if (myCur.Tag == null)
                // {
                    // MessageBox.Show("Error!");
                    // return;
                // }

                PictureBox temp = new PictureBox();
                temp.Location = mouse_location;
                temp.Image = currentCursor;
                temp.Size = currentCursor.Size;
                temp.MouseClick += temp_MouseClick;
                temp.BackColor = Color.Transparent;
                pictureBox1.Controls.Add(temp);
            }
        }
    }
}
