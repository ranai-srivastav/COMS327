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
#include <ctime>
#include "world.h"
#include "cstddef"
#include "cstdlib"
#include "ncurses.h"
#include <cmath>
#include "Pokemon.h"
#include <unistd.h>


void init(World *w, int num_trainers)
{
    int i=0, j=0;
    for(i = 0; i<401; i++)
    {
        for(j = 0; j<401; j++)
        {
            w->world[i][j] = nullptr;
        }
    }

    w->x = 200;
    w->y = 200;

    MapStruct *center = new MapStruct();
    w->world[200][200] = center;
    w->world[200][200]->w_y = w->world[200][200]->e_y = w->world[200][200]->n_x = w->world[200][200]->s_x = -1;
    map_gen(center, -1, -1, -1, -1, nullptr, num_trainers);
    w->bag["pokeballs"] = 5;
    w->bag["revive"] = 3;
    w->bag["elixir"] = 3;
}

MapStruct* get_north(World *w, int multiplier)
{
    return w->world[(w->y)-(1*multiplier)][(w->x)];
}

MapStruct* get_south(World *w, int multiplier)
{
    return w->world[(w->y)+(1*multiplier)][(w->x)];
}

MapStruct* get_east(World *w, int multiplier)
{
    return w->world[(w->y)][(w->x)+(1*multiplier)];
}

MapStruct* get_west(World *w, int multiplier)
{
    return w->world[(w->y)][(w->x)-(1*multiplier)];
}

void move_dir(World *w, int passed_y, int passed_x, point_t *new_player_pos, int num_trainers)
{
    w->x = passed_x;
    w->y = passed_y;

    if(w->world[passed_y][passed_x] == nullptr)
    {
        w->world[passed_y][passed_x] = new MapStruct();
        w->world[passed_y][passed_x]->w_y = w->world[passed_y][passed_x]->e_y = w->world[passed_y][passed_x]->n_x = w->world[passed_y][passed_x]->s_x = -1;
        MapStruct *center = w->world[passed_y][passed_x];
        center->player_pos = (point_t*)malloc(sizeof(point_t));

        int nmx = -2, smx = -2, emy = -2, wmy = -2;

        if(get_north(w, 1) != nullptr)
        {
            nmx = get_north(w, 1)->s_x;
        }
        if(get_south(w, 1) != nullptr)
        {
            smx = get_south(w, 1)->n_x;
        }
        if(get_west(w, 1) != nullptr)
        {
            emy = get_west(w, 1)->w_y;
        }
        if(get_east(w, 1) != nullptr)
        {
            wmy = get_east(w, 1)->e_y;
        }

        map_gen(center, nmx, smx, emy, wmy, new_player_pos, num_trainers);
    }
    else
    {
        map_print(w->world[passed_y][passed_x]);
    }
}

int is_movable(MapStruct *curr_map, int y, int x)
{
    return !(curr_map->map[y][x] == BOULDER ||
               curr_map->map[y][x] == TREE ||
               curr_map->map[y][x] == WALLS ||
               curr_map->map[y][x] == EXITS ||
               curr_map->players[y][x] == SENTRIES ||
               curr_map->players[y][x] == HIKER ||
               curr_map->players[y][x] == RIVAL);
}

char is_exiting(World* w, int curr_y, int curr_x)
{
    MapStruct *curr_map = w->world[w->y][w->x];
    point_t *player_pos = (point_t*) malloc(sizeof(point_t));

    if(curr_y == curr_map->e_y && curr_x == 0)          // left exit
    {
        w->x -= 1;
//        w->y;
        curr_x = 78;
//        curr_y = 78;

        player_pos->y = curr_y;
        player_pos->x = curr_x;
        move_dir(w, w->y, w->x, player_pos, 5);
        return 1;
    }
    else if(curr_y == 20 && curr_x == curr_map->s_x)    // bottom exit
    {
//        w->x -= 1;
        w->y -= 1;
//        curr_x = 78;
        curr_y = 1;
        player_pos->y = curr_y;
        player_pos->x = curr_x;
        move_dir(w, w->y, w->x, player_pos,5);
        return 2;
    }
    else if(curr_y == curr_map->e_y && curr_x == 79)    // right exit
    {
        w->x += 1;
//        w->y;
        curr_x = 1;
//        curr_y = 78;
        player_pos->y = curr_y;
        player_pos->x = curr_x;
        mvprintw(0, 0, "player_pos x=%d, y=%d", curr_x, curr_y);
        move_dir(w, w->y, w->x, player_pos,5);
        return 3;
    }
    else if(curr_y == 0 && curr_x == curr_map->n_x)    // up exit
    {
//        w->x -= 1;
        w->y += 1;
//        curr_x = 78;
        curr_y = 19;
        player_pos->y = curr_y;
        player_pos->x = curr_x;
        move_dir(w, w->y, w->x, player_pos,5);
        return 4;
    }
    else
    {
        return 0;
    }
}

bool move_pc(World *w, int in)
{
    MapStruct *curr_map = w->world[w->y][w->x];
    char const *ERROR = "CANNOT MOVE to req posn";
    int new_y = -1;
    int new_x = -1;

    switch(in)
    {
        case 52:
        case 'h': //Left
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
        srand(time(nullptr));

        is_exiting(w, new_y, new_x);
        curr_map->players[curr_map->player_pos->y][curr_map->player_pos->x] = NONE;
        curr_map->players[new_y][new_x] = PLAYER_CHARACTER;
        curr_map->player_pos->y = new_y;
        curr_map->player_pos->x = new_x;
        map_djikstra(curr_map, HIKER);
        map_djikstra(curr_map, RIVAL);

            if(curr_map->map[new_y][new_x] == TALL_GRASS)
        {
            if(rand()%100 < 85)
            {
                return true;
            }
        }
    }
    else
    {
        mvprintw(0, 0, "%s", ERROR);
    }
    refresh();

    return false;
}

void deinit(World *w)
{
    int i = 0, j = 0;
    for(i = 0; i<401; i++)
    {
        for(j = 0; j<401; j++)
        {
            if(w->world[i][j] != nullptr)
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