#include "map.h"

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
Player_status(Player p)
{
	printf("Player\thp: %u\tmana: %u\tlocation: %u\tspeed: %u\n",
		p.hp, p.mana, p.location, p.speed
	);
}

void
Player_move(Map * m, enum directions dir)
{
	int offset = 0;

	switch (dir) {
		case DOWN_LEFT:
			offset = m->width - 1;
			break;

		case DOWN:
			offset = m->width;
			break;

		case DOWN_RIGHT:
			offset = m->width + 1;
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
			offset = -m->width - 1;
			break;

		case UP:
			offset = -m->width;
			break;

		case UP_RIGHT:
			offset = -m->width + 1;
			break;
	}

	/* find what is in the tile to move into */
	char new_loc = m->map[m->player.location + offset];

	if (new_loc == '#' || new_loc == ' ') {
		/* new_loc is a wall or out of bounds: don't move and display message */
	} else if (new_loc >= 'a' && new_loc - 'a' < 26) {
		/* new_loc is an enemy: attack */
	} else if (new_loc >= 'A' && new_loc - 'A' < 26) {
		/* new_loc is an enemy: attack */
	} else {
		m->player.location += offset;
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

