/* -------------------------------------------------------------------
 Cards Library v1.0  -  18-03-2003  -  C file
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

---------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"


//---------------------------------------------------------------------
// Init the card deck by setting the top of the stack to -1
//---------------------------------------------------------------------
void DeckInit( Deck *deck )
{  deck->top = -1; }


//---------------------------------------------------------------------
// Fill a deck with spanish cards
//---------------------------------------------------------------------
void DeckFillSpanish( Deck *deck )
{
   
   Card tmpcard;
   int i, j;

   for( j=0; j<4; j++ )
      for( i=12; i>0; i-- )
      {
         tmpcard.type = j;
         tmpcard.value = i;
         tmpcard.extra = 0;
         DeckPushCard( deck, tmpcard );
      }

// while(!DeckEmpty(&baraja))          // Simple test of the library
// {
//    DeckPopCard( &baraja, &carta );
//    printf("El %d de %s (quedan %d cartas)\n", 
//          carta.value, palos[carta.type], DeckCardsInDeck(&baraja));
// }

}


//---------------------------------------------------------------------
// Fill a deck with poker cards
//---------------------------------------------------------------------
void DeckFillPoker( Deck *deck )
{
   
   Card tmpcard;
   int i, j;

   for( j=0; j<4; j++ )
      for( i=13; i>0; i-- )
      {
         tmpcard.type = j;
         tmpcard.value = i;
         tmpcard.extra = 0;
         DeckPushCard( deck, tmpcard );
      }

}


//---------------------------------------------------------------------
// Show a given card (which 0-4)
//---------------------------------------------------------------------
void CardShow( char v, char t, char which )
{
   char attr;
 
   attr = 2+(7<<3);
   if( t & 1 ) attr = 0+(7<<3);

   DrawChar( t, (which*6)+3, 6, Types, attr );
   
   if( v == 1 )
   {
      DrawChar( 0, (which*6)+2, 4, Ace, attr );
      DrawChar( 0, (which*6)+4, 8, Ace, attr );
      return;
   }
   else
   {
      DrawChar( v, (which*6)+2, 4, Numbers, attr );
      DrawChar( v, (which*6)+4, 8, Numbers, attr );
      return;
   }
}


//---------------------------------------------------------------------
// Show 5 cards (if which == -1) or a given card (1-5).
//---------------------------------------------------------------------
void DeckShow( Deck *deck, int which )
{
  Card carta;
  int i, v, t, attr;

  for( i=0; i<DeckCardsInDeck(deck); i ++)
    if( i==(which-1) || which == -1 )
    {
      v = deck->cards[i].value;
      t = deck->cards[i].type;
      CardShow( v, t, i );
    }
}
 

//---------------------------------------------------------------------
// Erase a given card (which 0-4)
//--------------------------------------------------------------------
void CardErase( char v, char t, char which )
{
   char attr;

   DrawChar( v, (which*6)+2, 4, Numbers, 7+(7<<3) );
   DrawChar( 0, (which*6)+3, 6, Discard, 0+(7<<3) );
   DrawChar( v, (which*6)+4, 8, Numbers, 7+(7<<3) );

}



//---------------------------------------------------------------------
// Erase 5 cards (if which == -1) or a given card (1-5).
//---------------------------------------------------------------------
void DeckErase( Deck *deck, int which )
{
  Card carta;
  int i, v, t;

  for( i=0; i<DeckCardsInDeck(deck); i++)
    if( i==(which-1) || which == -1 )
       CardErase( 0, 0, i );
}
 

//---------------------------------------------------------------------
// Check if the deck stack is empty (1 = empty, 0 = not empty) 
//---------------------------------------------------------------------
int DeckEmpty( Deck *deck )
{
   if ( deck->top == -1 )
      return(1);
   return(0); 
}


//---------------------------------------------------------------------
// Return the number of cards remaining in the deck
//---------------------------------------------------------------------
int DeckCardsInDeck( Deck *deck )
{
   return( deck->top + 1 ); 
}


//---------------------------------------------------------------------
// Push a card into the deck, in the upper side (non visible)
//---------------------------------------------------------------------
int DeckPushCard( Deck *deck, Card card )
{
   deck->top += 1;
   deck->cards[ deck->top ].type = card->type;
   deck->cards[ deck->top ].value = card->value;
   deck->cards[ deck->top ].extra = card->extra;
   return(1);
}


//---------------------------------------------------------------------
// Extract a card from the deck, from the non visible side
// Returns 0 if there is no card available (deck empty)
//---------------------------------------------------------------------
int DeckPopCard( Deck *deck, Card *card )
{
   if( DeckEmpty( deck ) == 1 )
      return(0);
   
   card->type  = deck->cards[ deck->top ].type;
   card->value = deck->cards[ deck->top ].value;
   card->extra = deck->cards[ deck->top ].extra;
   deck->top -= 1;

   return( 1 );
 
}


//---------------------------------------------------------------------
// Read/set a card from the deck, without actually extracting it
// Returns 0 if that card is not available (numcards < card)
//---------------------------------------------------------------------
int DeckGetCard( Deck *deck, Card *card, int which )
{
   if( DeckEmpty( deck ) == 1 || DeckLastCard(deck) < which )
      return( 0 );
   
   card->type  = deck->cards[ which ].type;
   card->value = deck->cards[ which ].value;
   card->extra = deck->cards[ which ].extra;
   return( 1 );
 
}


//---------------------------------------------------------------------
// Set a given card to a value/type
//---------------------------------------------------------------------
int DeckSetCard( Deck *deck, Card *card, int which )
{
   if( DeckEmpty( deck ) == 1 || DeckLastCard(deck) < which )
      return( 0 );
   deck->cards[ which ].type  = card->type;
   deck->cards[ which ].value = card->value;
   deck->cards[ which ].extra = card->extra;
   return( 1 );

}


//---------------------------------------------------------------------
// Shuffle the deck array using the following method:
//  for n := 52 downto 2
//  generate a random integer 'r' in the range 1..n
//  swap array[r] <-> array[n]
//  howmany = howmany times shuffle (1...n)
//---------------------------------------------------------------------
void DeckShuffle( Deck *deck, int howmany )
{
   int i, j, n;

   if( howmany < 1 )  howmany = 1;
   if( howmany > 10 ) howmany = 10;
   
   for( j=0; j<howmany; j++)
   {
     for( i=DeckCardsInDeck( deck )-1; i > 1; i-- )
     {
        n = (rand() % i)+1;
        DeckExchangeCards( deck, n, i );
     }
   }
}


//---------------------------------------------------------------------
// Exchange 2 cards
//---------------------------------------------------------------------
void DeckExchangeCards( Deck *deck, int n, int i )
{
   Card tmpcard;
   
   tmpcard.type   = deck->cards[n].type;
   tmpcard.value  = deck->cards[n].value;
   tmpcard.extra  = deck->cards[n].extra;

   deck->cards[n].type  = deck->cards[i].type;
   deck->cards[n].value = deck->cards[i].value;
   deck->cards[n].extra = deck->cards[i].extra;

   deck->cards[i].type  = tmpcard.type;
   deck->cards[i].value = tmpcard.value;
   deck->cards[i].extra = tmpcard.extra;
}


//---------------------------------------------------------------------
// Sort cards by value
//---------------------------------------------------------------------
void DeckSortCards( Deck *deck )
{
    int i, j, numelem;
    Card carta1, carta2;

    numelem = DeckCardsInDeck(deck);
    for( i=0; i<numelem-1; i++ )
        for( j=0; j<numelem-1-i; j++ )
        {
            DeckGetCard( deck, &carta1, j );
            DeckGetCard( deck, &carta2, j+1 );
            if( carta1.value > carta2.value )
               DeckExchangeCards( deck, j, j+1 );
        }
}

