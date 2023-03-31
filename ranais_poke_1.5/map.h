#ifndef MAP_H
#define MAP_H

#include "linked_list.h"


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

typedef struct map_struct
{
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
} map_t;

void map_init(map_t *map_pointer);

void map_print(map_t *map_pointer);

void recurse_terrain(map_t *map_pointer, int x, int y, int type);

void terrain_gen(map_t *map_pointer, int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2);

void path_gen(map_t *map_pointer, int distance);

void map_gen( map_t *map_pointer, int nmx, int smx, int emy, int wmy, int num_trainers);

void map_place_pc(map_t *map);

void map_djikstra(map_t *map, player_type type);

void simulate_movement(map_t *map_pointer);

//void npc_move(map_t *map_pointer, player_type type, int i, priority_queue_t pq);

#endif

