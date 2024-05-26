// credit to: https://invisible-island.net/ncurses/ncurses-intro.html
// for supplying some template code to get started
/*
	name: Rogue Clone
	author: Colin Enck
	date initialized: May 18th, 2024
*/
#include <ncurses.h>
#include <stdlib.h> // need this for exit(0); code breaks otherwise
#include <signal.h>
#include <locale.h>
#define STARTHP 10
#define STARTSTR 10
#define STARTARM 10
#define MAXHALLVERTS 10

using namespace std;

typedef struct {
    int x;
    int y;
} Point;

class Entity {
	int x, y, color;
	char type;
public:
	Entity(int a, int b, int c, char d);
	void draw();
};

class Room {
    Point tl; // point of top left corner
    int dx, dy; // how far down/right it goes from the tl corner
public:
    Room(Point a, int b, int c);
    void draw();
};

class Hall {
    Point verts[MAXHALLVERTS]; // array of verticies of the hallway
    int vertNum;
public:
    Hall(Point *v, int num);
    void draw();
};

static void finish(int sig);

int main(int argc, char const *argv[]) {
	// curses and others setup
	setlocale(LC_ALL, "");
    signal(SIGINT, finish);      /* arrange interrupts to terminate */
    initscr();       /* initialize the curses library */
    keypad(stdscr, TRUE);   /* enable keyboard mapping */
    nonl();          /* tell curses not to do NL->CR/NL on output */
    cbreak();        /* take input chars one at a time, no wait for \n */
    curs_set(0);     /* makes the cursor invisible */

    // initializations and setup
    int x, y;
    getmaxyx(stdscr, y, x);
    int level = 1;
    int gold = 0;
    int hp = STARTHP;
    int maxHp = STARTHP;
    int str = STARTSTR; // strength
    int maxStr = STARTSTR;
    int arm = STARTARM; // armor
    int exp = 0;
    int expLevel = 1;

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

    // -- examples --
    Point v;
    v.x = 10;
    v.y = 10;
    Room eg(v, 20, 10);

    Point vs[3];
    vs[0].x = 12;
    vs[0].y = 10;
    vs[1].x = 12;
    vs[1].y = 7;
    vs[2].x = 25;
    vs[2].y = 7;
    Hall way(vs, 3);
    // ---------------

    for (;;) {
    	// keyboard input
    	getch();

    	// game logic

    	// draw stuff
        eg.draw();
        way.draw();
        refresh();
    }

    finish(0);
	return 0;
}

Entity::Entity(int a, int b, int c, char d) {
	x = a;
	y = b;
	color = c;
	type = d;
}

void Entity::draw() {
	attrset(COLOR_PAIR(color));
	mvaddch(y, x, type);
}

Room::Room(Point a, int b, int c) {
    tl = a;
    dx = b;
    dy = c;
}

void Room::draw() {
    attrset(COLOR_PAIR(3));
    move(tl.y, tl.x);
    for (int i = 0; i < dx; i++)
        addch('-');
    for (int i = 1; i < dy - 1; i++) {
        move(tl.y + i, tl.x);
        addch('|');
        for (int j = 1; j < dx - 1; j++)
            addch('.');
        addch('|');
    }
    move(tl.y + dy - 1, tl.x);
    for (int i = 0; i < dx; i++)
        addch('-');
}

Hall::Hall(Point *v, int num) {
    vertNum = num;
    for (int i = 0; i < vertNum; i++)
        verts[i] = v[i];
}

void Hall::draw() {
    attrset(COLOR_PAIR(3));
    for (int i = 0; i < vertNum - 1; i++) {
        move(verts[i].y, verts[i].x);
        if (verts[i].y - verts[i+1].y == 0) { // is horizontal line?
            if (verts[i].x - verts[i+1].x > 0)
                for (int j = 0; j < verts[i].x - verts[i+1].x; j++)
                    mvaddch(verts[i].y, verts[i].x - j, '#');
            else 
                for (int j = 0; j < verts[i+1].x - verts[i].x; j++)
                    mvaddch(verts[i].y, verts[i].x + j, '#');
        }
        else { // vertical line
            if (verts[i].y - verts[i+1].y > 0)
                for (int j = 0; j < verts[i].y - verts[i+1].y; j++)
                    mvaddch(verts[i].y - j, verts[i].x, '#');
            else 
                for (int j = 0; j < verts[i+1].y - verts[i].y; j++)
                    mvaddch(verts[i].y + j, verts[i].x, '#');

        }
    }
}

static void finish(int sig) {
    endwin();
    exit(0);
}
