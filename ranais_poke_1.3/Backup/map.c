/**
 * @file map.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The file that generates a map, terrain, paths, etc
 * @version 3.1
 * @date 2022-09-07
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "priority_queue.h"



void map_init(map_t *map_pointer)
{
    int i, j;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 80; j++) {
            map_pointer->map[i][j] = 0;
        }
    }

    i = 0, j = 0;
    for (i = 0; i < 80; i++) {
        map_pointer->map[0][i] = 6;
        map_pointer->map[20][i] = 6;
    }

    for (i = 0; i < 21; i++) {
        map_pointer->map[i][0] = 6;
        map_pointer->map[i][79] = 6;
    }

}

void map_print(map_t *map_pointer)
{
    int i, j;
    for(i = 0; i<80; i++)
    {
        printf("%d", i%10);
    }
    printf("\n");
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            // if(map[i][j] == 1) printf("%d", map[i][j]);

            if (map_pointer->map[i][j] > -5 && map_pointer->map[i][j] < 0) printf("%c", ':');
            else if (map_pointer->map[i][j] > -10 && map_pointer->map[i][j] < 0) printf("%c", '^');
            else if (map_pointer->map[i][j] == 6) printf("%c", '%');
            else if (map_pointer->map[i][j] == 2) printf("%c", '#');
            else if (map_pointer->map[i][j] == 8) printf("%c", 'M');
            else if (map_pointer->map[i][j] == 9) printf("%c", 'C');
            else if (map_pointer->map[i][j] == 5) printf("%c", '@');
            else printf("%c", '.');
        }
        printf("\n");
    }
}

void map_print_dists(map_t *map_pointer)
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            if((map_pointer->dist[i][j])%10 != 9)
            {
                printf("%02d ", (map_pointer->dist[i][j]) % 100);
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void recurse_terrain(map_t *map_pointer, int x, int y, int type)
{
    if (map_pointer->map[y][x] <= 0 && map_pointer->map[y][x] > -9)
    {
        map_pointer->map[y][x] = map_pointer->map[y][x] - 1;
    }
    else
    {
        map_pointer->map[y][x] += 8;
        if (x < 79 && y > 2)
            recurse_terrain(map_pointer, x + 1, y - 1, type);
        if (x < 70)
            recurse_terrain(map_pointer, x + 1, y, type);
        if (x < 79 && y < 16)
            recurse_terrain(map_pointer, x + 1, y + 1, type);
        if (y > 10)
            recurse_terrain(map_pointer, x, y - 1, type);
        if (x < 78 && y > 2 && y < 19)
            recurse_terrain(map_pointer, x, y + 1, type);
        if (x > 2 && y > 2)
            recurse_terrain(map_pointer, x - 1, y - 1, type);
        if (x > 2)
            recurse_terrain(map_pointer, x - 1, y, type);
        if (x > 2 && x < 72 && y > 2 && y < 10)
            recurse_terrain(map_pointer, x - 1, y + 1, type);
    }
}

void terrain_gen(map_t *map_pointer, int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2)
{
    int count = 0;
    map_pointer->map[treey][treex] = -1;
    for (count = 0; count < 6000; count++) {
        recurse_terrain(map_pointer, treex, treey, -5);
        recurse_terrain(map_pointer, grassx, grassy, -5);
        recurse_terrain(map_pointer, x1, y1, -5);
        recurse_terrain(map_pointer, x2, y2, -5);
        recurse_terrain(map_pointer, grassx, y2, -5);
        recurse_terrain(map_pointer, x2, treey, -5);
        // map_print_nums(map);
    }
}

void path_gen(map_t *map_pointer, int distance)
{
    int top, right;
    int Cx = rand() % 70 + 2, Mx = rand() % 70 + 2;
    int Cy = rand() % 15 + 2, My = rand() % 15 + 2;

    My = My + 0;
    Cx = Cx + 0;

    int choose = rand() % 2;

    int x = 0, y = 0;
    top = map_pointer->n_x; // should be the same as s_x
    for (y = 0; y < 21; y += 1)
    {
        map_pointer->map[y][top] = 2;
        if (y == Cy)
        {
            if (choose)
            {
                map_pointer->map[y][top + 1] = 8;
                map_pointer->map[y][top + 2] = 8;
            }
            else
            {
                map_pointer->map[y][top + 1] = 9;
                map_pointer->map[y][top + 2] = 9;
            }
        }
    }

    right = map_pointer->e_y;
    x = 0, y = 0;
    for (x = 0; x < 80; x += 1)
    {
        map_pointer->map[right][x] = 2;
        if (x == Mx)
        {
            if (choose)
            {
                map_pointer->map[right + 1][x] = 9;
                map_pointer->map[right + 2][x] = 9;
            }
            else
            {
                map_pointer->map[right + 1][x] = 8;
                map_pointer->map[right + 2][x] = 8;
            }
        }
    }
}

/**
 * Distance Table
 *  % 1,000  not passible  (greatest cost)*500
 *  Terr   PC   Hiker   Rival
 *  .      10    10     10
 *  ^      inf   inf    inf
 *  :      20    15     20
 *  #      10    10     10
 *  M      10    50     50
 *  C      10    50     50
 * @param map
 * @param point the point whose weight to return
 */
int get_weight(map_t *map, point_t *point, player_type type)
{
    if(type == RIVAL)
    {
        if (map->map[point->y][point->x] > -5 && map->map[point->y][point->x] < 0) //GRASS
        {
            return 20;
        }
        else if (map->map[point->y][point->x] > -10 && map->map[point->y][point->x] < 0) //TREE
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == 6) //BOULDER
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == 2) //PATH
        {
            return 10;
        }
        else if (map->map[point->y][point->x] == 8) //MART
        {
            return 50;
        }
        else if (map->map[point->y][point->x] == 9) //CENTER
        {
            return 50;
        }


        return 10;
    }

    else if(type == HIKER)
    {
        if (map->map[point->y][point->x] > -5 && map->map[point->y][point->x] < 0) //GRASS
        {
            return 15;
        }
        else if (map->map[point->y][point->x] > -10 && map->map[point->y][point->x] < 0) //TREE
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == 6) //BOULDER
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == 2) //PATH
        {
            return 10;
        }
        else if (map->map[point->y][point->x] == 8) //MART
        {
            return 50;
        }
        else if (map->map[point->y][point->x] == 9) //CENTER
        {
            return 50;
        }
        return 10;
    }

    return 10;
}

void map_djikstra(map_t *map, player_type type)
{

    point_t *player_pos_backup = malloc(sizeof(point_t));
    player_pos_backup->y = map->player_pos->y;
    player_pos_backup->x = map->player_pos->x;

    int i = 0, j = 0;
    const char delta[3] = {-1, 0, 1};
    point_t *node;

    for (i = 0; i < 21; ++i)
    {
        for(j = 0; j<80; ++j)
        {
            map->dist[i][j] = -1;
        }
    }

    priority_queue_t *pq = malloc(sizeof(priority_queue_t));
    priority_q_init(pq, map->player_pos, 0);

    int curr_y = map->player_pos->y;
    int curr_x = map->player_pos->x;
    map->dist[curr_y][curr_x] = 00;
    point_t *enq;


    while(!isEmpty(pq))
    {
        node = peek(pq);
        curr_x = node->x;
        curr_y = node->y;
        i = 0, j = 0;
        for(i = 0; i<3; i++)
        {
            for(j = 0; j<3; j++)
            {
                int new_y = curr_y + delta[i];
                int new_x = curr_x + delta[j];
                if(new_y < 0 || new_y > 20 || new_x > 79 || new_x < 0)
                {
                    continue;
                }

                if(map->dist[new_y][new_x] == -1)
                {
                    enq = malloc(sizeof(point_t));
                    enq->y = new_y;
                    enq->x = new_x;
                    map->dist[new_y][new_x] = map->dist[curr_y][curr_x] + get_weight(map, enq, type);
                    push(pq, enq, get_weight(map, enq, type));
//                    free(enq);
                }
                else
                {
                    int k = 0, l = 0;
                    for(k = 0; k<3; k++)
                    {
                        for (l = 0; l < 3; l++)
                        {
                            point_t *p = malloc(sizeof(point_t));
                            p->x = new_x + delta[j];
                            p->y = new_y + delta[l];
                            if((map->dist[p->y][p->x] > map->dist[new_y][new_x] + get_weight(map, p, type)))
                            {
                                map->dist[p->y][p->x] = map->dist[new_y][new_x] + get_weight(map, p, type);
                            }
                        }
                    }
                }
            }
        }
        pop(pq);
        map->player_pos = player_pos_backup;
    }
    printf(" ");
}

//TODO Check terrain type for !path for CC and MM

void map_place_pc(map_t *map)
{
    do
    {
        int px = rand()%70 + 5;
        int py = rand()%15 + 3;

        if(map->map[py][px] == 2)
        {
            map->map[py][px] = 5;

            map->player_pos->x = px;
            map->player_pos->y = py;
            break;
        }
    }while(1);
}


void map_gen( map_t *map_pointer, int nmx, int smx, int emy, int wmy)
{
    int distance = 0;
    map_init(map_pointer);

    srand(time(NULL));

    int top = rand() % 70 + 2, bot = rand() % 70 + 2, right = rand() % 15 + 2, left = rand() % 15 + 2;
    int treex = rand() % 70 + 2, treey = rand() % 10 + 5, grassx = rand() % 70 + 2, grassy = rand() % 10 + 5;

    int x1 = rand() % 70 + 2, y1 = rand() % 10 + 5, x2 = rand() % 70 + 2, y2 = rand() % 10 + 5;

    bot += 0;
    left += 0;
    if (nmx < 0 && smx < 0)
    {
        map_pointer->map[0][top] = 2;
        map_pointer->map[20][top] = 2;
        map_pointer->s_x = top;
        map_pointer->n_x = top;
    }
    else
    {
        if (nmx > 0 && smx < 0)
        {
            map_pointer->map[0][nmx] = 2;
            map_pointer->map[20][nmx] = 2;
            map_pointer->s_x = nmx;
            map_pointer->n_x = nmx;
        }
        else if (smx > 0 && nmx < 0)
        {
            map_pointer->map[0][smx] = 2;
            map_pointer->map[20][smx] = 2;
            map_pointer->s_x = smx;
            map_pointer->n_x = smx;
        }
        else
        {
            map_pointer->map[0][smx] = 2;
            map_pointer->map[20][smx] = 2;
            map_pointer->s_x = smx;
            map_pointer->n_x = smx;
            int i = 0;

            srand(time(NULL));

            for (i = 0; i < rand() % 10 + 8; i++)
            {
                map_pointer->map[i][nmx] = 2;
            }
        }
    }

    if (wmy < 0 && emy < 0)
    {
        map_pointer->map[right][0] = 2;
        map_pointer->map[right][79] = 2;
        map_pointer->e_y = right;
        map_pointer->w_y = right;
    }
    else
    {
        if (wmy < 0 && emy > 0)
        {
            map_pointer->map[emy][0] = 2;
            map_pointer->map[emy][79] = 2;
            map_pointer->e_y = emy;
            map_pointer->w_y = emy;
        }
        else if (emy < 0 && wmy > 0)
        {
            map_pointer->map[wmy][0] = 2;
            map_pointer->map[wmy][79] = 2;
            map_pointer->e_y = wmy;
            map_pointer->w_y = wmy;
        }
        else
        {
            map_pointer->map[wmy][0] = 2;
            map_pointer->map[wmy][79] = 2;

            int i = 0;

            srand(time(NULL));

            for (i = 0; i < rand() % 70 + 4; i++)
            {
                map_pointer->map[emy][i] = 2;
            }
        }
    }


    terrain_gen(map_pointer, treex, treey, grassx, grassy, x1, y1, x2, y2);
    path_gen(map_pointer, distance);
    map_place_pc(map_pointer);
    map_print(map_pointer);
    map_djikstra(map_pointer, RIVAL);
    map_print_dists(map_pointer);
    map_djikstra(map_pointer, HIKER);
    map_print_dists(map_pointer);
}