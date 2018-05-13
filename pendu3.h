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

#include "switches.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h> /* rand */
#include "lcd.h"

#define LED_ON      PORTB |=  _BV(PINB7)
#define LED_OFF     PORTB &= ~_BV(PINB7) 
#define LED_TOGGLE  PINB  |=  _BV(PINB7)

/* Lines have to be shorter than this. Note: buffer is on stack. */
#define LINE_BUFF_LEN 55
#define F_CPU 1000000UL

void affichage();
int inWord(char c);
void showHidden();
int countOne();
void checkGuess();
void showPendu();
void reset();
int mod(int a, int b);

