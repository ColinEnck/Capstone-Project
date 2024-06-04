// credit to: https://invisible-island.net/ncurses/ncurses-intro.html
// for supplying some template code to get started
/*
	name: Battleship
	author: Colin Enck
	date initialized: May 18th, 2024
*/
#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>

typedef struct
{
    int x;
    int y;
} Point;

void drawBoard();
static void finish(int sig);

int main(int argc, char const *argv[])
{
	// curses and others setup
	setlocale(LC_ALL, "");
    signal(SIGINT, finish);     /* arrange interrupts to terminate */
    initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);   /* enable keyboard mapping */
    nonl();         /* tell curses not to do NL->CR/NL on output */
    cbreak();       /* take input chars one at a time, no wait for \n */
    curs_set(0);    /* makes the cursor invisible */
    echo();

    // initializations and setup
    int x, y;
    char c;
    getmaxyx(stdscr, y, x);
    
    // setup colors (this is a template found online)
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }

    for (;;)
    {
    	// keyboard input
        c = getch();
        switch (c) 
        {
        case 'q':
            goto done; // breaks out of the for loop
            break;
        }

    	// game logic

    	// draw stuff
        refresh();
    }

done:;

    finish(0);
	return 0;
}

void drawBoard()
{
    
}

static void finish(int sig)
{
    endwin();
    exit(0);
}
