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
#include "map.h"


void map_init(map_t *map_pointer)
{
    int i = 0, j = 0;
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

    i = 0, j = 0;
    for (i = 0; i < 21; i++) {
        map_pointer->map[i][0] = 6;
        map_pointer->map[i][79] = 6;
    }

}

void map_print(map_t *map_pointer)
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 80; j++) {
            // if(map[i][j] == 1) printf("%d", map[i][j]);

            if (map_pointer->map[i][j] > -5 && map_pointer->map[i][j] < 0) printf("%c", ':');
            else if (map_pointer->map[i][j] > -10 && map_pointer->map[i][j] < 0) printf("%c", '^');
            else if (map_pointer->map[i][j] == 6) printf("%c", '%');
            else if (map_pointer->map[i][j] == 2) printf("%c", '#');
            else if (map_pointer->map[i][j] == 8) printf("%c", 'M');
            else if (map_pointer->map[i][j] == 9) printf("%c", 'C');
            else printf("%c", '.');
        }
        printf("\n");
    }
}

void map_print_nums(map_t *map_pointer)
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            printf("%2d", map_pointer->map[i][j]);
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
    for (count = 0; count < 3000; count++) {
        recurse_terrain(map_pointer, treex, treey, -5);
        recurse_terrain(map_pointer, grassx, grassy, -5);
        recurse_terrain(map_pointer, x1, y1, -5);
        recurse_terrain(map_pointer, x2, y2, -5);
        recurse_terrain(map_pointer, grassx, y2, -5);
        recurse_terrain(map_pointer, x2, treey, -5);
        // map_print_nums(map);
    }
}

void path_gen(map_t *map_pointer)
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

    // int pathx, pathy;

    // while(abs(pathx-Cx)<=2 || pathy != (Cy - 1))
    // {
    //     if( (abs(Cx-(pathx-1)) < abs(Cx-pathx)))
    //     {
    //         map[pathy][pathx-1] = 2;
    //         pathx -= 1;
    //     }
    //     else if( (abs(Cx-(pathx-1)) > abs(Cx-pathx)))
    //     {
    //         map[pathy][pathx+1] = 2;
    //         pathx += 1;
    //     }

    //     if(pathy != Cy-1)
    //     {
    //         map[pathy+1][pathx] = 2;
    //         pathy += 1;
    //     }

    //     map_print(map);
    // }
}


void map_gen(map_t *map_pointer, int nmx, int smx, int emy, int wmy)
{
    map_init(map_pointer);

    srand(time(NULL));

    int top = rand() % 70 + 2, right = rand() % 15 + 2;
    int treex = rand() % 70 + 2, treey = rand() % 10 + 5, grassx = rand() % 70 + 2, grassy = rand() % 10 + 5;

    int x1 = rand() % 70 + 2, y1 = rand() % 10 + 5, x2 = rand() % 70 + 2, y2 = rand() % 10 + 5;

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

            for(i=0; i<rand()%10+8; i++)
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
        if(wmy < 0 && emy > 0)
        {
            map_pointer->map[emy][0] = 2;
            map_pointer->map[emy][79] = 2;
            map_pointer->e_y = emy;
            map_pointer->w_y = emy;
        }
        else if(emy < 0 && wmy > 0)
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

            for(i=0; i<rand()%70+4; i++)
            {
                map_pointer->map[emy][i] = 2;
            }
        }
    }


    terrain_gen(map_pointer, treex, treey, grassx, grassy, x1, y1, x2, y2);
    path_gen(map_pointer);
    map_print(map_pointer);
}

// int main(int argc, char *argv[])
// {
//     map_t* map;
//     map_init(map);
//     map_gen(map);
//     map_print(map);

// }
