using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Map_Editor
{
    public partial class MainForm : Form
    {
        Image Main_Image;
        public MainForm()
        {
            InitializeComponent();
            Bitmap map = new Bitmap("background1.png");
            Main_Image = new Bitmap("background1.png");
            panel1.AutoScroll = true;
            this.pictureBox1.SizeMode = PictureBoxSizeMode.AutoSize;
            pictureBox1.Image = map;
            Button _newButton = new Button();

            _newButton.BackgroundImage = new Bitmap("simon.png");

            _newButton.Size = new System.Drawing.Size(64, 64);
            _newButton.BackgroundImageLayout = ImageLayout.Zoom;
            _newButton.Name = "simon";
            //_newButton.Click += new System.EventHandler(this.Button_Click);
            flowLayoutPanel1.Controls.Add(_newButton);
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
            string _output = "X: " + mouse_location.X + " Y: " + mouse_location.Y;
            //Bitmap img = new Bitmap("background1.png");
            Graphics g = Graphics.FromImage(Main_Image);
            g.DrawImage(Image.FromFile("simon.png"), mouse_location);
            pictureBox1.Image = Main_Image;
            //img.Save("background1.png");
            Console.WriteLine(_output);
        }
        
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
            //string _output = "X: " + mouse_location.X + " Y: " + mouse_location.Y;
            //Bitmap temp = new Bitmap("background1.png");
            Image temp = (Image)Main_Image.Clone();
            
            Graphics g = Graphics.FromImage(temp);
            g.DrawImage(Image.FromFile("simon.png"), mouse_location);

            pictureBox1.Image = temp;
            temp = null;
            //Console.WriteLine(_output);
        }

       
    }
}
