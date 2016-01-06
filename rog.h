#include "map.h"

#include <ncurses.h>
#include <stdio.h>

/* game initialization */
Map *
game_setup();

/* game logic */
void
game_loop(Map * m);

/* player input */
void
interpret_input(Map * m, char ch);

