//#ifndef WORLD_H
//#define WORLD_H

/**
 * @file world.h
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The struct defnition and abstract method signatures for the world
 * @version 2
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "map.h"

typedef struct world_struct
{
    map_t* world[401][401];
    int x;
    int y;
} world_t;

void init(world_t *w, int num_trainers);
void deinit(world_t *w);

map_t* get_north(world_t *w, int multiplier);
map_t* get_south(world_t *w, int multiplier);
map_t* get_east(world_t *w, int multiplier);
map_t* get_west(world_t *w, int multiplier);

void move_dir(world_t *w, int passed_y, int passed_x, int num_trainers);

//#endif
