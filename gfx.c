/*---------------------------------------------------------------------

 Graphical functions.
 
 Feel free to improve this game, solve bugs, and add whatever
 you want. It's free software, you can do it without asking me,
 but it would be very nice if you maintain my name in the
 credits.

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 /long with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

---------------------------------------------------------------------*/



/*
Speccy colors:

0 black
1 blue
2 red
3 purple, or magenta
4 green
5 pale blue, or cyan
6 yellow
7 white
*/


int scan_convert[192] = {
0,8,16,24,32,40,48,56,1,9,17,25,33,41,49,57,2,10,18,26,34,42,50,58,
3,11,19,27,35,43,51,59,4,12,20,28,36,44,52,60,5,13,21,29,37,45,53,61,
6,14,22,30,38,46,54,62,7,15,23,31,39,47,55,63,
 64,72,80,88,96,104,112,120,65,73,81,89,97,105,113,121,66,74,82,90,98,106,114,122,
67,75,83,91,99,107,115,123,68,76,84,92,100,108,116,124,69,77,85,93,101,109,117,125,
70,78,86,94,102,110,118,126,71,79,87,95,103,111,119,127,128,136,144,152,160,168,176,184,
 129,137,145,153,161,169,177,185,130,138,146,154,162,170,178,186,131,139,147,155,163,171,179,187,
132,140,148,156,164,172,180,188,133,141,149,157,165,173,181,189,134,142,150,158,166,174,182,190,
135,143,151,159,167,175,183,191
};


#define GetRowAddress(row) (scan_convert[(row)])
#define SCREENSIZE 6912
unsigned char *VRAM;
unsigned char *Attributes;

void InitGFX( void );
void ClearScreen( int value, int color );
void ClearScreenAttr( int x, int y, int width, int height, int value );
void ClearScreenData( int x, int y, int width, int height, int value );
void DrawChar( char number, char x, char y, char *spr, char attr );

//---------------------------------------------------------------------
// Init GFX stuff...
//---------------------------------------------------------------------
void InitGFX( void )
{
  int x;

  VRAM = 0x4000;
  Attributes = 0x4000 + (32*192);

  for(x=0; x<192; x++)
    scan_convert[x] = (scan_convert[x] * 32) + (int) VRAM;
}



//---------------------------------------------------------------------
// Clear the entire screen with a given value/attr
//---------------------------------------------------------------------
void ClearScreen( int value, int color )
{
  memset( (unsigned char) Attributes, color, 768 );
  memset( (unsigned char) VRAM, value, 32*192 );
}


//---------------------------------------------------------------------
// Clear Memory Screen Attribute Block (x,y,w,h in 8x8-size blocks)
//---------------------------------------------------------------------
void ClearScreenAttr( int x, int y, int width, int height, int value )
{
  int i, j;
  unsigned char *memoffset;

  memoffset = (unsigned char *) (Attributes + (y<<5) + x) ;
  for(j=0; j<height; j++)
  {
     for(i=0; i<width; i++ )
       *memoffset++ = value;
     memoffset += (32-width);
  }

}


//---------------------------------------------------------------------
// Clear Memory Screen Block (x,y,w,h in 8x8-size blocks)
//---------------------------------------------------------------------
void ClearScreenData( int x, int y, int width, int height, int value )
{
  int i, newy;
  unsigned char *memoffset;

  newy = y<<3;

  for(i=0; i<(height<<3); i++)
  {
     memoffset = (unsigned char *) scan_convert[newy+i]+x;
     memset( memoffset, value, width );
  }

}



//---------------------------------------------------------------------
// Draw a single 8x8 sprite in 8x8 block screen coordinates
//---------------------------------------------------------------------
void DrawChar( char number, char x, char y, char *spr, char attr )
{
  char i;
  unsigned char *memoffset;
  char tmp;
  int newy;

  tmp = (number<<3);
  newy = (y<<3);

  // Dibujar los 8 bytes del caracter
  for( i=0; i<8; i++)
  {
     memoffset = (unsigned char *) scan_convert[newy+i]+x;
     *memoffset = spr[tmp+i];
  }

  if( attr != -1 )
  {
     memoffset = (unsigned char *) Attributes + (y<<5) + x ;
     *memoffset = attr;
  }
  
}



