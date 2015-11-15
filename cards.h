/*-----------------------------------------------------------------
 Cards Library v1.0  -  18-03-2003  -  Header file
 Santiago Romero - sromero@escomposlinux.org

 Functions for cards/deck manipulation (Init, Shuffle, Push...).

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
-------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _CARDS_H_
#define _CARDS_H_

#define MAX_CARDS 64
#define NUM_CARDS 52


//--- Card definition -------------------------------------------------
typedef struct
{
  signed char type;
  signed char value;
  signed char extra;
} Card;


//--- Deck of cards ---------------------------------------------------
typedef struct
{
  signed char top;
  Card cards[MAX_CARDS];
} Deck;


//--- Function declarations -------------------------------------------
void DeckInit( Deck *deck );
void DeckFillSpanish( Deck *deck );
void DeckFillPoker( Deck *deck );
int  DeckEmpty( Deck *deck );
int  DeckCardsInDeck( Deck *deck );
int  DeckPushCard( Deck *deck, Card card );
int  DeckPopCard( Deck *deck, Card *card );
void DeckShuffle( Deck *deck, int howmany );
int  DeckGetCard( Deck *deck, Card *card, int which );
int  DeckSetCard( Deck *deck, Card *card, int which );
void DeckExchangeCards( Deck *deck, int c1, int c2 );
void CardShow( char v, char t, char which );
void CardErase( char v, char t, char which );
void DeckShow( Deck *deck, int which );
void DeckErase( Deck *deck, int which );
void DeckSortCards( Deck *deck );
   

//---------------------------------------------------------------------
#define DeckLastCard(deck) (DeckCardsInDeck((deck))-1)

#define TextDefault()       printf( "\x1B[m" )
#define TextHiRes()         printf( "%c2J",155 )
#define TextBold()          printf( "\x1B[1m" )
#define TextDim()           printf( "\x1B[2m" )
#define TextUnderline()     printf( "\x1B[4m" )
#define TextUnunderline()   printf( "\x1B[24m" )
#define TextReverse()       printf( "\x1B[7m" )
#define TextUnreverse()     printf( "\x1B[27m" )
#define TextFG_Black()      printf( "\x1B[%um", 30 )
#define TextFG_Red()        printf( "\x1B[%um", 31 )
#define TextFG_Green()      printf( "\x1B[%um", 32 )
#define TextFG_Yellow()     printf( "\x1B[%um", 33 )
#define TextFG_Blue()       printf( "\x1B[%um", 34 )
#define TextFG_Magenta()    printf( "\x1B[%um", 35 )
#define TextFG_Cyan()       printf( "\x1B[%um", 36 )
#define TextFG_White()      printf( "\x1B[%um", 37 )
#define TextBG_Black()      printf( "\x1B[%um", 40 )
#define TextBG_Red()        printf( "\x1B[%um", 41 )
#define TextBG_Green()      printf( "\x1B[%um", 42 )
#define TextBG_Yellow()     printf( "\x1B[%um", 43 )
#define TextBG_Blue()       printf( "\x1B[%um", 44 )
#define TextBG_Magenta()    printf( "\x1B[%um", 45 )
#define TextBG_Cyan()       printf( "\x1B[%um", 46 )
#define TextBG_White()      printf( "\x1B[%um", 47 )
#define TextColor(x)        printf( "\x1B[%um", (x) )
#define TextGotoXY(x,y)     printf( "\x1B[%u;%uH",(y),(x))
#define TextClearScreen()   printf( "\x1B[2J" )

#endif


