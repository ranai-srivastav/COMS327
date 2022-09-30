#ifndef MAP_H
#define MAP_H

/**
 * @file map.h
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The file that contains the structure definitions for the map struct
 * @version 1.2
 * @date 2022-09-10
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

void map_init(map_t *map_pointer);

void map_print(map_t *map_pointer);

void recurse_terrain(map_t *map_pointer, int x, int y, int type);

void terrain_gen(map_t *map_pointer, int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2);

void path_gen(map_t *map_pointer, int distance);

void map_gen( map_t *map_pointer, int nmx, int smx, int emy, int wmy);

void map_place_pc(map_t *map);

void map_djikstra(map_t *map);

#endif

