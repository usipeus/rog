struct entity {
	char tile;
	int location;
}

// map related functions
void draw_map(char * map);
char * load_map(char * name, uint16_t height);
void replace_with_entities(char * map, struct entity * entities);

// entity related functions
uint32_t * add_entity(struct entity * entities);
uint32_t * del_entity(struct entity * entities);
uint32_t * move_entity(struct entity * entities, uint32_t id, uint16_t dir);


void draw_map(char * m) {
	uint32_t i;
	// print each character
	for (i = 0; i < (strlen(m)); i++) {
		printf("%c", m[i]);
		if ((i + 1) % MAP_WIDTH == 0)
			printf("\n");
	}
}
