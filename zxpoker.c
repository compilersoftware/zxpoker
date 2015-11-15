/*---------------------------------------------------------------------

   ZXPoker  -> The Spectrum version of Linux KPoker.
   v 1.0     (c) 2005 Santiago Romero AkA NoP / Compiler
                    sromero@escomposlinux.org
 
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
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#include "sprites.c"
#include "gfx.c"
#include "cards.h"
#include "cards.c"
#include "menu.c"

#define WaitKey getkey


//---------------------------------------------------------------------
#define getakey() getchar()

#define HAND_ROYAL_FLUSH       128
#define HAND_STRAIGHT_FLUSH     64
#define HAND_POKER              32
#define HAND_STRAIGHT           16
#define HAND_FULL               10
#define HAND_FLUSH               8
#define HAND_THREE_OF_A_KIND     4
#define HAND_TWO_PAIRS           2
#define HAND_PAIR                1

#define CASH                    41

int miliseg;
int sound = 1;
unsigned char my_tmp_border;

void Startup( int game );
long start, end;
char GetKey( void );
int PlayAHand( int money, Deck *baraja );
int EvaluateHand( Deck *playing );
char DisplayHand( int value );
void ClearHand( void );
void UpdateInfo( int money, int bet );
int DoubleOrNothing( Deck *deck, int money, int won );
void DrawBoard( char flags );
void BEEP(unsigned int cycles, unsigned int tone);
void BORDER( unsigned char value );
   
int money, bet, hands;

//--- Main function ---------------------------------------------------
int main( void )
{
  unsigned char done=0;
  char tecla, option;
  Deck baraja;

  BORDER(0);
  Startup( 1 );
  start = clock();
  end = clock();
  
  /*
   Bucle:
    - Esperar pulsaciones de teclas (1-5 = apuesta, ENTER/SPC = jugar mano)
      (con 1-5 cambiar bet, con 0 empezar desde nueva partida)
    - Llamar a jugar mano
    - Si dinero == 0 -> fin juego
  */

  option = 1;
  // program main loop
  while(1)
  {
    if( option < 3 )
       DrawBoard( 1 );
    
    option = Menu();
    srand(clock());
    done = 1;

    // game main loop
    if( option == 1 )
    {
      done = 0; bet = 1; hands = 0; money = CASH;
      DrawBoard( 0 );
    }
  
    while( !done )
    {
       // play a hand 
       hands++;
       money = PlayAHand( money, baraja );

       // game end condition
       if( money <= 0 || money >= 10000 )
       {
          TextClearScreen();
          if( money >= 29999 ) money -= 30000;
          
          GameEnd( money, hands );
          done = option = 1; // to force screen redraw
       } // end if
    } // end while(!done)
    
  } // end while(1)
  
}


//---------------------------------------------------------------------
// Display game board. If menu_mode = 0, clear the screen and draw text
//---------------------------------------------------------------------
void DrawBoard( char menu_mode )
{
  char tecla;
  char i, j;

  if( menu_mode==1 ) 
  {
    ClearScreenData(0,1,32,23,0);
    TextGotoXY(1,0);
    printf(" ZX Poker v1.0         NoP/Compiler\n");
    ClearScreenAttr( 0, 0, 32, 1, 6+(1<<3) );
    ClearScreenAttr( 0, 1, 32, 22, (4<<3) );

    for( i=0; i<5; i++)
      ClearScreenAttr( (6*i)+1, 3, 5, 7, (7<<3) );
  
    for( i=0; i<5; i++)
    {
      // top
      DrawChar( 0, (6*i)+(1), 3, Corners, -1 );
      for( j=0; j<3; j++ ) 
         DrawChar( 1, (6*i)+2+j, 3, Corners, -1 );
      DrawChar( 2, (6*i)+(1+4), 3, Corners, -1 );
      
      // vertical lines
      for( j=0; j<5; j++ )
      {
         DrawChar( 7, (6*i)+1, 4+j, Corners, -1 );
         DrawChar( 3, (6*i)+5, 4+j, Corners, -1 );
      }
     
      // bottom
      DrawChar( 6, (6*i)+(1), 9, Corners, -1 );
      for( j=0; j<3; j++ ) 
         DrawChar( 5, (6*i)+2+j, 9, Corners, -1 );
      DrawChar( 4, (6*i)+(1+4), 9, Corners, -1 );
  
      // Draw the numbers
      DrawChar( i+1, (6*i)+(3), 10, Numbers, -1);
    }
    
    // Blue status bar
    ClearScreenAttr( 0, 23, 32, 1, 7+(1<<3) );

  } // end if( menu_mode )
  else
  {
    ClearHand();
    TextFG_Green(); TextBG_Green();
    TextGotoXY(2,13); 
    if( lang == 1 ) printf("Tienes  : ");
    else            printf("You have: ");
    TextGotoXY(1,18); 
    if( lang == 1 ) printf("       Doble o nada? (s/n)");
    else            printf("    Double or nothing? (y/n) ");
    TextGotoXY(3,19); 
    if( lang == 1 ) printf("   1-5 = Selecciona una carta ");
    else            printf("      1-5 = Select a card ");
    TextGotoXY(3,21); 
    if( lang == 1 ) printf("1-5=Apuesta  0=Fin   Enter=Seguir ");
    else            printf("1-5=Bet      0=End     Enter=Play ");
    TextGotoXY(2,20); 
    if( lang == 1 ) printf("1-5=Descartar   Space/Enter=Seguir ");
    else            printf("1-5=Discard       Space/Enter=Play ");
  
    // Draw the "$", "Bet=" and "e" symbols...
    DrawChar( 0, 1, 23, MoneySymbols, 6+(1<<3));
    DrawChar( 1, 26, 23, MoneySymbols, 6+(1<<3));
    DrawChar( 2, 27, 23, MoneySymbols, 6+(1<<3));
    DrawChar( 3, 30, 23, MoneySymbols, 6+(1<<3));
    UpdateInfo( money, bet );
  } // end else
 
}


//---------------------------------------------------------------------
// Play a game hand
//---------------------------------------------------------------------
/*
 
 - Preparar baraja.
 - Sacar y mostrar 5 cartas.
 - Permitir seleccionar 1-2-3-4-5 para descartar (N cartas)
 - Sacar N cartas sustituyendo a las elegidas
 - Evaluar la jugada
 - Mostrar el resultado
   - Si no se gana nada, quitar dinero y salir de la función
   - Si se gana, aumentar dinero y jugar a doble o nada
     - LLamar a doble_o_nada()
 - Permitir cambiar la apuesta
 
 
*/
int PlayAHand( int money, Deck baraja )
{
  Deck playing;
  Card tmpcard;
  int i, oldmoney;
  char done = 0;
  char discarded[5];
  char jugada;
  char tecla, numero;
  
  // Prepare the hand to be played
  DeckInit( baraja );
  DeckInit( playing );
  DeckFillPoker( baraja );
  DeckShuffle( baraja, 2 );
  
  // Get 5 cards to play with
  for(i=0; i<5; i++)
  {
    discarded[i] = 0;
    DeckPopCard( baraja, tmpcard );
    DeckPushCard( playing, tmpcard );
  }
  
  // Display the deck
  DeckShow( playing, -1 );
  money -= bet;
  ClearScreenAttr( 0, 20, 32, 1, 0+(4<<3) );
  UpdateInfo( money, bet );
  
  // Discard cards you don't like (1-5 discard card, 0 continue)
  while(!done)
  {
    tecla = getchar();
    numero = tecla-'0';
    if( numero >= 1 && numero <= 5 )
    {
       discarded[numero-1] = 1-discarded[numero-1];
       if( discarded[numero-1] == 1)     DeckErase( playing, numero );
       else                              DeckShow ( playing, numero );
    }

    if( tecla == ' ' || tecla == '\n' ) done = 1;
  }
  
  // Exchange the discarded cards by new ones
  for(i=0; i<5; i++)
  {
     if( discarded[i] == 1 )
     {
        DeckPopCard( baraja, tmpcard );
        DeckSetCard( playing, tmpcard, i );
     }
  }

  // Display the deck
  ClearScreenAttr( 0, 20, 32, 1, 4+(4<<3) );
  DeckShow( playing, -1 );

  // Check if we won anything
  DeckSortCards( playing );
  jugada = EvaluateHand( playing );

  TextBG_Green();

  if( jugada == 0 )
  {
     // player loses
     DisplayHand( jugada );

     TextFG_Black();
     TextGotoXY(2,14); 
     if( lang == 1 ) printf("Pierdes : ");
     else            printf("You lose: ");
     TextFG_Red();   TextGotoXY(12,14); 
     printf("$%d    ", bet );
     ClearScreenAttr( 0, 21, 32, 1, 0+(4<<3) );
     UpdateInfo( money, bet );
    }
  else if( jugada > 0 )
  {
     // player wins
     DisplayHand( jugada );

     TextFG_Black();
     TextGotoXY(2,14); 
     if( lang == 1 ) printf("Ganas   : ");
     else            printf("You win : ");
     oldmoney = money;
     money = DoubleOrNothing( baraja, money, (bet*jugada));
     if( money == oldmoney )
     {
       TextFG_Black();
       TextGotoXY(2,14); 
       if( lang == 1 ) printf("Ganas   : $0    ");
       else            printf("You win : $0    ");
     }
     ClearScreenAttr( 0, 21, 32, 1, 0+(4<<3) );
     UpdateInfo( money, bet );
  }

  // Check for new bets, restart game or continue.
  done = 0;
  while(!done)
  {
     tecla = getchar();
     numero = tecla-'0';
     if( numero == 0 )
     {
        money += 30000;
        bet = 1;
        numero = 9;
        tecla = ' ';
     }
     if( (numero >= 1 && numero <= 5) || numero == 0 )
     {
        if( numero != 0 ) bet = numero;
        UpdateInfo( money, bet );
     }
     if( tecla == ' ' || tecla == '\n' ) done = 1;
  }

  ClearScreenAttr( 0, 16, 32, 1, 4+(4<<3) );
  ClearHand();
  return( money );
     
}


//---------------------------------------------------------------------
// Play the "double or nothing" game with the money you won
//---------------------------------------------------------------------
int DoubleOrNothing( Deck *deck, int money, int won )
{
  char done=0, tecla, numero, done2, i;
  Deck playing;
  Card cpu, yours, tmpcard;
  int n;
  
  srand(clock());

  while(!done)
  {
    
    TextFG_Blue();
    TextGotoXY(12,14); printf("$%d    ", won);
    ClearScreenAttr( 0, 18, 32, 1, 0+(4<<3) );
    
    do     tecla = getchar();
    while( tecla != 'n' && tecla != 's' && tecla != 'y');

    if( tecla == 'n' ) 
    {
       done = 1;
       ClearScreenAttr( 0, 16, 32, 1, 4+(4<<3) );
    }
    else
    {
      ClearScreenAttr( 0, 16, 32, 1, 4+(4<<3) );
      ClearScreenAttr( 0, 18, 32, 1, 4+(4<<3) );
      ClearScreenAttr( 0, 19, 32, 1, 0+(4<<3) );
      DeckInit( deck );
      DeckInit( playing );
      DeckFillPoker( deck );
      DeckShuffle( deck, 1 );
      
      // Get 5 cards to play with
      for(i=0; i<5; i++)
      {
        DeckPopCard( deck, tmpcard );
        DeckPushCard( playing, tmpcard );
      }
      
      // clear cards, get a random one and show it
      DeckErase( playing, -1 );
      n = ((rand() % 5) +1);
      DeckShow( playing, n );

      // wait for user selection
      done2 = 0;
      while(!done2)
      {
        tecla = getchar();
        numero = tecla-'0';
        if( (numero >= 1 && numero <= 5) )
        {
           if( numero != n )
           {
             // Check if the player wins or loses
             DeckShow( playing, numero );
             DeckGetCard( playing, cpu, n-1 );
             DeckGetCard( playing, yours, numero-1 );
                          
             TextFG_Red(); TextBG_Green();
             TextFG_Red();
             TextGotoXY(12,13); 
             // Clear info area (money won/lost, info, etc...)
             ClearScreenData( 12, 13, 15, 1, 0 );

             if( yours.value == 1 ) yours.value = 15;
             if( cpu.value == 1 ) cpu.value = 15;
             if( yours.value < cpu.value )
             {
                if( lang == 1 ) printf("Menor ");
                else            printf("Lower ");
                won = 0; 
                done = 1;
             }
             else if( yours.value > cpu.value )
             {
                if( lang == 1 ) printf("Mayor ");
                else            printf("Higher ");
                won *= 2;
             }
             else
             {
                if( lang == 1 ) printf("Empate ");
                else            printf("Draw ");
                won = won;
             }
             
             done2 = 1;
           }
        }
      }
      ClearScreenAttr( 0, 19, 32, 1, 4+(4<<3) );
    }
  }

  ClearScreenAttr( 0, 18, 32, 1, 4+(4<<3) );
  return( money+won );
}

      

//---------------------------------------------------------------------
// Evaluate player's current hand 
// (0=nothing, 1=pair, 2=double pairs, 3=three of a kind...
//---------------------------------------------------------------------


int EvaluateHand( Deck *playing )
{
  int v1, v2, v3, v4, v5;
  int t1, t2, t3, t4, t5;
  int how_many_pairs;

  v1 = playing->cards[0].value; t1=playing->cards[0].type;
  v2 = playing->cards[1].value; t2=playing->cards[1].type;
  v3 = playing->cards[2].value; t3=playing->cards[2].type;
  v4 = playing->cards[3].value; t4=playing->cards[3].type;
  v5 = playing->cards[4].value; t5=playing->cards[4].type;

  // Straight, straight flush and royal flush:
  if( (v5==v4+1 && v4==v3+1 && v3==v2+1 && v2==v1+1) || (v2==v1+9))
  {
     if( v2==v1+9 )
        return HAND_ROYAL_FLUSH;
     if( t1==t2 && t2==t3 && t3==t4 && t4==t5 )
        return HAND_STRAIGHT_FLUSH;
     else
        return HAND_STRAIGHT;
  }

  // poker (Four of a kind)
  if( ( (v1==v2) && (v2==v3) && (v3==v4)) || 
      ( (v2==v5) && (v2==v3) && (v3==v4)) )
     return( HAND_POKER );

  // Full House
  if( ( (v1==v3) && (v4==v5) ) ||
      ( (v1==v2) && (v3==v5) ) )
     return( HAND_FULL );
   
  // Flush
  if( t1==t2 && t2==t3 && t3==t4 && t4==t5 )
      return HAND_FLUSH;

  // Three of a kind
  if( v1==v3 || v3==v5 || v2==v4 )
      return HAND_THREE_OF_A_KIND;

  // Double pairs
  how_many_pairs = 0;
  if( v1==v2 ) how_many_pairs++;
  if( v2==v3 ) how_many_pairs++;
  if( v3==v4 ) how_many_pairs++;
  if( v4==v5 ) how_many_pairs++;
  if( how_many_pairs == 2 )
      return( HAND_TWO_PAIRS );
  
  // Pair
  if(
      ( (v1==v2) && ((v1>10)||v1==1) ) ||
      ( (v2==v3) && ((v2>10)||v2==1) ) ||
      ( (v3==v4) && ((v3>10)||v3==1) ) ||
      ( (v4==v5) && ((v4>10)||v4==1) ) 
    )
      return( HAND_PAIR );
  
  return(0);
}

 
//---------------------------------------------------------------------
// UpdateMoney
//---------------------------------------------------------------------
void UpdateInfo( int money, int bet )
{
  TextFG_White(); TextBG_Blue();
  TextGotoXY(4, 23); 
  printf("%d ", money );
  
   // Display the current bet
  DrawChar( bet, 29, 23, Numbers, 7+(1<<3) );

  TextFG_Green(); TextBG_Green();
}

  

//---------------------------------------------------------------------
// Clear player's hand
//---------------------------------------------------------------------
void ClearHand()
{
  // Clear info area (money won/lost, info, etc...)
  ClearScreenData( 12, 13, 22, 1, 0 );
  ClearScreenAttr( 0, 12, 32, 10, 4+(4<<3) );
}


//---------------------------------------------------------------------
// Display player's hand
//---------------------------------------------------------------------
char DisplayHand( int value )
{
 
   ClearScreenAttr( 1, 13, 12, 1, 0+(4<<3) );
   
   TextBG_Green();
   TextFG_Black();
   TextGotoXY(12,13); 
   TextFG_Red();
   if( value > 0 ) TextFG_Blue();
   if( lang == 1 )
   {
     if( value == HAND_ROYAL_FLUSH )            printf("Real Flush ");
     else if( value == HAND_STRAIGHT_FLUSH )    printf("Escalera Flush ");
     else if( value == HAND_POKER )             printf("Poker ");
     else if( value == HAND_STRAIGHT )          printf("Escalera ");
     else if( value == HAND_FULL )              printf("Full House ");
     else if( value == HAND_FLUSH )             printf("Flush ");
     else if( value == HAND_THREE_OF_A_KIND )   printf("Trio ");
     else if( value == HAND_TWO_PAIRS )         printf("Dobles parejas ");
     else if( value == HAND_PAIR )              printf("Pareja ");
     else                                       printf("Nada ");
   }
   else
   {
     if( value == HAND_ROYAL_FLUSH )            printf("Royal Flush ");
     else if( value == HAND_STRAIGHT_FLUSH )    printf("Straight Flush ");
     else if( value == HAND_POKER )             printf("Poker ");
     else if( value == HAND_STRAIGHT )          printf("Straight ");
     else if( value == HAND_FULL )              printf("Full House ");
     else if( value == HAND_FLUSH )             printf("Flush ");
     else if( value == HAND_THREE_OF_A_KIND )   printf("Three of a kind ");
     else if( value == HAND_TWO_PAIRS )         printf("Two Pairs ");
     else if( value == HAND_PAIR )              printf("Pair ");
     else                                       printf("Nothing ");
   }

   TextFG_White();

}

//---------------------------------------------------------------------
// game = 1 -> Startup the game itself
// game = 0 -> Startup just a new game
//---------------------------------------------------------------------
void Startup( int game )
{
   int y;
   
   if( game )
   {
      TextDefault();
      TextClearScreen();
      InitGFX();
      ClearScreen( 0, 0 );
   }
}


//---------------------------------------------------------------------
char GetKey( void )
{  return( getk() ); }


//---------------------------------------------------------------------
void BEEP(unsigned int cycles, unsigned int tone)
{
#asm
   pop bc      ; bc = return address
   pop hl      ; hl = tone
   pop de      ; de = cycles
   push de
   push hl
   push bc
   jp 0x03b5   ; jump to ROM beep
#endasm
}


//---------------------------------------------------------------------
// Set Border
//---------------------------------------------------------------------
void BORDER( unsigned char value )
{
   
   my_tmp_border = value<<3;
#asm
   ld hl, 2
   add hl, sp
   ld a, (hl)
   ld c, 254
   out (c), a
   ld hl, 23624
   ld a, (_my_tmp_border)
   ld (hl), a
#endasm
}

