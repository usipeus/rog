#include "rog.h"
#include <math.h>
#include <time.h>

int
main()
{
	int rows, cols;
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
	printw("Inventory: i\tExamine: e\n");
	refresh();

	getch();

	/* seed rand */
	srand(time(NULL));

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
	Player player = {
		.hp = 10,
		.mana = 4,
		.location = 746,
		.speed = 2,
		.max_hit = 4,
		.AC = 12,
	};

	Map * m = Map_create(79, 20, "###############                                                   ##############.............#                                                   #...........##.............#########                                           #...........##.....................#                        ###                #...........##.....................#                       #...#               #...........##.............######..#                       #....##             #...........#########.###########..##########              #.....#             #...........#.........########..............###            #.....#             #...........#.#################...............##############.....###############...........#.#               ##...........................................................#.#                ##.................##############################...........#.#                 ##..................#                          #...........#.#                  #######.############                          #...........#.#                        #.#                                     #...........#.#                        #.#                                     #...........#.#                        #.#                                     #...........#.##########################.#                                     #...........#............................#                                     #...........#............................#                                     #...........################################################################################", player);

	Enemy enemy1 = {
		.blank = 0,
		.hp = 16,
		.location = 708,
		.speed = 2,
		.max_hit = 6,
		.AC = 14,
		.tile = 'D'
	};

	Enemy_add(m, enemy1);

	return m;
}

void
game_loop(Map * m)
{
	char ch;

	while (1)
	{
		ch = getch();
		if (ch == 'Q') {
			printw("Are you sure you want to quit? (y/N) ");
			refresh();
			ch = getch();
			refresh();
			if (ch == 'y' || ch == 'Y') {
				return;
			}
		} else {
			interpret_input(m, ch);
			clear();
			Map_draw(m);
			refresh();
		}
	}
}

void
interpret_input(Map * m, char ch)
{
	enum directions dir = IN_PLACE;
	/* movement */
	switch (ch) {
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

	Movement_player(m, dir);

	/* inventory */
	if (ch == 'i') {
	}

	/* examining something */
	if (ch == 'e') {
	}

	/* help */
	if (ch == KEY_F(1)) {
	}

}

/* function definitions */
void
Player_status(Player p)
{
	printf("Player\thp: %u\tmana: %u\tlocation: %u\tspeed: %u\n",
		p.hp, p.mana, p.location, p.speed
	);
}

void
Enemy_add(Map * m, Enemy e)
{
	int i;
	unsigned int first_blank = -1;
	for (i = 0; i < MAX_ENEMIES; i++) {
		/* find first blank spot */
		if (m->enemies[i].blank == 1) {
			first_blank = i;
			break;
		}
	}

	m->enemies[first_blank] = e;

	/* error: first_blank is -1 if no blank slots */
	if (first_blank == -1) {
		/* print error */
	}
}

int
Enemy_getid(Map * m, unsigned int location)
{
	/* find id using linear search; if id doesn't exist, return -1 */
	int i, id = -1;
	for (i = 0; i < MAX_ENEMIES; i++) {
		if (m->enemies[i].location == location) {
			id = i;
			break;
		}
	}

	return id;
}

void
Enemy_delete(Map * m, unsigned int id)
{
	/* set that enemy to blank */
	if (id != -1) {
		Enemy e = {.blank = 1};
		m->enemies[id] = e;
	}
}

void
Enemy_status(Enemy e, int id)
{
	printf("tile:%c\t id: %i\t hp: %i\t loc: %i\n",
			e.tile,
			id,
			e.hp,
			e.location);
}

void
Combat_damage_enemy(Map * m, unsigned int location, int dmg)
{
	int id = Enemy_getid(m, location);

	if (id == -1) {
		/* error, enemy not found */
	} else {
		/* delete if dead, else subtract from hp */
		if (m->enemies[id].hp <= dmg) {
			Enemy_delete(m, id);
		} else {
			m->enemies[id].hp -= dmg;
		}
	}
}

void
Combat_damage_player(Map * m, int dmg)
{
	/* delete if dead, else subtract from hp */
	if (m->player.hp <= dmg) {
		/* game over */
	} else {
		m->player.hp -= dmg;
	}
}

void
Movement_player(Map * map, enum directions dir)
{
	int offset = 0;

	switch (dir) {
		case DOWN_LEFT:
			offset = map->width - 1;
			break;

		case DOWN:
			offset = map->width;
			break;

		case DOWN_RIGHT:
			offset = map->width + 1;
			break;

		case LEFT:
			offset = -1;
			break;

		case IN_PLACE:
			offset = 0;
			break;

		case RIGHT:
			offset = 1;
			break;

		case UP_LEFT:
			offset = -map->width - 1;
			break;

		case UP:
			offset = -map->width;
			break;

		case UP_RIGHT:
			offset = -map->width + 1;
			break;
	}

	unsigned int new_loc = map->player.location + offset;

	/* check to see if there are any enemies in the new location; if so, atk */
	int i, enemy_there = 0;
	for (i = 0; i < MAX_ENEMIES; i++) {
		if (!(map->enemies[i].blank) && (map->enemies[i].location == new_loc)) {
			enemy_there = 1;

			/* calculate damage to the enemy */
			unsigned int hit_roll = rand() % 20 + 1; /* roll 1d20 */
			if (hit_roll >= map->enemies[i].AC) {
				Combat_damage_enemy(map, new_loc, 
					rand() % map->player.max_hit + 1);
			}

			break;
		}
	}

	/* no enemy; try to move */
	if (!enemy_there) {
		/* find what is in the tile to move into */
		char new_tile = map->map[new_loc];

		if (new_tile == '#' || new_tile == ' ') {
			/* new_tile is a wall or out of bounds: don't move */
		} else {
			map->player.location += offset;
		}
	}
}

Map *
Map_create(int width, int height, char * map, Player player)
{
	assert (width <= 80);
	assert (height <= 25);

	int i = 0;

	Map * m = malloc(sizeof(Map));

	/* initialize enemies, all blank */
	for (i = 0; i < MAX_ENEMIES; i++) {
		Enemy e = {.blank = 1};
		m->enemies[i] = e;
	}

	/* set player */
	m->player = player;

	/* set width and height */
	m->width = width;
	m->height = height;

	/* set map */
	char trunc_map[sizeof(char) * (1 + width * height)];
	/* truncate map string */
	strcpy(trunc_map, map);
	trunc_map[width * height] = '\0';
	/* copy it over */
	strcpy(m->map, trunc_map);

	return m;
}

void
Map_draw(Map * m)
{
	unsigned int i, j;
	int area = m->width * m->height;
	char map_with_chars[area + 1];
	strcpy(map_with_chars, m->map);
	map_with_chars[area] = '\0';

	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (m->enemies[i].blank == 0) {
			map_with_chars[m->enemies[i].location] =
				m->enemies[i].tile;
		}

		map_with_chars[m->player.location] = '@';
	}

	/* print the map to the screen, character by character */
	for (j = 0; j < area; j++)
	{
		addch(map_with_chars[j]);

		if ((j + 1) % m->width == 0)
		{
			addch('\n');
		}
	}

}

