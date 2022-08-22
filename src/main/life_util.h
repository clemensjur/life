//
// Created by clemens on 08.09.20.
//

#ifndef LIFECLIENT_LIFE_UTIL_H
#define LIFECLIENT_LIFE_UTIL_H

typedef enum {
    WATER,
    DIRT,
    GRASS
} FIELD_TYPE;

extern const char FIELD;
extern const unsigned int MAP_HEIGHT;
extern const unsigned int MAP_WIDTH;

void life_init();
void life_run(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void life_map_draw(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH], unsigned int offsetX, unsigned int offsetY);
void life_map_generate(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH], int rand);
void life_map_print(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH]);

#endif //LIFECLIENT_LIFE_UTIL_H
