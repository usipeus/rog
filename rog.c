#include "rog.h"

/* initialization */
Map * game_setup();
/* game logic, combat */
void game_loop();

int
main()
{
	Map * m = game_setup();
	game_loop(m);

	return 0;
}

Map *
game_setup()
{
	Player player = {.hp = 10, .mana = 4, .location = 6, .speed = 2};
	Map * m = Map_create(4, 4, "#####..##..#####", player);

	Enemy enemy1 = {.blank = false, .hp = 4, .location = 5, .tile = 'D'};
	Enemy_add(m, enemy1);

	return m;
}

void
game_loop(Map * m)
{
	Map_draw(m);

	Combat_damage(m, 5, 5);

	Map_draw(m);

	free(m);
}
