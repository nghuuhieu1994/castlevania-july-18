using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
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

            _newButton.BackgroundImage = new Bitmap("2.png");

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
            g.DrawImage(Image.FromFile("2.png"), mouse_location);
            pictureBox1.Image = Main_Image;
            //img.Save("background1.png");
            Console.WriteLine(_output);
        }
        
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
            
            Image temp = (Image)Main_Image.Clone();

            ColorMatrix matrix = new ColorMatrix(); 
            matrix.Matrix33 = 0.7f;

            
            ImageAttributes attributes = new ImageAttributes();

            
            attributes.SetColorMatrix(matrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);    

            Graphics g = Graphics.FromImage(temp);
            Image icon = Image.FromFile("2.png"); 
            //g.DrawImage(icon, mouse_location,
            g.DrawImage(icon, new Rectangle(mouse_location, new Size(icon.Width, icon.Height)), 0, 0, icon.Width, icon.Height, GraphicsUnit.Pixel, attributes);

            pictureBox1.Image = temp;
            temp = null;
            //Console.WriteLine(_output);
        }

       
    }
}
