#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAPSIZE 80 * 25
#define MAX_ENEMIES 256

typedef struct {
	bool blank;
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

/* map related functions */
Map *
Map_create(int width, int height, char * map, Player player);

void
Map_draw(Map * m);

/* combat functions */
void
Combat_damage(unsigned int id, int damage);

/* function definitions */
Map *
Map_create(int width, int height, char * map, Player player)
{
	int i = 0;

	Map * m = malloc(sizeof(Map));

	/* initialize enemies, all blank */
	for (i = 0; i < MAX_ENEMIES; i++) {
		Enemy e = {.blank = true};
		m->enemies[i] = e;
	}

	/* set player */
	m->player = player;

	/* set width and height */
	m->width = width;
	m->height = height;

	/* set map */
	char * trunc_map = malloc(sizeof(char) * (1 + width * height));
	// truncate map string
	strcpy(trunc_map, map);
	trunc_map[width * height] = '\0';
	// copy it over
	strcpy(m->map, trunc_map);

	free(trunc_map);
	return m;
}

void
Map_draw(Map * m)
{
	unsigned int i, j;
	int area = m->width * m->height;
	char * map_with_chars = malloc(area + 1);
	strcpy(map_with_chars, m->map);
	map_with_chars[area] = '\0';

	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (!m->enemies[i].blank) {
			map_with_chars[m->enemies[i].location] = m->enemies[i].tile;
		}

		map_with_chars[m->player.location] = '@';
	}

	for (j = 0; j < area; j++)
	{
		printf("%c", map_with_chars[j]);

		if ((j + 1) % m->width == 0)
		{
			printf("\n");
		}
	}

	free(map_with_chars);
}
