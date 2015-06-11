/************************************************************************/
/*                    Copyright © 2013 Max Wällstedt                    */
/*                                                                      */
/* This file is part of Ncurses-menu.                                   */
/*                                                                      */
/* Ncurses-menu is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* Ncurses-menu is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with Ncurses-menu. If not, see <http://www.gnu.org/licenses/>. */
/*                                                                      */
/************************************************************************/

#include <curses.h>
#include <locale.h>
#include "ncurses-menu.h"
#include "ncurses-readstring-example.h"
#include "rumba.h"
#include <string>

/* Prints typical menus that you might see in games */
int main (int argc, char *argv[])
{
    std::string str;
    int menu_ret = 1, menu_ret2 = 1;
    char alts[][100] = {{"1. Dodaj plik do listy udostepnianych plikow"},     /* Every menu needs an */
                         {"2. Usun plik z listy udostepnianych plikow"},
                         {"3. Wypisz liste udostepnianych plikow"},
                         {"4. Wypisz liste uzytkownikow wspierajacych protokol rumba"},
                         {"5. Wypisz liste plikow wybranego uzytkownia"}, 
                         {"6. Wybierz plik do poprbania"},
                         {"7. Quit"},    /* array like these to */
                         };   /* hold the entries.   */
    char alts2[][100] = {{"Slot 1"},
                         {"Slot 2"},
                         {"Slot 3"},
                         {"Return"},};

    setlocale (LC_CTYPE, "");

    initscr();                  /* Most of the below initialisers are */
    noecho();                   /* not necessary for this example.    */
    keypad (stdscr, TRUE);      /* It's just a template for a         */
    meta (stdscr, TRUE);        /* hypothetical program that might    */
    nodelay (stdscr, FALSE);    /* need them.                         */
    notimeout (stdscr, TRUE);
    raw();
    curs_set (0);
    init(argc,argv);
    
    do  /* This loop terminates when MAIN MENU returns 3, Quit Game.   */
    {   /* menu_ret is sent as the start value, to make the last entry */
        /* highlighted when you return to the main menu.               */
        menu_ret = print_menu (2, 5, 7, 15,
                               "RUMBA", alts, menu_ret);

        if (menu_ret == 1)  /* This is just an example program. */
        {                   /* You can't start an actual game.  */
            //clear();
            str=fun(20,0);
	       const char *c=str.c_str();
            AddFile(c);
            getch();
            //main();
        }
        else if (menu_ret == 3){
            //clear();
            //mvprintw(23,23,"Wypisuje liste udostepnianych plikow");
            endwin();
            ListMyfiles();
            getch();
        }

        else if (menu_ret == 2) /* If you select load game, a new    */
        {                       /* menu will show up without erasing */
            endwin();
            DeleteFile();
            getch();
            
        }
        else if (menu_ret == 4) /* If you select load game, a new    */
        {                       /* menu will show up without erasing */
            endwin();
            ListUsers(argv);
            getch();
            
        }
        else if (menu_ret == 5) /* If you select load game, a new    */
        {                       /* menu will show up without erasing */
            endwin();
            ListUserFiles();
            getch();
            
        }
        else if (menu_ret == 6) /* If you select load game, a new    */
        {                       /* menu will show up without erasing */
            endwin();
            DownloadFile();
            getch();
            
        }

        erase();    /* When you return from the SELECT SLOT menu,      */
    }               /* everything will be erased and MAIN MENU will be */
    while (menu_ret != 7); /* reprinted.                               */
    endwin();
    EndProgram();
    return 0;
}
