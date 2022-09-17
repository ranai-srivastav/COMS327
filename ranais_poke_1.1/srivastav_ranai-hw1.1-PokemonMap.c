/**
 * @file srivastav_ranai-hw1.1-PokemonMap.c
 * @author ranais@iastate.edu
 * @brief 
 * @version 1.1
 * @date 2022-09-07
 * 
 */

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


void map_init(int map[21][80])
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            map[i][j] = 0;
        }
    }

    i = 0, j = 0;
    for (i = 0; i < 80; i++)
    {
        map[0][i] = 6;
        map[20][i] = 6;
    }

    i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        map[i][0] = 6;
        map[i][79] = 6;
    }

}

void map_print(int map[21][80])
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 80; j++) {
            // if(map[i][j] == 1) printf("%d", map[i][j]);

            if (map[i][j] > -5 && map[i][j] < 0) printf("%c", ':');
            else if (map[i][j] > -10 && map[i][j] < 0) printf("%c", '^');
            else if (map[i][j] == 6) printf("%c", '%');
            else if (map[i][j] == 2) printf("%c", '#');
            else if (map[i][j] == 8) printf("%c", 'M');
            else if (map[i][j] == 9) printf("%c", 'C');
            else printf("%c", '.');
        }
        printf("\n");
    }
}

void map_print_nums(int map[21][80])
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 80; j++) {
             printf("%2d", map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void recurse_terrain(int map[21][80], int x, int y, int type)
{
    if(map[y][x] <= 0 && map[y][x] > -9)
    {
        map[y][x] = map[y][x] - 1;
    }
    else
    {
        map[y][x] += 8;
        if (x < 79 && y > 2)
            recurse_terrain(map, x + 1, y - 1, type);
        if (x < 70)
            recurse_terrain(map, x + 1, y, type);
        if (x < 79 && y < 16)
            recurse_terrain(map, x + 1, y + 1, type);
        if (y > 10)
            recurse_terrain(map, x, y - 1, type);
        if (x < 78 && y > 2 && y < 19)
            recurse_terrain(map, x, y + 1, type);
        if (x > 2 && y > 2)
            recurse_terrain(map, x - 1, y - 1, type);
        if (x > 2)
            recurse_terrain(map, x - 1, y, type);
        if (x > 2 && x < 72 && y > 2 && y < 10)
            recurse_terrain(map, x - 1, y + 1, type);
    }
}

void terrain_gen(int map[21][80], int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2)
{
    int count = 0;
    map[treey][treex] = -1;
    for(count = 0; count < 3000; count ++)
    {
        recurse_terrain(map, treex, treey, -5);
        recurse_terrain(map, grassx, grassy, -5);
        recurse_terrain(map, x1, y1, -5);
        recurse_terrain(map, x2, y2, -5);
        recurse_terrain(map, grassx, y2, -5);
        recurse_terrain(map, x2, treey, -5);
        // map_print_nums(map);
    }
}

void path_gen(int map[21][80], int top, int right)
{
    int Cx = rand() % 70 + 2, Mx = rand() % 70 + 2;
    int Cy = rand() % 15 + 2, My = rand() % 15 + 2;

    int choose = rand() % 2;

    int x = 0, y = 0;
    for (y = 0; y < 20; y += 1)
    {
        map[y][top] = 2;
        if (y == Cy)
        {
            if (choose)
                map[y][top + 1] = 8;
            else
                map[y][top + 1] = 9;
        }
    }

    x = 0, y = 0;
    for (x = 0; x < 80; x += 1)
    {
        map[right][x] = 2;
        if (x == Mx)
        {
            if (choose)
                map[right + 1][x] = 9;
            else
                map[right + 1][x] = 8;
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


void map_gen(int map[21][80])
{
    srand(time(NULL));

    int top = rand() % 70 + 2, right = rand() % 15 + 2;
    int treex = rand() % 70 + 2, treey = rand() % 10 + 5, grassx = rand() % 70 + 2, grassy = rand() % 10 + 5;

    int x1 = rand() % 70 + 2, y1 = rand() % 10 + 5, x2 = rand() % 70 + 2, y2 = rand() % 10 + 5;


    map[0][top] = 2;
    map[20][top] = 2;
    map[right][0] = 2;
    map[right][79] = 2;


    terrain_gen(map, treex, treey, grassx, grassy, x1, y1, x2, y2);
     path_gen(map, top, right);

}

int main(int argc, char *argv[])
{
    int map[21][80];
    map_init(map);
    map_gen(map);
    map_print(map);

}
