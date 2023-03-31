/**
 * @file world.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief keeps track of the current state of the world and the players location in the world
 * @version 2
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <time.h>
#include "world.h"
#include "stddef.h"
#include "stdlib.h"
#include "ncurses.h"

void init(world_t *w, int num_trainers)
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
    map_gen(center, -1, -1, -1, -1, num_trainers);
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

void move_dir(world_t *w, int passed_y, int passed_x, int num_trainers)
{
    w->x = passed_x;
    w->y = passed_y;

    if(w->world[passed_y][passed_x] == NULL)
    {
        w->world[passed_y][passed_x] = malloc(sizeof(map_t));
        w->world[passed_y][passed_x]->w_y = w->world[passed_y][passed_x]->e_y = w->world[passed_y][passed_x]->n_x = w->world[passed_y][passed_x]->s_x = -1;
        map_t *center = w->world[passed_y][passed_x];
        center->player_pos = malloc(sizeof(point_t));

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

        map_gen(center, nmx, smx, emy, wmy, num_trainers);
    }
    else
    {
        map_print(w->world[passed_y][passed_x]);
    }
}

int is_movable(map_t *curr_map, int y, int x)
{
    return !(curr_map->map[y][x] == BOULDER ||
               curr_map->map[y][x] == TREE ||
               curr_map->map[y][x] == WALLS ||
               curr_map->players[y][x] == SENTRIES ||
               curr_map->players[y][x] == HIKER ||
                curr_map->players[y][x] == RIVAL);
}

void move_pc(world_t *w, int in)
{
    map_t *curr_map = w->world[w->y][w->x];
    char *ERROR = "CANNOT MOVE to req posn";
    int new_y = -1;
    int new_x = -1;

    switch(in)
    {
        case 52:
        case 'h': //Left
//            if(curr_map->player_pos->x - 1 != 0 && is_movable(curr_map, curr_map->player_pos->y, curr_map->player_pos->x - 1))
            if(is_movable(curr_map, curr_map->player_pos->y, curr_map->player_pos->x - 1))
            {
                new_y = curr_map->player_pos->y;
                new_x = curr_map->player_pos->x - 1;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving Left", new_x, new_y);
            }
        break;

        case 54:
        case 'l': // Right
//            if(curr_map->player_pos->x + 1 != 80 && is_movable(curr_map, curr_map->player_pos->y, curr_map->player_pos->x + 1))
            if(is_movable(curr_map, curr_map->player_pos->y, curr_map->player_pos->x + 1))
            {
                new_y = curr_map->player_pos->y;
                new_x = curr_map->player_pos->x + 1;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving Right", new_x, new_y);
            }
        break;

        case 50:
        case 'j': //Down
            if(is_movable(curr_map, curr_map->player_pos->y + 1, curr_map->player_pos->x))
            {
                new_y = curr_map->player_pos->y + 1;
                new_x = curr_map->player_pos->x;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving down", new_x, new_y);
            }
        break;

        case 56:
        case 'k': //Up
            if(is_movable(curr_map, curr_map->player_pos->y - 1, curr_map->player_pos->x))
            {
                new_y = curr_map->player_pos->y - 1;
                new_x = curr_map->player_pos->x;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving Up", new_x, new_y);
            }
        break;

        case 55:
        case 'y': //upper left
            if(is_movable(curr_map, curr_map->player_pos->y - 1, curr_map->player_pos->x - 1))
            {
                new_y = curr_map->player_pos->y - 1;
                new_x = curr_map->player_pos->x - 1;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving UL", new_x, new_y);
            }
        break;

        case 57:
        case 'u': //upper right
            if(is_movable(curr_map, curr_map->player_pos->y - 1, curr_map->player_pos->x + 1))
            {
                new_y = curr_map->player_pos->y + 1;
                new_x = curr_map->player_pos->x - 1;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving UR", new_x, new_x);
            }
        break;

        case 51:
        case 'n': //lower right
            if(is_movable(curr_map, curr_map->player_pos->y + 1, curr_map->player_pos->x + 1))
            {
                new_y = curr_map->player_pos->y + 1;
                new_x = curr_map->player_pos->x + 1;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving LR", new_x, new_y);
            }
        break;

        case 49:
        case 'b': //lower left
            if(is_movable(curr_map, curr_map->player_pos->y + 1, curr_map->player_pos->x - 1))
            {
                new_y = curr_map->player_pos->y + 1;
                new_x = curr_map->player_pos->x - 1;
//                clr_line(0,0);
//                mvprintw(0, 0, "At (%d, %d) moving left", new_x, new_y);
            }
        break;

        case 53:
        case 32:
        case 46:
        break;
    }

    if(new_y != -1 && new_x != -1)
    {
        curr_map->players[curr_map->player_pos->y][curr_map->player_pos->x] = NONE;
        curr_map->players[new_y][new_x] = PLAYER_CHARACTER;
        curr_map->player_pos->y = new_y;
        curr_map->player_pos->x = new_x;
        map_djikstra(curr_map, HIKER);
        map_djikstra(curr_map, RIVAL);
    }
    else
    {
        mvprintw(0, 0, "%s", ERROR);
    }

    refresh();
}


void deinit(world_t *w)
{
    int i = 0, j = 0;
    for(i = 0; i<401; i++)
    {
        for(j = 0; j<401; j++)
        {
            if(w->world[i][j] != NULL)
            {
//                free(w->world[i][j]->map);
//                free(w->world[i][j]->dist);
//                free(w->world[i][j]->player_pos);
                free(w->world[i][j]);
            }
        }
//        free(w->world[i]);
    }
    free(w);
}