#include "rog.h"

/* initialization */
Map * game_setup();
/* game logic, combat */
void game_loop(Map * m);

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

	Enemy enemy1 = {.blank = 0, .hp = 4, .location = 5, .tile = 'D'};
	Enemy_add(m, enemy1);

	return m;
}

void
game_loop(Map * m)
{
	Map_draw(m);

	Combat_damage_enemy(m, 5, 5);

	Map_draw(m);

	Player_status(m->player);
	Combat_damage_player(m, 3);
	Player_status(m->player);

	free(m);
}
