#pragma once

#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>
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
	uint8_t blank;
	uint8_t hp;
	uint16_t location;
	char tile;
} Enemy;

typedef struct {
	uint8_t hp;
	uint8_t mana;
	uint8_t speed;
	uint16_t location;
} Player;

typedef struct {
	uint8_t width;
	uint8_t height;
	char map[MAX_MAPSIZE + 1]; /* MAX_MAPSIZE tiles + '\0' */
	Enemy enemies[MAX_ENEMIES];
	Player player;
} Map;

Map *
Map_create(uint8_t width, uint8_t height, char * map, Player player);

void
Map_draw(Map * m);

int16_t
Map_offset(Map * m, enum directions dir);

void
Combat_damage_enemy(Map * m, uint16_t location, int8_t dmg);

void
Combat_damage_player(Map * m, int8_t dmg);

void
Enemy_add(Map * m, Enemy e);

int
Enemy_getid(Map * m, uint16_t location);

void
Enemy_delete(Map * m, uint8_t id);

void
Enemy_move(Map * m, Enemy e, enum directions dir);

void
Enemy_status(Enemy e, uint8_t id);

void
Player_status(Player p);

void
Player_move(Map * m, enum directions dir);
