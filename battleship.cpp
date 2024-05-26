// credit to: https://invisible-island.net/ncurses/ncurses-intro.html
// for supplying some template code to get started
/*
	name: Battleship
	author: Colin Enck
	date initialized: May 18th, 2024
*/
#include <ncurses.h>
#include <stdlib.h> // need this for exit(0); code breaks otherwise
#include <signal.h>
#include <locale.h>
#define STARTHP 10
#define STARTSTR 10
#define STARTARM 2

using namespace std;

typedef struct {
    int x;
    int y;
} Point;

static void finish(int sig);

int main(int argc, char const *argv[]) {
	// curses and others setup
	setlocale(LC_ALL, "");
    signal(SIGINT, finish);     /* arrange interrupts to terminate */
    initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);   /* enable keyboard mapping */
    nonl();         /* tell curses not to do NL->CR/NL on output */
    // cbreak();       /* take input chars one at a time, no wait for \n */
    curs_set(0);    /* makes the cursor invisible */
    echo();

    // initializations and setup
    int x, y;
    getmaxyx(stdscr, y, x);
    
    // setup colors (this is a template found online)
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }

    for (;;) {
    	// keyboard input
    	getch();

    	// game logic

    	// draw stuff
        refresh();
    }

    finish(0);
	return 0;
}

static void finish(int sig) {
    endwin();
    exit(0);
}
