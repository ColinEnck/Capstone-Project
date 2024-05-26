# INCOMPLETE

import curses
from curses import wrapper

stdscr = curses.initscr()


class SnakePiece:
    def __init__(self, x: int, y: int, direction: str) -> None:
        self.x = x
        self.y = y
        self.direction = direction
    def __str__(self) -> str:
        return f"({self.x}, {self.y}); headed {self.direction}"
    def update(self) -> None:
        match self.direction:
            case "w":
                self.y -= 1
            case "a":
                self.x -= 1
            case "s":
                self.y += 1
            case "d":
                self.x += 1
    def draw(self) -> None:
        stdscr.addch(self.y, self.x, curses.ACS_BLOCK, curses.color_pair(1))

def main(stdscr):
    # initialize stuff here
    curses.start_color()
    curses.curs_set(0)
    curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)

    snake = []
    snake.append(SnakePiece(int(curses.COLS/2), int(curses.LINES/2), "w"))

    while True:
        # update stuff here
        c = stdscr.getch()
        if c == "q":
            break
        snake[0].direction = c
        for i in range(0, len(snake)):
            snake[i].update()
        
        # draw stuff here
        stdscr.clear()
        for i in range(0, len(snake)):
            snake[i].draw()

        stdscr.refresh()

wrapper(main)
