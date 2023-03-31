#ifndef MAP_H
#define MAP_H

#include "linked_list.h"
#include "IO_Pokemon.h"
#include "IO_moves.h"
#include "IO_pokemon_moves.h"
#include "IO_miscl.cpp"


/**
 * @file map.h
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The file that contains the structure definitions for the map struct
 * @version 2
 * @date 2022-09-28
 * 
 */

typedef struct point
{
    int x;
    int y;
} point_t;


typedef enum terrain
{
    CLEARING,
    TALL_GRASS,
    TREE,
    BOULDER,
    PATH,
    WALLS,
    EXITS,
    POKE_CENTER,
    POKE_MART,
    CHARACTER
} terrain_type;

typedef struct non_playable_character
{
    point_t *curr_pos;
    player_type type;
    point_t *vector;
} npc_t;

class MapStruct
{
public:
    int map[21][80];
    int players[21][80];
    int dist_hiker[21][80];
    int dist_rival[21][80];
    point_t *player_pos;
    int n_x;
    int s_x;
    int e_y;
    int w_y;
    int num_players;
    linked_list_t *player_positions;

    MapStruct()
    {

    }
};

void map_init(MapStruct *map_pointer);

void map_print(MapStruct *map_pointer);

void recurse_terrain(MapStruct *map_pointer, int x, int y, int type);

void terrain_gen(MapStruct *map_pointer, int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2);

void path_gen(MapStruct *map_pointer, int distance);

void map_gen( MapStruct *map_pointer, int nmx, int smx, int emy, int wmy, point_t *new_player_pos, int num_trainers);

void map_place_pc(MapStruct *map);

void map_djikstra(MapStruct *map, player_type type);

void simulate_movement(MapStruct *map_pointer);

//void npc_move(map_t *map_pointer, player_type type, int i, priority_queue_t pq);

#endif
