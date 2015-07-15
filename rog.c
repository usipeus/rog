#include <stdio.h>
#include <stdlib.h>

int* entities;

char* map;

// map related functions
void draw_map(char* m);
char* load_map(char* name, int height);
void replace_with_entities(char* map, int* entities);

// entity related functions
int* add_entity(int* e);
int move_entity(int id, int direction);

void game_setup();
void game_loop();

// map related functions
void draw_map(char* m) {
	for (i = 0; i < (sizeof(m) / sizeof(char); i++)
    {
        printf("%c", m[i]);
        if (i % MAP_LENGTH == 0)
            printf("\n");
    }
}

char* load_map(char* name, int height) {

}

void replace_with_entities(char* map, int* e) {
	for (

}

int main(int argc, char* argv[])
{
	game_setup();
	game_loop();
    return 0;
}
