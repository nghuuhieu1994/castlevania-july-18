using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ToolTileMap
{
    public struct Tile
    {
        
        public static int TILE_Y = 64;
        public static int TILE_X = 64;
        public Color[,] m_Bitmap;
        public int ID;
    }
    public struct Map
    {
        public int X;
        public int Y;
        public Bitmap m_Map;
    }
}
