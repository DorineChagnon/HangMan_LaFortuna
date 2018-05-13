/* This is adapted from EpicPhill's code available at:
 *    https://github.com/EpicPhill/FortunaTetris/blob/master/switches.c
      Licensed under the GNU General Public License
 */
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
#include <avr/io.h>

int center_start = 0;
int left_pushed = 0;
int right_pushed = 0;
int up_pushed = 0;
int down_pushed = 0;
int start = 0;

void init_switches(){
  DDRE &= ~_BV(SWC);
  PORTE |= _BV(SWC);
  DDRC &= ~_BV(SWN) & ~_BV(SWE) & ~_BV(SWS) & ~_BV(SWW);
  PORTC |= _BV(SWN) | _BV(SWE) | _BV(SWS) | _BV(SWW);

  DDRE &= ~_BV(SWC);   /* Central button */
  PORTE |= _BV(SWC);
	
  DDRC &= ~COMPASS_SWITCHES;  /* configure compass buttons for input */
  PORTC |= COMPASS_SWITCHES; 

  EICRB |= _BV(ISC40) | _BV(ISC50) | _BV(ISC71);
}

int center_pressed(){
  if ((~PINE & _BV(PE7)) && !center_start && !start) {
    center_start = 1;
    start = 1;
    return 1;
  } else if ((PINE & _BV(PE7)) && center_start){
    center_start = 0;
    start = 0;
  }
  return 0;
}

int left_pressed(){
  if ((~PINC & _BV(SWW)) && !left_pushed && !start) {
    left_pushed = 1;
    start = 1;
    return 1;
  } else if ((PINC & _BV(SWW)) && left_pushed){
    left_pushed = 0;
    start = 0;
  }
  return 0;
}

int right_pressed(){
  if ((~PINC & _BV(SWE)) && !right_pushed && !start) {
    right_pushed = 1;
    start = 1;
    return 1;
  } else if ((PINC & _BV(SWE)) && right_pushed){
    right_pushed = 0;
    start = 0;
  }
  return 0;
}

/* Copyright 2018 Dorine Chagnon */

