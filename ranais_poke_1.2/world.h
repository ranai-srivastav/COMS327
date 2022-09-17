/**
 * @file world.h
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The struct defnition and abstract method signatures for the world
 * @version 2.4
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

typedef struct world_struct
{
    map_t* world[401][401];
    int x;
    int y;
} world_t;

void init(world_t *w);
void deinit();

map_t* get_north(world_t *w, int multiplier);
map_t* get_south(world_t *w, int multiplier);
map_t* get_east(world_t *w, int multiplier);
map_t* get_west(world_t *w, int multiplier);

void move_dir(world_t *w, int passed_y, int passed_x);