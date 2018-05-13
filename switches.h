/* This is adapted from EpicPhill's code available at:
 *    https://github.com/EpicPhill/FortunaTetris/blob/master/switches.h
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

#define SWN     PC2
#define SWE     PC3
#define SWS     PC4
#define SWW     PC5
#define SWC     PE7

#define COMPASS_SWITCHES (_BV(SWW)|_BV(SWS)|_BV(SWE)|_BV(SWN))

void init_switches();
int center_pressed();
int left_pressed();
int right_pressed();
/* Copyright 2018 Dorine Chagnon */
