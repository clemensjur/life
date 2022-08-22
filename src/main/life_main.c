#include <stdlib.h>

#include "life_util.h"

int main() {

    // Initialize the map as 2-dimensional Array of FIELD_TYPE
    FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH];
    // Generate the map
    life_map_generate(map, rand() % 1000);

    life_init();
    life_run(map);

    return 0;
}


