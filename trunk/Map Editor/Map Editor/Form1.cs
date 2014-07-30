using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Map_Editor
{
    public partial class MainForm : Form
    {
        Image Main_Image;
        PictureBox z = new PictureBox();
        Cursor myCur;
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
            
            //pictureBox1.Controls.Add((Control)z);
            z.Image = Image.FromFile("2.png");
            z.Size = new Size(32, 32);
            Bitmap cs = new Bitmap("2.png");
            myCur = CursorTest.CreateCursor(cs, 0, 0);
            
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
            //Point mouse_location = pictureBox1.PointToClient(Control.MousePosition);
            Cursor.Current = myCur;
            //z.Location = mouse_location;
            //z.BringToFront();
            //pictureBox1.Controls.Add(z);
            
            //pictureBox1.Controls.SetChildIndex(z, 1);
            
            //this.Controls.Add(z);
            //Image temp = (Image)Main_Image.Clone();

            //ColorMatrix matrix = new ColorMatrix(); 
            //matrix.Matrix33 = 0.7f;

            
            //ImageAttributes attributes = new ImageAttributes();

            
            //attributes.SetColorMatrix(matrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);    

            //Graphics g = Graphics.FromImage(temp);
            //Image icon = Image.FromFile("2.png"); 
            
            ////g.DrawImage(icon, mouse_location,
            //g.DrawImage(icon, new Rectangle(mouse_location, new Size(icon.Width, icon.Height)), 0, 0, icon.Width, icon.Height, GraphicsUnit.Pixel, attributes);

            //pictureBox1.Image = temp;
            //temp = null;
            //Console.WriteLine(_output);
        }

       
    }
      public struct IconInfo
  {
    public bool fIcon;
    public int xHotspot;
    public int yHotspot;
    public IntPtr hbmMask;
    public IntPtr hbmColor;
  }

      public class CursorTest : Form
      {
          public CursorTest()
          {
              this.Text = "Cursor Test";

              Bitmap bitmap = new Bitmap(140, 25);
              Graphics g = Graphics.FromImage(bitmap);
              using (Font f = new Font(FontFamily.GenericSansSerif, 10))
                  g.DrawString("{ } Switch On The Code", f, Brushes.Green, 0, 0);

              this.Cursor = CreateCursor(bitmap, 3, 3);

              bitmap.Dispose();
          }

          [DllImport("user32.dll")]
          public static extern IntPtr CreateIconIndirect(ref IconInfo icon);
          [DllImport("user32.dll")]
          [return: MarshalAs(UnmanagedType.Bool)]
          public static extern bool GetIconInfo(IntPtr hIcon, ref IconInfo pIconInfo);

          public static Cursor CreateCursor(Bitmap bmp, int xHotSpot, int yHotSpot)
          {
              IntPtr ptr = bmp.GetHicon();
              IconInfo tmp = new IconInfo();
              GetIconInfo(ptr, ref tmp);
              tmp.xHotspot = xHotSpot;
              tmp.yHotspot = yHotSpot;
              tmp.fIcon = false;
              ptr = CreateIconIndirect(ref tmp);
              return new Cursor(ptr);
          }
      }
}
