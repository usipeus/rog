#pragma once

#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENEMIES 256

#define MAX_MAPSIZE 80 * 25

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
	char tile;
} Enemy;

typedef struct {
	unsigned int hp;
	unsigned int mana;
	unsigned int location;
	unsigned int speed;
} Player;

typedef struct {
	unsigned int width;
	unsigned int height;
	char map[MAX_MAPSIZE + 1]; /* MAX_MAPSIZE tiles + '\0' */
	Enemy enemies[MAX_ENEMIES];
	Player player;
} Map;

void
Combat_damage_enemy(Map * m, unsigned int location, int dmg);

void
Combat_damage_player(Map * m, int dmg);

void
Enemy_add(Map * m, Enemy e);

void
Enemy_delete(Map * m, unsigned int id);

int
Enemy_getid(Map * m, unsigned int location);

void
Enemy_move(Map * m, Enemy e, enum directions dir);

void
Enemy_status(Enemy e, int id);

void
Player_status(Player p);

void
Player_move(Map * m, enum directions dir);

Map *
Map_create(int width, int height, char * map, Player player);

void
Map_draw(Map * m);

