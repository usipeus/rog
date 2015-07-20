#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int width;
	unsigned int height;
	char * map;
	char * characters;
	unsigned int * locations;
} map;

// map related functions
void draw_map(map m);
map * load_map();

// entity related functions
void add_character();
void del_character();
void move_character();

void draw_map(map m) {
	unsigned int i, j;
	char to_print;
	for (i = 0; i < strlen(m.map); i++) {
		for (j = 0; j < strlen(m.characters); j++) {
			if (m.locations[j] == i)
				to_print = m.characters[j];
			else
				to_print = m.map[i];
		}

		printf("%c", to_print);

		if ((i + 1) % m.width == 0)
			printf("\n");
	}
}
