#include "rog.h"

void game_setup();
void game_loop();

int
main ()
{
	game_setup();
	game_loop();

	return 0;
}

void
game_setup()
{
	map m;
	m.height = 4;
	m.width = 4;
	m.map = malloc ((m.height * m.width + 1) * sizeof (char));
	strcpy (m.map, "#####..##..#####");
	m.characters = malloc (5 * sizeof (char));
	strcpy (m.characters, "@aDc");
	m.locations = malloc(4 * sizeof (unsigned int));
	(m.locations)[0] = 5;
	(m.locations)[1] = 9;
	(m.locations)[2] = 10;
	(m.locations)[3] = 6;

	draw_map (&m);

	free (m.map);
	free (m.characters);
	free (m.locations);
}

void
game_loop ()
{

}
