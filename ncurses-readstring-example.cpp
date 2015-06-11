/************************************************************************/
/*                    Copyright © 2013 Max Wällstedt                    */
/*                                                                      */
/* This file is part of Ncurses-readstring.                             */
/*                                                                      */
/* Ncurses-readstring is free software: you can redistribute it and/or  */
/* modify it under the terms of the GNU General Public License as       */
/* published by the Free Software Foundation, either version 3 of the   */
/* License, or (at your option) any later version.                      */
/*                                                                      */
/* Ncurses-readstring is distributed in the hope that it will be        */
/* useful, but WITHOUT ANY WARRANTY; without even the implied warranty  */
/* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with Ncurses-readstring. If not, see                           */
/* <http://www.gnu.org/licenses/>.                                      */
/*                                                                      */
/************************************************************************/

#include <curses.h>
#include <locale.h>
#include "ncurses-readstring.h"
#include "ncurses-readstring-example.h"
#include <string>
#include <iostream>

using namespace std;

std::string fun(int x, int y)
{
    /* "i" is used in for-loops to keep track of the x coordinate */
    /* "key" is used for storing the value returned by getch()    */
    int i, key;
    char string1[20];  /* The two string variables */

    setlocale (LC_CTYPE, "");

    initscr();                  /* Most of the below initialisers are */
    noecho();                   /* not necessary for this example.    */
    keypad (stdscr, TRUE);      /* It's just a template for a         */
    meta (stdscr, TRUE);        /* hypothetical program that might    */
    nodelay (stdscr, FALSE);    /* need them.                         */
    notimeout (stdscr, TRUE);
    raw();
    curs_set (0);
	
    mvprintw (3+x, 10+y, "Podaj lokalizacje pliku...");
    mvaddch (5+x, 10+y, ACS_ULCORNER);  /* Starts to print the first frame */

    for (i = 0; i < 20; i++)
        mvaddch (5+x, 10+y + i + 1, ACS_HLINE);

    mvaddch (5+x, 10+y + i + 1, ACS_URCORNER);
    mvaddch (6+x, 10+y, ACS_VLINE);

    for (i = 0; i < 20; i++)
        mvaddch (6+x, 10 + i + 1, ' ');

    mvaddch (6+x, 10+y + i + 1, ACS_VLINE);
    mvaddch (7+x, 10+y, ACS_LLCORNER);

    for (i = 0; i < 20; i++)
        mvaddch (7+x, 10+y + i + 1, ACS_HLINE);

     mvaddch (7+x, 10+y + i + 1, ACS_LRCORNER);
     mvreadstr (6+x, 12+y, string1, 18, 0);  /* readstring is called here. */

    // mvaddch (5, 35, ACS_ULCORNER);  /* Starts to print the second frame */

    // for (i = 0; i < 20; i++)
    //     mvaddch (5, 35 + i + 1, ACS_HLINE);

    // mvaddch (5, 35 + i + 1, ACS_URCORNER);
    // mvaddch (6, 35, ACS_VLINE);

    // for (i = 0; i < 20; i++)
    //     mvaddch (6, 35 + i + 1, ' ');

    // mvaddch (6, 35 + i + 1, ACS_VLINE);
    // mvaddch (7, 35, ACS_LLCORNER);

    // for (i = 0; i < 20; i++)
    //     mvaddch (7, 35 + i + 1, ACS_HLINE);

    // mvaddch (7, 35 + i + 1, ACS_LRCORNER);
    // mvreadstr (6, 37, string2, 18, 0);  /* readstring is called here */
    //                                     /* once again.               */
    mvprintw (9+x, 10+y, "Podana przez ciebie lokalizacja to:");
    mvprintw (10+x, 10+y, "\"%s\"", string1);
                                            /* The two entered strings */
    mvprintw (12+x, 10+y, "Nacisnij q zeby przejsc dalej..."); /* are both printed.       */

//    do                      /* Loops until you press 'q' */
//    {
        key = getch();
//    }
//    while (key != 'q');
    //clear();
    //fun(0,0);
    //endwin();
    return string1;
}
