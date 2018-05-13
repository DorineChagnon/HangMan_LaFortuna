/* Copyright 2018 Dorine Chagnon */
/*This file is part of Hangman.

    Hangman is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Hangman is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Hangman.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pendu3.h"

const char *dictionary [96]= {"information","available","copyright","university","management","international","development","education","community","technology","following","resources","including","directory","inspector","bookmarks","modelling","miniature","interstate","consequence","systematic","perceived","madagascar","presenting","troubleshooting","gentleman","reproduce","convicted","roommates","threatening","spokesman","activists","frankfurt","encourages","assembled","restructuring","terminals","books","school","through","links","review","years","order","privacy","items","company","group","under","general","research","january","reviews","program","games","could","great","united","hotel","center","store","travel","comments","report","member","details","terms","before","hotels","right","because","local","those","using","results","office","national","design","posted","missions","watson","lying","costumes","strict","saddam","drill","offense","bryan","protest","hobby","tries","nickname","inline","washing","builds","shaft"}; //length 96
const char alphabet [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char current_letter='#';
char word [LINE_BUFF_LEN];
int secret[LINE_BUFF_LEN];
unsigned int word_length;
int started = 0;
int score = 0;
int tries  = 0;
int i = 0;
volatile int loop = 0;
char checked[26];
int checked_length=0;


void affichage(){
  display_string_xy("\n",0,0);
  display_string("\n\n    _   _ _____ _   _ _____    _    _ _____ _   _ \n");
  display_string("   | | | |  _  | \\ | |  ___|  | \\  / |  _  | \\ | |\n");
  display_string("   | |_| | |_| |  \\| | |      |  \\/  | |_| |  \\| |\n");
  display_string("   |  _  |  _  |     | | __   |      |  _  |     |\n");
  display_string("   | | | | | | | |\\  | |_| |  | |\\/| | | | | |\\  |\n");
  display_string("   |_| |_|_| |_|_| \\_|_____|  |_|  |_|_| |_|_| \\_|\n");
  display_string("\n\n                Press Center to Start\n");
}

/*
 * Check if the character c is in the hidden word
 */
int inWord(char c){
    int j = 0;
    for (j=0; j < word_length; j++){
        if(c == word[j]){
            return 1;
        }
    }
    return 0;
}

/**
 * Display the hangman and word, 
 * by replacing every unknown character (0 in secret) by _
 */
void showHidden(){
  clear_screen();
  showPendu();
  int i=0;
  display_string("\n                 ");
  for (i = 0 ; i < word_length ; i++) {
    
    if (secret [i] == 0) {
      display_string ("_");
    } else {
      display.foreground = GREEN;
      display_char(word[i]);
      display.foreground = WHITE;
    }
    display_string(" ");
  }
  display_string ("\n\n\n                         <");
  display_char(current_letter);
  display_string(">");
  display_string("\n\n\nAlready checked: \n");
  for(i=0; i < checked_length; i++){
    if(inWord(checked[i])){
        display.foreground = GREEN;
    }else{
        display.foreground = RED;
    }
    display_char(checked[i]);
    display.foreground = WHITE;
    display_string("  ");
  }
}

/**
 * Return the number of 1 in the array secret
 */
int countOne(){
  int one = 0;
  int i;
  for (i = 0; i < word_length; i++) {
    if (secret [i] == 1) {
      one++;
    }
  }
  return one;
}

/**
 * Modify the array secret such that secret[i] is 1 if the i-th letter of word is the current letter
 **/
void checkGuess(){
  int i=0;
  for (i = 0; i < word_length; i++) {
    if (current_letter == word[i]) {
      secret [i] = 1;
    }
  }
  checked[checked_length++]=current_letter;
}

/**
 * Display the hangman
 */
void showPendu(){
    
  switch (tries) {
  case 0: /* Bottom of the gallows */
    display_string("\n\n\n\n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("                              \n");
    display_string("               ----------------------\n");
    break;

  case 1: /* the pole */
    display_string("\n\n\n                       \n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break;

  case 2 : /* the gallows */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break;

  case 3 : /* and the head */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                  | |         |\n");
    display_string("                   -          |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break;

  case 4 : /* and the body */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                  | |         |\n");
    display_string("                   -          |\n");
    display_string("                   |          |\n");
    display_string("                   |          |\n");
    display_string("                   |          |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");

    break;
  case 5 : /* and the legs */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                  | |         |\n");
    display_string("                   -          |\n");
    display_string("                   |          |\n");
    display_string("                   |          |\n");
    display_string("                   |          |\n");
    display_string("                  / \\         |\n");
    display_string("                 /   \\        |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break;

  case 6 : /* and the arms */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                  | |         |\n");
    display_string("                   -          |\n");
    display_string("                   |          |\n");
    display_string("                 --|--        |\n");
    display_string("                   |          |\n");
    display_string("                  / \\         |\n");
    display_string("                 /   \\        |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break ;
    
  case 7 : /* and the hands */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                  | |         |\n");
    display_string("                   -          |\n");
    display_string("                   |          |\n");
    display_string("                o--|--o       |\n");
    display_string("                   |          |\n");
    display_string("                  / \\         |\n");
    display_string("                 /   \\        |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break ;

  case 8 : /* and the feet */
    display_string("\n\n\n                   ___________\n");
    display_string("                   |          |\n");
    display_string("                  | |         |\n");
    display_string("                   -          |\n");
    display_string("                   |          |\n");
    display_string("                o--|--o       |\n");
    display_string("                   |          |\n");
    display_string("                  / \\         |\n");
    display_string("               o_/   \\_o      |\n");
    display_string("                              |\n");
    display_string("               ----------------------\n");
    break ;
  default :
    break ;
  }
}

void reset(){
  score = 0;
  tries  = 0;
  loop = 1;
  started = 0;
  current_letter='A';
  int alea = rand() % 97;
  char tmp [LINE_BUFF_LEN-1];
  strcpy(tmp, dictionary[alea]);
    
  word_length = strlen (tmp);
  i=0;
  for(i = 0; i < word_length; i++){
    tmp[i] = toupper(tmp[i]);
  }
  strcpy(word, tmp);
  word_length = strlen (word);
  i = 0;
  for(i=0; i < word_length; i++){
    secret[i]=0;
  }
  for(i = 0; i < checked_length+1; i++){
    checked[i] = 0;
  }
  checked_length = 0;
}

int mod(int a, int b)
{
  int r = a % b;
  return r < 0 ? r + b : r;
}

ISR(TIMER1_COMPA_vect)
{
  if (center_pressed()){
    if (started != 0){
      checkGuess();
      if (countOne() > score) {
        score = countOne() ;
      } else {
        tries++;
      }
      showHidden();
    }else started = 1;
    
    
    
    
    if(score < word_length && tries < 8) {
      loop = 1;
    }else{
      loop = 0;
    }
  }
  if(left_pressed()){
    current_letter = (mod(((current_letter-65)-1),26)+65);
    clear_screen();
    showHidden();
  }
  if(right_pressed()){
    current_letter = ((((current_letter-65)+1)%26)+65);
    clear_screen();
    showHidden();
  }
  
}



int main()
{
  /* 8MHz clock, no prescaling (DS, p. 48) */
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;
  
  init_lcd();
  init_switches();
  set_frame_rate_hz(61);
	
  /* Configure I/O Ports */
  DDRB |= _BV(PB7); /* LED pin out */
  PORTB &= ~_BV(PB7); /* LED off */

  /* enable button press interrupt */
  TCCR1A = 0;
  TCCR1B = _BV(WGM12);
  TCCR1B |= _BV(CS10);
  TIMSK1 |= _BV(OCIE1A); /* ENABLE TIMER INTERRUPT */

  OCR3A = 0;

  /*timer for random word */
  TCCR2B |= (1 << CS10);

  OCR3A = 20000;
  display.foreground = WHITE;
  affichage();
  
  LED_ON;

  do{
    srand(TCNT2);
    reset();
    
    while(!center_pressed()){
    }
    srand(TCNT2);
    reset();
    
    OCR1A = 65535;
    LED_OFF;
    sei();
    showHidden();
    while(loop);
    cli();
    LED_ON;
    if (score < word_length ) {
      display_string("\n\n      Game Over... You kill your friend...\nThe word was: "); 
      display.foreground = GREEN;
      display_string(word);
      display.foreground = WHITE;
    } else {
      display_string("\n\nCongratulation !");
    }
    display.foreground = MAGENTA;
    display_string("\n\n             Press Center to Restart");
    display.foreground = WHITE;
  } while (1);

  return -1;
}

