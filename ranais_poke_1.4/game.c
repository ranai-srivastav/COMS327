/**
 * @file game.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The main code for the game. Syncs values between map.c and world.c and their respective data structures.
 * @version 2
 * @date 28th Oct, 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "world.h"

int main(int argc, char* argv[])
{
    world_t *w = malloc(sizeof(world_t));
    int num_trainers = 12;
    if(argc > 1)
    {
        num_trainers = atoi(argv[2]);
    }

    init(w, num_trainers);

    simulate_movement(w->world[w->y][w->x]);

//    char user_in[12] = "\0";
//    while (strcmp(user_in, "q"))
//    {
//        scanf("%s", user_in);
//        char d = user_in[0];
//        switch (d)
//        {
//            case 'n':
//                w->y = (w->y) - 1;
//                break;
//
//            case 's':
//                w->y = (w->y) + 1;
//                break;
//
//            case 'e':
//                w->x = (w->x) + 1;
//                break;
//
//            case 'w':
//                w->x = (w->x) - 1;
//                break;
//
//            case 'f':
//            {
//                int nx = 0, ny = 0;
//                scanf(" %d", &nx);
//                scanf(" %d", &ny);
//                w->x = nx;
//                w->y = ny;
//            }
//            break;
//
//            case 'q':
//                break;
//
//            default:
//                printf("*****************ERROR**************\n");
//                printf("Typed in a value other than [n, s, e, w, <f, x, y>]");
//                break;
//        }
//        if(d != 'q')
//            move_dir(w, w->y, w->x);
//    }

    deinit(w);

    return 0;

}