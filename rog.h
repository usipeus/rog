#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAPSIZE 80 * 25
#define MAX_ENEMIES 256

typedef struct {
	bool blank;
	unsigned int hp;
	unsigned int location;
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
	Enemy enemies[MAX_CHARS];
	Player player;
} Map;

/* map related functions */
void
draw_map(map * m);

map *
load_map(FILE * file);

/* character related functions */
void
add_character(map * m, char * tile, unsigned int loc);

void
del_character(map * m, unsigned int id);

void
move_character(map * m, unsigned int id, int dir);

/* function definitions */

void
draw_map(map * m)
{
	unsigned int i, j;
	char * map_with_chars = malloc(strlen(m->map) * sizeof(char) + 1);
	strcpy(map_with_chars, m->map);

	for (i = 0; i < strlen(m->characters); i++)
	{
		map_with_chars[(m->locations)[i]] = (m->characters)[i];
	}

	for (j = 0; j < strlen(map_with_chars); j++)
	{
		printf("%c", map_with_chars[j]);

		if ((j + 1) % m->width == 0)
		{
			printf("\n");
		}
	}

	free(map_with_chars);
}

void
add_character(map * m, char * tile, unsigned int loc)
{

}

void
del_character(map * m, unsigned int id)
{

}

void
move_character(map * m, unsigned int id, int dir)
{

}
