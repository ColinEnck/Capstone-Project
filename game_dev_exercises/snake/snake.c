#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <locale.h>
#define APLSIZ 25

struct SnakePiece 
{
    int x;
    int y;
    char dir;
    struct SnakePiece *next; 
};

struct Apple
{
    int x;
    int y;
};

void addSnakePiece(struct SnakePiece *snake, int x, int y);
void updateSnakePos(struct SnakePiece *snake);
void updateSnakeDir(struct SnakePiece *snake);
int hasHitApple(struct SnakePiece *snake, struct Apple *apples);
static void finish(int sig);

int main(int argc, char *argv[])
{
    // initializations
    struct SnakePiece *snake = (struct SnakePiece*) malloc(sizeof(struct SnakePiece));
    struct Apple *apples = (struct Apple*) malloc(sizeof(struct Apple) * APLSIZ);
    int winlines, wincols, c, x, y, temp;
    bool addPiece = FALSE;
    struct timespec timer;
    srand(time(0));

    // curses setup
    setlocale(LC_ALL, "");
    signal(SIGINT, finish);      /* arrange interrupts to terminate */
    initscr();       /* initialize the curses library */
    keypad(stdscr, TRUE);   /* enable keyboard mapping */
    nonl();          /* tell curses not to do NL->CR/NL on output */
    cbreak();        /* take input chars one at a time, no wait for \n */
    noecho();        /* disable echo */
    curs_set(0);     /* makes the cursor invisible */
    halfdelay(2);   // getch() waits 0.2 seconds if there is no input
    nodelay(stdscr, TRUE); 

    // definitions
    timer.tv_sec = 0;
    timer.tv_nsec = 100000000;
    getmaxyx(stdscr, winlines, wincols);
    snake->x =  wincols/2;
    snake->y = winlines/2;
    snake->dir = 'w';
    snake->next = NULL;
    for (int i = 0; i < APLSIZ; i++)
    {
        apples[i].x = rand() % wincols;
        apples[i].y = rand() % winlines;
    }
    

    if (has_colors())
    {
        start_color();

        /*
         * Simple color assignment, often all we need.  Color pair 0 cannot
         * be redefined.  This example uses the same value for the color
         * pair as for the foreground color, though of course that is not
         * necessary:
         */

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
        c = getch(); 
        if (c != ERR)
        {
            if (c == 'q')
                break;
            else switch (c){
                case 'w':
                    if (snake->dir != 's')
                        snake->dir = c;
                    break;
                case 'a':
                    if (snake->dir != 'd')
                        snake->dir = c;
                    break;
                case 's':
                    if (snake->dir != 'w')
                        snake->dir = c;
                    break;
                case 'd':
                    if (snake->dir != 'a')
                        snake->dir = c;
                    break;
            }
            nanosleep(&timer, NULL);
            flushinp();
        }
        
        // check if head of snake has hit apple
        temp = hasHitApple(snake, apples);
        if (temp != -1)
        {
            addPiece = TRUE;
            apples[temp].x = rand() % wincols;
            apples[temp].y = rand() % winlines;
            // saves the pos of the head of the snake
            struct SnakePiece *s = snake;
            while (s->next != NULL) s = s->next;
            x = s->x;
            y = s->y;
        }
        
        // updates each SnakePiece based on its dir
        updateSnakePos(snake);

        // adds new piece if needed
        if (addPiece) 
        {
            addSnakePiece(snake, x, y);
            addPiece = FALSE;
        }

        // snake pieces follow the one before them
        updateSnakeDir(snake);

        // --- Drawing stuff here ---

        // clears the screen
        clear();

        // paints the snake to the screen
        attrset(COLOR_PAIR(2));
        for (struct SnakePiece *s = snake; s != NULL; s = s->next)
            mvaddch(s->y, s->x, ACS_BLOCK);
        attrset(COLOR_PAIR(1));

        // paints the apple
        for (int i = 0; i < APLSIZ; i++)
            mvaddch(apples[i].y, apples[i].x, ACS_DIAMOND);
        
        refresh();
    }

    free(snake);

    finish(0);
}

void addSnakePiece(struct SnakePiece *snake, int x, int y)
{
    struct SnakePiece *s = snake;
    while (s->next != NULL) s = s->next;
    s->next = (struct SnakePiece*) malloc(sizeof(struct SnakePiece));
    s->next->x = x;
    s->next->y = y;
    s->next->dir = s->dir;
    s->next->next = NULL;
}

void updateSnakePos(struct SnakePiece *snake)
{ 
    for (struct SnakePiece *s = snake; s != NULL; s = s->next)
    {
        switch (s->dir) {
        case 'w':
            s->y--;
            break;
        case 'a':
            s->x--;
            break;
        case 's':
            s->y++;
            break;
        case 'd':
            s->x++;
            break;
        default:
            break;
        }
    }
}

void updateSnakeDir(struct SnakePiece *snake)
{
    char lastDir = snake->dir;
    char currentDir;
    for (struct SnakePiece *s = snake->next; s != NULL; s = s->next)
    {
        currentDir = s->dir;
        s->dir = lastDir;
        lastDir = currentDir;
    }
}

// returns index of apple hit, otherwise -1
int hasHitApple(struct SnakePiece *snake, struct Apple *apples)
{
    for (int i = 0; i < APLSIZ; i++)
        if (snake->x == apples[i].x && snake->y == apples[i].y)
            return i;
    return -1;
}

static void finish(int sig)
{
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
