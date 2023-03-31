/**
 * @file srivastav_ranai-hw1.1-PokemonMap.c
 * @author ranais@iastate.edu
 * @brief 
 * @version 1.1
 * @date 2022-09-07
 * 
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "map.h"


void map_init(int map[21][80])
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            map[i][j] = CLEARING;
        }
    }

    i = 0, j = 0;
    for (i = 0; i < 80; i++)
    {
        map[0][i] = WALLS;
        map[20][i] = WALLS;
    }

    i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        map[i][0] = WALLS;
        map[i][79] = WALLS;
    }

    start_color();
    init_pair(CLEARING, COLOR_GREEN, COLOR_BLACK);
    init_pair(TALL_GRASS, COLOR_GREEN, COLOR_BLACK);
    init_pair(BOULDER, COLOR_BLACK, COLOR_WHITE);
    init_pair(TREE, COLOR_GREEN, COLOR_BLACK);
    init_pair(POKE_CENTER, COLOR_RED, COLOR_BLUE);
    init_pair(POKE_MART, COLOR_BLUE, COLOR_WHITE);
    init_pair(PATH, COLOR_YELLOW, COLOR_BLACK);

}

void map_print(int map[21][80])
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            move(i+1, j);
            refresh();
            switch (map[i][j])
            {
                case CLEARING:
                    attron(COLOR_PAIR(CLEARING));
                    addch('.');
                    attroff(COLOR_PAIR(CLEARING));
                break;

                case WALLS:
                case BOULDER:
                    attron(COLOR_PAIR(BOULDER));
                    addch('%');
                    attroff(COLOR_PAIR(BOULDER));
                break;

                case TALL_GRASS:
                    attron(COLOR_PAIR(TALL_GRASS));
                    addch(':' | A_BOLD);
                    attroff(COLOR_PAIR(TALL_GRASS));
                break;

                case TREE:
                    attron(COLOR_PAIR(TREE));
                    addch('^');
                    attroff(COLOR_PAIR(TREE));
                break;

                case EXITS:
                case PATH:
                    attron(COLOR_PAIR(PATH));
                    addch('#');
                    attroff(COLOR_PAIR(PATH));
                break;

                case POKE_CENTER:
                    attron(COLOR_PAIR(POKE_CENTER));
                    addch('C');
                    attroff(COLOR_PAIR(POKE_CENTER));
                break;

                case POKE_MART:
                    attron(COLOR_PAIR(POKE_MART));
                    addch('M');
                    attroff(COLOR_PAIR(POKE_MART));
                break;

//                case CHARACTER:
//                    switch (map)
//                    {
//
//                    }
            }
            move(0, j+1);
            refresh();
        }
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
     if (map[y][x] < type)
     {
         map[y][x] = type;
     }
     else
     {
         map[y][x] = CLEARING;
         if (x < 79 && y > 2 && map[y - 1][x + 1] == CLEARING)
             recurse_terrain(map, x + 1, y - 1, type);
         if (x < 70 && map[y][x] == CLEARING)
             recurse_terrain(map, x + 1, y, type);
         if (x < 79 && y < 16 && map[y + 1][x + 1] == CLEARING)
             recurse_terrain(map, x + 1, y + 1, type);

         if (y > 10 && map[y-1][x] == CLEARING)
             recurse_terrain(map, x, y - 1, type);
         if (x < 78 && y > 2 && y < 19 && map[y+1][x] == CLEARING)
             recurse_terrain(map, x, y + 1, type);
         if (x > 2 && y > 2 && map[y-1][x-1] == CLEARING)
             recurse_terrain(map, x - 1, y - 1, type);
         if (x > 2 && map[y][x-1] == CLEARING)
             recurse_terrain(map, x - 1, y, type);
         if (x > 2 && x < 72 && y > 2 && y < 10 && map[y+1][x-1] == CLEARING)
             recurse_terrain(map, x - 1, y + 1, type);
     }
 }

void terrain_gen(int map[21][80], int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2)
{
    int count = 0;
    map[treey][treex] = BOULDER;
    for (count = 0; count < 12000; count++) {
        recurse_terrain(map, treex, treey, TREE);
        recurse_terrain(map, grassx, grassy, TALL_GRASS);
        recurse_terrain(map, x1, y1, BOULDER);
        recurse_terrain(map, x2, y2, TREE);
        recurse_terrain(map, grassx, y2, TALL_GRASS);
        recurse_terrain(map, x2, treey, TALL_GRASS);
        // map_print_nums(map);
    }
}

void path_gen(int map[21][80], int top, int right)
{
    int Cx = rand() % 70 + 2, Mx = rand() % 70 + 2;
    int Cy = rand() % 15 + 2, My = rand() % 15 + 2;

    Cx += 0;
    My += 0;

    int choose = rand() % 2;

    int x = 0, y = 0;
    for (y = 0; y < 20; y += 1)
    {
        map[y][top] = PATH;
        if (y == Cy)
        {
            if (choose)
                map[y][top + 1] = POKE_MART;
            else
                map[y][top + 1] = POKE_CENTER;
        }
    }

    x = 0, y = 0;
    for (x = 0; x < 80; x += 1)
    {
        map[right][x] = PATH;
        if (x == Mx)
        {
            if (choose)
                map[right + 1][x] = POKE_CENTER;
            else
                map[right + 1][x] = POKE_MART;
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


    map[0][top] = EXITS;
    map[20][top] = EXITS;
    map[right][0] = EXITS;
    map[right][79] = EXITS;


    terrain_gen(map, treex, treey, grassx, grassy, x1, y1, x2, y2);
     path_gen(map, top, right);

}

int main(int argc, char *argv[])
{
    int map[21][80];

    initscr();
    noecho();
    curs_set(FALSE);

    map_init(map);
    map_gen(map);
    mvaddstr(0,0, "Welcome to Pokemon game!");
    map_print(map);
    mvaddstr(0,0, "Welcome to Pokemon game!");
    refresh();

    getch();

    endwin();
    

}
