/*--------------------------------------------------------------------

   ZXPoker menu file.

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

char Menu( void );
void ShowCredits( void );
void ShowInstructions( void );
void GameEnd( int money, int hands );

char lang=0;

//---------------------------------------------------------------------
// Game Menu
//---------------------------------------------------------------------
char Menu( void )
{
   int i;
   char tecla;

   for( i=0; i<5; i++) CardShow( 1, 2, i );

   TextFG_Black();
   TextBG_Green();

   // draw the multilanguage menu
   if( lang == 1 ) // Spanish
   {
     TextGotoXY(10,14); printf("1. Jugar a ZXPoker  ");
     TextGotoXY(10,16); printf("2. Instrucciones    ");
     TextGotoXY(10,18); printf("3. Ingles/English   ");
     TextGotoXY(10,20); printf("4. Creditos         ");
   }
   else
   {
     TextGotoXY(10,14); printf("1. Play ZXPoker     ");
     TextGotoXY(10,16); printf("2. Instructions     ");
     TextGotoXY(10,18); printf("3. Spanish/Espanyol ");
     TextGotoXY(10,20); printf("4. Credits          ");
   }

   // menu loop
   do 
   {
      tecla = getchar();

      if( tecla=='1' ) // start game
      {
        for( i=0; i<5; i++) CardErase( 1, 2, i );
        return(1);
      }
      else if( tecla == '2' )
      {
        ShowInstructions();
        return(2);
      }
      else if( tecla == '3' ) // change language
      {
        lang=1-lang;
        return(3);
      }
      else if( tecla == '4' )
      {
        ShowCredits();
        return(4);
      }
   }
   while( 1 );

   return(1);

}


//---------------------------------------------------------------------
// Show the credits
//---------------------------------------------------------------------
void ShowCredits( void )
{
   int i;
   char tecla;

   for( i=0; i<5; i++) CardShow( 1, 1, i );

   TextFG_Red();
   TextBG_Green();
   ClearScreenData( 7, 14, 20, 7, 0 );

   // draw the multilanguage menu
   if( lang == 1 ) // Spanish
   {
     TextGotoXY(14,12); printf(" CREDITOS ");
     TextFG_Blue();
     TextGotoXY(2,14); printf("Codigo: sromero (NoP) - 01-02-2005 ");
     TextFG_Black();
     TextGotoXY(2,16); printf(" Gracias a Fede, Miguel, Pedrete,");
     TextGotoXY(2,17); printf("JP, Jose Manuel y Jesus Ramos, asi");
     TextGotoXY(2,18); printf("  como a muchos otros de e.c.s.s.");
     TextFG_Blue();
     TextGotoXY(3,20); printf("http://www.speccy.org/compiler/ ");
   }
   else
   {
     TextGotoXY(14,12); printf("  CREDITS ");
     TextFG_Blue();
     TextGotoXY(2,14); printf("Code: sromero (NoP)  -  01-02-2005 ");
     TextFG_Black();
     TextGotoXY(2,16); printf(" Thanks to Fede, Miguel, Pedrete,");
     TextGotoXY(2,17); printf("JP, Jose Manuel, Jesus Ramos, and");
     TextGotoXY(2,18); printf("    many others from e.c.s.s.    ");
     TextFG_Blue();
     TextGotoXY(3,20); printf("http://www.speccy.org/compiler/ ");

   }

   TextFG_Red();
   TextGotoXY(13,22); printf("[ENTER/SPACE]");
   
   do     tecla = getchar();
   while( tecla !=  ' ' && tecla != '\n' );

   ClearScreenData(1,12,32,11,0);

}


//---------------------------------------------------------------------
// Show the game manual
//---------------------------------------------------------------------
void ShowInstructions( void )
{
   int i;
   char tecla;

   TextFG_Yellow();
   TextBG_Black();
   ClearScreenData( 0, 1, 32, 22, 0 );
   ClearScreenAttr( 0, 1, 32, 22, 7 );

   // draw the multilanguage menu
   if( lang == 1 ) // Spanish
   {
     TextFG_Yellow();
     TextGotoXY( 1, 2);
     puts(" Reglas del Poker-Solitario:\n\n");
     TextFG_White();
     puts(" Se reparten 5 cartas al jugador,");
     puts(" quien debe decidir cuales quiere");
     puts(" descartar (con las teclas 1 a 5)");
     puts(" a cambio de nuevas cartas.\n");
     
     puts(" Tras el descarte, se evalua la");
     puts(" mano del jugador: si tiene algun");
     puts(" tipo de combinacion como parejas,");
     puts(" trios, poker, escalera, etc.,");
     puts(" el jugador ganara lo que haya");
     puts(" apostado (Bet o apuesta).\n");
     
     puts(" Si el jugador no tiene ninguna");
     puts(" jugada, perdera la cantidad que");
     puts(" aposto (Bet), de 1 a 5 euros.\n");

     TextFG_White(); TextBG_Blue();
     TextGotoXY( 1, 23 );
     printf(" [Pag. 1/3 - Enter/Space=Continuar]");
     TextFG_White(); TextBG_Black();
     do     tecla = getchar();
     while( tecla !=  ' ' && tecla != '\n' );
     ClearScreenData( 0, 1, 32, 22, 0 );
     
     TextFG_Yellow();
     TextGotoXY( 1, 2);
     puts(" Como ganar en el Poker Solitario:\n");
     TextFG_White();
     puts(" El jugador gana con manos tipicas");
     puts(" del poker: como 1 euro por una");
     puts(" pareja de figuras (A, J, Q, o K),");
     puts(" 2 euros por dobles parejas, o 32");
     puts(" euros por un poker, por ejemplo.\n");
     
     puts(" Si el jugador gana algo, el juego");
     puts(" le ofrece la posibilidad de jugar-");
     puts(" selo a doble o nada: se muestra");
     puts(" una carta y el jugador elige otra:");
     puts(" si la suya es mayor ganara el");
     puts(" doble pero si es menor perdera el");
     puts(" dinero en juego.\n");

     puts(" Tras acabar una mano puedes cam-");
     puts(" biar tu apuesta (bet), con las");
     puts(" teclas 1-5. Con 0 acaba el juego.");

     TextFG_White(); TextBG_Blue();
     TextGotoXY( 1, 23 );
     printf(" [Pag. 2/3 - Enter/Space=Continuar]");
     TextFG_White(); TextBG_Black();
     do     tecla = getchar();
     while( tecla !=  ' ' && tecla != '\n' );
     ClearScreenData( 0, 1, 32, 22, 0 );

     TextFG_Yellow();
     TextGotoXY( 1, 2);
     printf(" Algunas jugadas ganadoras:\n\n");
     TextFG_White();

     printf("* Pareja: 2 cartas iguales (solo\n");
     printf("  figuras A, J, Q, K, numeros no).\n");
     printf("* Doble pareja: 2 parejas (aqui \n");
     printf("  los numeros si hacen parejas).\n");
     printf("* Trio, Poker: 3 o 4 cartas iguales\n");
     printf("* Full: 3 + 2 cartas iguales.\n");
     printf("* Flush: 5 cartas del mismo palo.\n");
     printf("* Escalera: Cartas consecutivas.\n");
     printf("* Escalera de color: (mismo color).\n\n");
     printf(" Puedes apostar de 1 a 5e cada vez.\n");
     printf(" La apuesta multiplica el valor de\n");
     printf(" la jugada, y combinado con el\n");
     printf(" doble o nada puede dar mucho $$$.\n\n");
     printf(" El juego sigue hasta que retiras\n");
     printf(" con la tecla '0' tras una jugada,\n");
     printf(" o hasta que te quedas sin dinero.\n");
     TextFG_White(); TextBG_Blue();
     TextGotoXY( 1, 23 );
     printf("   [Pag. 3/3 - Enter/Space=Menu]   ");
     TextFG_White(); TextBG_Black();
     do     tecla = getchar();
     while( tecla !=  ' ' && tecla != '\n' );
     ClearScreenData( 0, 1, 32, 22, 0 );
   }

   else // english
   { 
     TextFG_Yellow();
     TextGotoXY( 1, 2);
     printf(" Solitaire-Poker rules:\n\n");
     TextFG_White();
     printf("  The player gets 5 cards, and he \n");
     printf(" can choose which of them wants\n");
     printf(" to discard using keys 1 to 5,\n");
     printf(" getting new cards replacing the\n");
     printf(" discarded ones.\n\n");
     
     printf("  After discard, player's hand is\n");
     printf(" evaluated: if he has any kind of\n");
     printf(" poker-hand such as pair, 3 of a\n");
     printf(" kind, poker, straight, etc., the\n");
     printf(" player will win the Bet value,\n");
     printf(" otherwise he'll lose that money.\n\n");

     printf("  After a hand you can change the\n");
     printf(" Bet value, using 1-5 keys. By\n");
     printf(" pressing 0 you'll return to the\n");
     printf(" main menu and the game ends.\n");

     TextFG_White(); TextBG_Blue();
     TextGotoXY( 1, 23 );
     printf("  [Page 1/3 - Enter/Space=Continue]");
     TextFG_White(); TextBG_Black();
     do     tecla = getchar();
     while( tecla !=  ' ' && tecla != '\n' );
     ClearScreenData( 0, 1, 32, 22, 0 );
     
     TextFG_Yellow();
     TextGotoXY( 1, 2);
     printf(" How to win in Solitaire-Poker:\n\n\n");
     TextFG_White();
     printf("  Player wins with typical poker\n");
     printf(" hands: A pair of A, J, Q or K\n");
     printf(" gives 1 EUR, two pairs give 2 EUR,\n");
     printf(" & a poker gives 32 EUR, by example.\n\n");
     
     printf("  If the player wins, the game will\n");
     printf(" ask him for a 'Double Or Nothing'\n");
     printf(" game: the CPU will show a card:\n");
     printf(" if you select an higher card you\n");
     printf(" will double your winnings, other-\n");
     printf(" wise you'll lose the money you won\n");
     printf(" in your last hand.\n");


     TextFG_White(); TextBG_Blue();
     TextGotoXY( 1, 23 );
     printf("  [Page 2/3 - Enter/Space=Continue]");
     TextFG_White(); TextBG_Black();
     do     tecla = getchar();
     while( tecla !=  ' ' && tecla != '\n' );
     ClearScreenData( 0, 1, 32, 22, 0 );

     TextFG_Yellow();
     TextGotoXY( 1, 2);
     printf(" Some winning hands:\n\n\n");
     TextFG_White();

     printf("* Pair: 2 equal cards, if they\n");
     printf("  are not numbers (only A,Q,J,K).\n");
     printf("* Two pairs: 2 pairs, including \n");
     printf("  0-10 numbers (and A,Q,J,K).\n");
     printf("* 3-of-a-kind, Poker: 3 or 4\n");
     printf("  equal cards. \n");
     printf("* Full: 3 + 2 equal cards.\n");
     printf("* Flush: 5 cards of the same suit.\n");
     printf("* Straight: Consecutive cards.\n");
     printf("* Color Straight: (same color).\n\n");
     printf(" The bet can be from 1 to 5 EUR.\n\n");
     printf(" The game continues until you retire");
     printf(" by pressing the '0' key or until\n");
     printf(" you lose all your money.\n");
     TextFG_White(); TextBG_Blue();
     TextGotoXY( 1, 23 );
     printf("   [Page 3/3 - Enter/Space=Menu]   ");
     TextFG_White(); TextBG_Black();
     do     tecla = getchar();
     while( tecla !=  ' ' && tecla != '\n' );
     ClearScreenData( 0, 1, 32, 22, 0 );
   }

   ClearScreenData(1,12,32,11,0);
   TextBG_Green();

}


//---------------------------------------------------------------------
// Game end
//---------------------------------------------------------------------
void GameEnd( int money, int hands )
{
   char tecla;
    
   TextFG_Yellow();
   TextBG_Black();
   ClearScreenData( 0, 1, 32, 22, 0 );
   ClearScreenAttr( 0, 1, 32, 22, 7 );

   TextGotoXY(12,6);
   if( lang==1 )
      printf(" FIN DEL JUEGO ");
   else
      printf("   GAME OVER ");
   
   TextFG_White();
   if( lang==1 )
   {
     TextGotoXY(5,10);   printf("* Dinero restante : ");
     TextGotoXY(5,12);   printf("* Manos jugadas   : ");
   }
   else
   {
     TextGotoXY(5,10);   printf("* Remaining money : ");
     TextGotoXY(5,12);   printf("* Hands played    : ");
   }
   TextFG_Red();
   if( money < 0 ) money=0;
   TextGotoXY(25,10); printf("%d ", money );
   TextGotoXY(25,12); printf("%d ", hands );
   TextFG_White();

   if( money == 0 )
   {
     if( lang==1 )
     { TextGotoXY(5,17);   printf("!Mas suerte la proxima vez! ");  }
     else
     { TextGotoXY(5,17);   printf("   Better luck next time! ");  }
   }
   else if( money >= 10000 )
   {
     if( lang==1 )
     { TextGotoXY(5,17);   printf(" !Has derrotado a la banca! ");  }
     else
     { TextGotoXY(5,17);   printf("     You beat the bank! ");  }
   }

   TextFG_White();
   TextGotoXY(12,21); printf("[ENTER/SPACE]");

   do     tecla = getchar();
   while( tecla !=  ' ' && tecla != '\n' );
   
   TextBG_Green();
}
