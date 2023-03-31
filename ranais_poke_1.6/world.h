#ifndef WORLD_H
#define WORLD_H

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

class World
{
public:
    MapStruct* world[401][401];
    int x;
    int y;
};

void init(World *w, int num_trainers);
void deinit(World *w);

MapStruct* get_north(World *w, int multiplier);
MapStruct* get_south(World *w, int multiplier);
MapStruct* get_east(World *w, int multiplier);
MapStruct* get_west(World *w, int multiplier);

void move_pc(World *w, int in);
void move_dir(World *w, int passed_y, int passed_x, point_t *new_player_pos, int num_trainers);

#endif
