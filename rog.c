#include "rog.h"

int
main()
{
	uint8_t rows, cols;
	/* initialize ncurses stuff */
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);

	printw("Starting game...\n");

	/* check dimensions of the screen */
	getmaxyx(stdscr, rows, cols);
	if (rows < 90 || cols < 30) {
		printw("Your terminal is not 90x30 (width x height) or larger.\n");
		printw("You may experience graphical bugs.\n\n");
	}

	printw("Movement:\n");
	printw("7  8  9			y  k  u\n");
	printw(" \\ | /			 \\ | /\n");
	printw("4  5  6		or	h     l\n");
	printw(" / | \\			 / | \\\n");
	printw("1  2  3			b  j  n\n");
	printw("Other actions:\n");
	printw("Inventory: i\tExamine: e\tQuit: q\n");
	refresh();

	getch();

	/* set up and start game */
	Map * m = game_setup();

	clear();
	Map_draw(m);
	refresh();

	game_loop(m);

	printw("\nGoodbye!\n");
	refresh();
	getch();

	free(m);
	endwin();

	return 0;
}

Map *
game_setup()
{
	Player player = {.hp = 10, .mana = 4, .location = 746, .speed = 2};
	Map * m = Map_create(79, 20, "###############                                                   ##############.............#                                                   #...........##.............#########                                           #...........##.....................#                        ###                #...........##.....................#                       #...#               #...........##.............######..#                       #....##             #...........#########.###########..##########              #.....#             #...........#.........########..............###            #.....#             #...........#.#################...............##############.....###############...........#.#               ##...........................................................#.#                ##.................##############################...........#.#                 ##..................#                          #...........#.#                  #######.############                          #...........#.#                        #.#                                     #...........#.#                        #.#                                     #...........#.#                        #.#                                     #...........#.##########################.#                                     #...........#............................#                                     #...........#............................#                                     #...........################################################################################", player);

	Enemy enemy1 = {.blank = 0, .hp = 4, .location = 708, .tile = 'D'};
	Enemy_add(m, enemy1);

	return m;
}

void
game_loop(Map * m)
{
	uint32_t turns = 0;
	char input;

	while (1)
	{
		input = getch();
		if (input == 'q') {
			printw("Are you sure you want to quit? (y/N) ");
			refresh();
			input = getch();
			if (input == 'y' || input == 'Y') {
				return;
			}
		} else {
			interpret_input(m, input);
			clear();
			Map_draw(m);
			turns++;
			printw("Turns: %d\n", turns);
			refresh();
		}

		if (turns % 2 == 0) {
			Enemy_move(m, m->enemies[0], LEFT);
		}
	}
}

void
interpret_input(Map * m, char input)
{
	enum directions dir = IN_PLACE;
	/* movement */
	switch (input) {
		case 'h':
			dir = LEFT;
			break;
		case 'j':
			dir = DOWN;
			break;
		case 'k':
			dir = UP;
			break;
		case 'l':
			dir = RIGHT;
			break;
		case 'y':
			dir = UP_LEFT;
			break;
		case 'u':
			dir = UP_RIGHT;
			break;
		case 'b':
			dir = DOWN_LEFT;
			break;
		case 'n':
			dir = DOWN_RIGHT;
			break;
	}

	Player_move(m, dir);

	/* inventory */
	if (input == 'i') {
	}

	/* examining something */
	if (input == 'e') {
	}

	/* show help */
	if (input == KEY_F(1)) {
	}

}

