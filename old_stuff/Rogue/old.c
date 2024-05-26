// credit to: https://invisible-island.net/ncurses/ncurses-intro.html
// for supplying some template code to get started
/*
	name: Sand
	author: Colin Enck
	date initialized: May 15th, 2024
*/
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <locale.h>

typedef struct
{
    int x, y; // entity position
    char type; // type of entity, represented by char it prints to screen
    int color; // color pair of the entity
} Entity;

void printEntity(Entity e);
static void finish(int sig);

int main(int argc, char const *argv[])
{
	// curses and others setup
	setlocale(LC_ALL, "");
    signal(SIGINT, finish);      /* arrange interrupts to terminate */
    initscr();       /* initialize the curses library */
    keypad(stdscr, TRUE);   /* enable keyboard mapping */
    nonl();          /* tell curses not to do NL->CR/NL on output */
    cbreak();        /* take input chars one at a time, no wait for \n */
    noecho();        /* disable echo */
    curs_set(0);     /* makes the cursor invisible */

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

    // initialize and delcare other stuff here
    Entity me;
    me.x = 3;
    me.y = 5;
    me.color = 2;
    me.type = '@';

    // game loop
    for (;;)
    {
        getch();
    	// take user input here

    	// update everything/implement game logic here

    	// draw things to the screen here
        printEntity(me);
    }

    finish(0);
	return 0;
}

static void finish(int sig)
{
    endwin();
    exit(0);
}

void printEntity(Entity e)
{
    switch (e.type)
    {
    case '@':
        attrset(COLOR_PAIR(e.color));
        mvaddch(e.y, e.x, '@');
        break;
    }
}