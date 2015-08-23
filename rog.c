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

	Map_draw(m);

	free(m);
}

void
game_loop()
{

}
