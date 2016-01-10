#pragma once

#include "map.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>

/* game initialization */
Map *
game_setup();

/* game logic */
void
game_loop(Map * m);

/* player input */
void
interpret_input(Map * m, char ch);

