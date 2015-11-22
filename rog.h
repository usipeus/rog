#include <assert.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAPSIZE 80 * 25
#define MAX_ENEMIES 256

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

/* function definitions */
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
  
  if (map->map[map->player.location + offset] == '.') {
    map->player.location += offset;
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
	char * trunc_map = malloc(sizeof(char) * (1 + width * height));
	/* truncate map string */
	strcpy(trunc_map, map);
	trunc_map[width * height] = '\0';
	/* copy it over */
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

	clear();

	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (m->enemies[i].blank == 0) {
			map_with_chars[m->enemies[i].location] =
				m->enemies[i].tile;
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

void
Player_status(Player p)
{
	printf("Player\thp: %u\tmana: %u\tlocation: %u\tspeed: %u\n",
			p.hp,
			p.mana,
			p.location,
			p.speed);
}
