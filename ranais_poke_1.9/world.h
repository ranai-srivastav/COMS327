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
#include <unordered_map>
//#include "Pokemon.h"
//#include "Pokemon.h"

class World
{
public:
    MapStruct* world[401][401];
    int x;
    int y;
    std::vector<IO_pokemon::IO_pokemon_struct*> csv_pokemon;
    std::vector<IO_moves::IO_moves_struct*> csv_moves;
    std::vector<IO_pokemon_moves::IO_pokemon_moves_struct*> csv_pokemon_moves;
    std::vector<IO_pokemon_species::IO_pokemon_species_struct*> csv_pokemon_species;
    std::vector<IO_experience::IO_experience_struct*> csv_experience;
    std::vector<IO_type_names::IO_type_names_struct*> csv_type_names;
    std::vector<IO_pokemon_stats::IO_pokemon_stats_struct*> csv_pokemon_stats;
    std::vector<IO_stats::IO_stats_struct*> csv_stats;
    std::vector<IO_pokemon_types::IO_pokemon_types_struct*> csv_pokemon_types;
    std::unordered_map<string, int> bag;

};

void init(World *w, int num_trainers);
void deinit(World *w);

MapStruct* get_north(World *w, int multiplier);
MapStruct* get_south(World *w, int multiplier);
MapStruct* get_east(World *w, int multiplier);
MapStruct* get_west(World *w, int multiplier);

bool move_pc(World *w, int in);
void move_dir(World *w, int passed_y, int passed_x, point_t *new_player_pos, int num_trainers);
#endif
