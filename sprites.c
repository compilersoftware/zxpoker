/*---------------------------------------------------------------------
 Sprites, created with SevenuP (http://www.speccy.org/metalbrain).
 
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
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

---------------------------------------------------------------------*/

/* C source file created by SevenuP v1.12                                */
/* SevenuP (C) Copyright 2002-2004 by Jaime Tejedor G¢mez, aka Metalbrain*/

/*
GRAPHIC DATA:
Pixel Size:      (  8, 112)
Char Size:       (  1,  14)
Sort Priorities: Char line, Y char
Attributes:      No attributes
Mask:            No
*/

/* (Don't forget to rename the Sprite before using it with more code) */

unsigned char Numbers[112] = {
  0, 56, 68, 76, 84,100, 68, 56,
  0, 48, 16, 16, 16, 16, 16, 56,
  0, 56,  4,  4,  8, 16, 32, 60,
  0, 56,  4,  4, 28,  4,  4, 56,
  0, 36, 36, 36, 60,  4,  4,  4,
  0, 60, 32, 32, 24,  4,  4, 56,
  0, 24, 32, 32, 56, 36, 36, 24,
  0, 60,  4,  4,  8,  8, 16, 16,
  0, 24, 36, 36, 24, 36, 36, 24,
  0, 24, 36, 36, 28,  4,  4, 56,
  0, 76,210, 86, 86, 90, 82,236,
  0, 28,  8,  8,  8,  8, 72, 56,
  0, 56, 68, 68, 84, 76, 69, 58,
  0, 36, 36, 40, 48, 40, 36, 36
};

unsigned char Corners[64] = {
 63, 64,128,128,128,128,128,128,
255,  0,  0,  0,  0,  0,  0,  0,
252,  2,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  2,252,
  0,  0,  0,  0,  0,  0,  0,255,
128,128,128,128,128,128, 64, 63,
128,128,128,128,128,128,128,128
};

unsigned char Types[32] = {
    16, 56,124,254,124, 56, 16,  0,
    16, 56,124,254,124, 16,124,  0,
    68,238,254,254,124, 56, 16,  0,
    60, 60,255,255,255, 60, 24, 60
};

unsigned char Discard[8] = {
   129, 66, 36, 24, 24, 36, 66,129 };

unsigned char MoneySymbols[32] = {
 32,120,160,163,112, 40, 43,240,
  0,112, 73, 74,115, 74, 74,113,
 16, 56,144, 83,208, 16, 83,136,
  0, 14, 17, 28, 16, 28, 17, 14
};

unsigned char Ace[8] = {
  8, 20, 34, 62, 34, 34, 34,  0};
