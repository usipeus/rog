#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rog.h"

struct entity {
	char tile;
	int location;
}

char * map;

// map related functions
void draw_map(char * map);
char * load_map(char * name, uint16_t height);
void replace_with_entities(char * map, char * entities, uint32_t * locations);

// entity related functions
uint32_t * add_entity(char * entities, uint32_t * locations);
uint32_t * del_entity(char * entities, uint32_t * locations);
uint32_t * move_entity(uint16_t id, uint32_t * locations, uint16_t dir);

// game functions
void game_setup();
void game_loop();

// main function
int main(int argc, char * argv[]) {
	// game_setup();
	// game_loop();

	return 0;
}

// map related functions
void draw_map(char * m) {
	uint32_t i;
	// print each character
	for (i = 0; i < (strlen(m)); i++) {
		printf("%c", m[i]);
		if ((i + 1) % MAP_WIDTH == 0)
			printf("\n");
	}
}
/*
char* load_map(char* name, uint16_t height) {

}
*/
void replace_with_entities() {

}
