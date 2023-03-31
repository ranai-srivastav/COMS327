#ifndef MAP_H
#define MAP_H

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

typedef struct map_struct
{
    int map[21][80];
    point_t *player_pos;
    int dist[21][80];
    int n_x;
    int s_x;
    int e_y;
    int w_y;

} map_t;

typedef enum player
{
    PLAYER,
    RIVAL,
    HIKER,
} player_type;

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
    POKE_MART
} terrain_type;



#endif

