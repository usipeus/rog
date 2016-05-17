#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_MAPSIZE
#define MAX_MAPSIZE 80 * 25
#endif /* MAX_MAPSIZE */

#ifndef MAX_ENEMIES
#define MAX_ENEMIES 256
#endif /* MAX_ENEMIES */

enum directions {
	UP_LEFT,
	UP,
	UP_RIGHT,
	LEFT,
	IN_PLACE,
	RIGHT,
	DOWN_LEFT,
	DOWN,
	DOWN_RIGHT
};

typedef struct {
	unsigned int blank;
	unsigned int hp;
	unsigned int location;
	unsigned int speed;		/* determines chance to get hit: 1 / (2 + speed) */
	unsigned int max_hit;	/* max damage possible in 1 hit */
	unsigned int AC;		/* armor class, determines how easily you are hit */
	char tile;
} Enemy;

typedef struct {
	unsigned int hp;
	unsigned int mana;
	unsigned int location;
	unsigned int speed;
	unsigned int max_hit;	/* max damage you can do in 1 hit */
	unsigned int AC;		/* armor class, determines how easily you are hit */
} Player;

typedef struct {
	unsigned int width;
	unsigned int height;
	char map[MAX_MAPSIZE + 1]; /* MAX_MAPSIZE tiles + '\0' */
	Enemy enemies[MAX_ENEMIES];
	Player player;
} Map;

/* game initialization */
Map *
game_setup();

/* game logic */
void
game_loop(Map * m);

/* player input */
void
interpret_input(Map * m, char ch);

/* player functions */
void
Player_status(Player p);

/* Enemy functions */
void
Enemy_add(Map * m, Enemy e);

int
Enemy_getid(Map * m, unsigned int location);

void
Enemy_delete(Map * m, unsigned int id);

void
Enemy_status(Enemy e, int id);

/* combat functions */
void
Combat_damage_enemy(Map * m, unsigned int location, int dmg);

void
Combat_damage_player(Map * m, int dmg);

/* movement functions */
void
Movement_player(Map * map, enum directions dir);

/* map functions */
Map *
Map_create(int width, int height, char * map, Player player);

void
Map_draw(Map * m);

