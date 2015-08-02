#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int width;
	unsigned int height;
	char * map;
	char * characters;
	unsigned int * locations;
} map;

/* map related functions */
void
draw_map (map * m);

map *
load_map ();

/* character related functions */
void
add_character (map * m,
	       char tile,
	       unsigned int loc);

void
del_character (map * m,
	       unsigned int id);

void
move_character (map * m,
		unsigned int id,
		int dir);

/* function definitions */

void
draw_map (map * m)
{
	unsigned int i, j;
	char * map_with_chars = malloc (strlen (m->map) * sizeof (char) + 1);
	strcpy (map_with_chars, m->map);

	/* replace the tiles in m.locations[] with a char from m.characters[] */
	printf("Num of chars to replace: %ld\n", strlen (m->characters));
	for (i = 0; i < strlen (m->characters); i++)
	{
		map_with_chars[(m->locations)[i]] = (m->characters)[i];
		printf("Replaced tile %i w/ char %c\n", i, (m->characters)[i]);
	}

	for (j = 0; j < strlen (map_with_chars); j++)
	{
		printf ("%c", map_with_chars[j]);

		if ((j + 1) % m->width == 0)
		{
			printf ("\n");
		}
	}

	free(map_with_chars);
}

void
add_character (map * m,
	       char tile,
	       unsigned int loc)
{

}

void
del_character (map * m,
	       unsigned int id)
{

}

void
move_character (map * m,
		unsigned int id,
		int dir)
{
	(m->locations)[id] += dir;
}
