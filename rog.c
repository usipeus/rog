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
	m.map = malloc ((m.height * m.width + 1) * sizeof(char));
	strcpy (m.map, "#####..##..#####");
	m.characters = malloc (3 * sizeof(char));
	strcpy(m.characters, "a@");
	m.locations = malloc (2 * sizeof(int));
	m.locations[0] = 5;
	m.locations[1] = 6;

	draw_map (m);
	
	free (m.map);
	free (m.characters);
	free (m.locations);
}

void
game_loop ()
{

}
