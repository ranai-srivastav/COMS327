/**
 * @file world.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief keeps track of the current state of the world and the players location in the world
 * @version 2.4
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "map.c"
#include "world.h"

void init(world_t *w)
{
    int i=0, j=0;
    for(i = 0; i<401; i++)
    {
        for(j = 0; j<401; j++)
        {
            w->world[i][j] = NULL;
        }
    }

    w->x = 200;
    w->y = 200;

    w->world[200][200] = malloc(sizeof(map_t));
    w->world[200][200]->w_y = w->world[200][200]->e_y = w->world[200][200]->n_x = w->world[200][200]->s_x = -1;
    map_t *center = w->world[200][200];
    map_gen(center, -1, -1, -1, -1);
}

map_t* get_north(world_t *w, int multiplier)
{
    return w->world[(w->y)-(1*multiplier)][(w->x)];
}

map_t* get_south(world_t *w, int multiplier)
{
    return w->world[(w->y)+(1*multiplier)][(w->x)];
}

map_t* get_east(world_t *w, int multiplier)
{
    return w->world[(w->y)][(w->x)+(1*multiplier)];
}

map_t* get_west(world_t *w, int multiplier)
{
    return w->world[(w->y)][(w->x)-(1*multiplier)];
}

void move_dir(world_t *w, int passed_y, int passed_x)
{
    w->x = passed_x;
    w->y = passed_y;

    if(w->world[passed_y][passed_x] == NULL)
    {
        w->world[passed_y][passed_x] = malloc(sizeof(map_t));
        w->world[passed_y][passed_x]->w_y = w->world[passed_y][passed_x]->e_y = w->world[passed_y][passed_x]->n_x = w->world[passed_y][passed_x]->s_x = -1;
        map_t *center = w->world[passed_y][passed_x];

        int nmx = -2, smx = -2, emy = -2, wmy = -2;

        if(get_north(w, 1) != NULL)
        {
            nmx = get_north(w, 1)->s_x;
        }
        if(get_south(w, 1) != NULL)
        {
            smx = get_south(w, 1)->n_x;
        }
        if(get_west(w, 1) != NULL)
        {
            emy = get_west(w, 1)->w_y;
        }
        if(get_east(w, 1) != NULL)
        {
            wmy = get_east(w, 1)->e_y;
        }

        map_gen(center, nmx, smx, emy, wmy);
    }
    else
    {
        map_print(w->world[passed_y][passed_x]);
    }
}


void deinit(world_t *w)
{
    int i = 0, j = 0;
    for(i = 0; i<401; i++)
    {
        for(j = 0; j<401; j++)
        {
            free(w->world[i][j]->map);
            free(w->world[i][j]);
        }
        free(w->world[i]);
    }
    free(w);
}