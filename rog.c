#include "rog.h"

/* initialization */
void game_setup();
/* game logic, combat */
void game_loop();

int
main()
{
	game_setup();
	game_loop();

	return 0;
}

void
game_setup()
{
	Player player = {.hp = 10, .mana = 4, .location = 6, .speed = 2};
	Map * m = Map_create(4, 4, "#####..##..#####", player);

	Enemy enemy1 = {.blank = false, .hp = 4, .location = 5, .tile = 'D'};
	Enemy_add(m, enemy1);

	Map_draw(m);

	Enemy_delete(m, 5);

	Map_draw(m);

	free(m);
}

void
game_loop()
{

}
