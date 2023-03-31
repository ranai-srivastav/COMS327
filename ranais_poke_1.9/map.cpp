/**
 * @file map.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The file that generates a map, terrain, paths, etc
 * @version 3
 * @date 2022-09-07
 * 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "priority_queue.h"
#include "linked_list.h"
#include <climits>
#include <unistd.h>
#include <ncurses.h>


void map_init(MapStruct *map_pointer)
{
    int i, j;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            map_pointer->map[i][j] = CLEARING;
            map_pointer->players[i][j] = NONE;
        }
    }

    i = 0, j = 0;
    for (i = 0; i < 80; i++) {
        map_pointer->map[0][i] = WALLS;
        map_pointer->map[20][i] = WALLS;
    }

    for (i = 0; i < 21; i++) {
        map_pointer->map[i][0] = WALLS;
        map_pointer->map[i][79] = WALLS;
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

void map_print(MapStruct *map_pointer)
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            move(i+1, j);
            refresh();

            if(map_pointer->players[i][j] != NONE)
            {
                switch(map_pointer->players[i][j])
                {
                    case PLAYER_CHARACTER:
                        addch('@');
                        break;
                    case RIVAL:
                        addch('R');
                        break;
                    case HIKER:
                        addch('H');
                        break;
                    case PACER:
                        addch('P');
                        break;
                    case WANDERER:
                        addch('W');
                        break;
                    case SENTRIES:
                        addch('S');
                        break;
                    case EXPLORERS:
                        addch('E');
                        break;
                }
            }
            else
            {
                switch(map_pointer->map[i][j])
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
                }
            }
        }
        move(0, j+1);
        refresh();
    }
}


void map_print_dists(MapStruct *map_pointer, player_type player_type)
{
    if(player_type == RIVAL)
    {
        int i = 0, j = 0;
        for(i = 1; i < 20; i++)
        {
            for(j = 1; j < 79; j++)
            {
                if(map_pointer->dist_rival[i][j] % 10 == 9)
                {
                    printf("   ");
                }
                else
                {
                    printf("%02d ", (map_pointer->dist_rival[i][j]) % 100);
                }
            }
            printf("\n");
        }
        printf("\n\n\n");
    }
    else if(player_type == HIKER)
    {
        int i = 0, j = 0;
        for(i = 0; i < 21; i++)
        {
            for(j = 0; j < 80; j++)
            {
                if(map_pointer->dist_hiker[i][j] % 10 == 9)
                {
                    printf("   ");

                }
                else
                {
                    printf("%02d", (map_pointer->dist_hiker[i][j]) % 100);
                }
            }
            printf("\n");
        }
        printf("\n\n\n");
    }
}

void map_debug_print(int map[21][80])
{
    int i = 0, j = 0;
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 80; j++)
        {
            printf("%02d ", (map[i][j]));
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void recurse_terrain(MapStruct *map_pointer, int x, int y, int type)
{
    if (map_pointer->map[y][x] < type)
    {
        map_pointer->map[y][x] = type;
    }
    else
    {
        map_pointer->map[y][x] = CLEARING;
        if (x < 79 && y > 2 && map_pointer->map[y - 1][x + 1] == CLEARING)
            recurse_terrain(map_pointer, x + 1, y - 1, type);
        if (x < 70 && map_pointer->map[y][x] == CLEARING)
            recurse_terrain(map_pointer, x + 1, y, type);
        if (x < 79 && y < 16 && map_pointer->map[y + 1][x + 1] == CLEARING)
            recurse_terrain(map_pointer, x + 1, y + 1, type);

        if (y > 10 && map_pointer->map[y-1][x] == CLEARING)
            recurse_terrain(map_pointer, x, y - 1, type);
        if (x < 78 && y > 2 && y < 19 && map_pointer->map[y+1][x] == CLEARING)
            recurse_terrain(map_pointer, x, y + 1, type);
        if (x > 2 && y > 2 && map_pointer->map[y-1][x-1] == CLEARING)
            recurse_terrain(map_pointer, x - 1, y - 1, type);
        if (x > 2 && map_pointer->map[y][x-1] == CLEARING)
            recurse_terrain(map_pointer, x - 1, y, type);
        if (x > 2 && x < 72 && y > 2 && y < 10 && map_pointer->map[y+1][x-1] == CLEARING)
            recurse_terrain(map_pointer, x - 1, y + 1, type);
    }
}

void terrain_gen(MapStruct *map_pointer, int treex, int treey, int grassx, int grassy, int x1, int y1, int x2, int y2)
{
    int count = 0;
    map_pointer->map[treey][treex] = BOULDER;
    for (count = 0; count < 12000; count++) {
        recurse_terrain(map_pointer, treex, treey, TREE);
        recurse_terrain(map_pointer, grassx, grassy, TALL_GRASS);
        recurse_terrain(map_pointer, x1, y1, BOULDER);
        recurse_terrain(map_pointer, x2, y2, TREE);
        recurse_terrain(map_pointer, grassx, y2, TALL_GRASS);
        recurse_terrain(map_pointer, x2, treey, TALL_GRASS);
        // map_print_nums(map);
    }
}

void path_gen(MapStruct *map_pointer, int distance)
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
        map_pointer->map[y][top] = PATH;
        if (y == Cy)
        {
            if (choose)
            {
                map_pointer->map[y][top + 1] = POKE_MART;
                map_pointer->map[y][top + 2] = POKE_MART;
            }
            else
            {
                map_pointer->map[y][top + 1] = POKE_CENTER;
                map_pointer->map[y][top + 2] = POKE_CENTER;
            }
        }
    }

    right = map_pointer->e_y;
    x = 0, y = 0;
    for (x = 0; x < 80; x += 1)
    {
        map_pointer->map[right][x] = PATH;
        if (x == Mx)
        {
            if (choose)
            {
                map_pointer->map[right + 1][x] = POKE_CENTER;
                map_pointer->map[right + 2][x] = POKE_CENTER;
            }
            else
            {
                map_pointer->map[right + 1][x] = POKE_MART;
                map_pointer->map[right + 2][x] = POKE_MART;
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
int get_weight(MapStruct *map, point_t *point, player_type type)
{
    if(type == RIVAL)
    {
        if (map->map[point->y][point->x] == TALL_GRASS) //GRASS
        {
            return 20;
        }
        else if (map->map[point->y][point->x] == TREE ) //TREE
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == BOULDER) //BOULDER
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == PATH) //PATH
        {
            return 10;
        }
        else if (map->map[point->y][point->x] == POKE_MART) //MART
        {
            return 50;
        }
        else if (map->map[point->y][point->x] == POKE_CENTER) //CENTER
        {
            return 50;
        }
        return 10;
    }

    else if(type == HIKER)
    {
        if (map->map[point->y][point->x] == TALL_GRASS) //GRASS
        {
            return 15;
        }
        else if (map->map[point->y][point->x] == TREE) //TREE
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == BOULDER) //BOULDER
        {
            return 10099;
        }
        else if (map->map[point->y][point->x] == PATH) //PATH
        {
            return 10;
        }
        else if (map->map[point->y][point->x] == POKE_MART) //MART
        {
            return 50;
        }
        else if (map->map[point->y][point->x] == POKE_CENTER) //CENTER
        {
            return 50;
        }
        return 10;
    }

    return 10;
}

void map_djikstra(MapStruct *map, player_type type)
{
    point_t *player_pos_backup = (point_t*) malloc(sizeof(point_t));
    player_pos_backup->y = map->player_pos->y;
    player_pos_backup->x = map->player_pos->x;
    int i = 0, j = 0;

    const char delta[3] = {-1, 0, 1};
    point_t *node;

    if(type == RIVAL)
    {
        for (i = 0; i < 21; ++i)
        {
            for(j = 0; j<80; ++j)
            {
                map->dist_rival[i][j] = -1;
            }
        }

        priority_queue_t *pq = (priority_queue_t*) malloc(sizeof(priority_queue_t));
        priority_q_init(pq, map->player_pos, 0);

        int curr_y = map->player_pos->y;
        int curr_x = map->player_pos->x;
        map->dist_rival[curr_y][curr_x] = 00;
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

                    if(map->dist_rival[new_y][new_x] == -1)
                    {
                        enq = (point_t*) malloc(sizeof(point_t));
                        enq->y = new_y;
                        enq->x = new_x;
                        map->dist_rival[new_y][new_x] = map->dist_rival[curr_y][curr_x] + get_weight(map, enq, type);
                        push(pq, enq, map->dist_rival[curr_y][curr_x] + get_weight(map, enq, type));
//                    free(enq);
                    }
                    else
                    {
                        int k = 0, l = 0;
                        point_t *p = (point_t*) malloc(sizeof(point_t));
                        for(k = 0; k<3; k++)
                        {
                            for (l = 0; l < 3; l++)
                            {
                                p->x = new_x + delta[k];
                                p->y = new_y + delta[l];
                                if(p->y < 0 || p->y > 20 || p->x > 79 || p->x < 0)
                                {
                                    continue;
                                }
                                else if((map->dist_rival[p->y][p->x] > map->dist_rival[new_y][new_x] + get_weight(map, p, type)))
                                {
                                    map->dist_rival[p->y][p->x] = map->dist_rival[new_y][new_x] + get_weight(map, p, type);
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
    else if(type == HIKER)
    {
        for (i = 0; i < 21; ++i)
        {
            for(j = 0; j<80; ++j)
            {
                map->dist_hiker[i][j] = -1;
            }
        }

        priority_queue_t *pq = (priority_queue_t*) malloc(sizeof(priority_queue_t));
        priority_q_init(pq, map->player_pos, 0);

        int curr_y = map->player_pos->y;
        int curr_x = map->player_pos->x;
        map->dist_hiker[curr_y][curr_x] = 00;
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

                    if(map->dist_hiker[new_y][new_x] == -1)
                    {
                        enq = (point_t*) malloc(sizeof(point_t));
                        enq->y = new_y;
                        enq->x = new_x;
                        map->dist_hiker[new_y][new_x] = map->dist_hiker[curr_y][curr_x] + get_weight(map, enq, type);
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
                                point_t *p = (point_t*) malloc(sizeof(point_t));
                                p->x = new_x + delta[j];
                                p->y = new_y + delta[l];
                                if(p->y < 0 || p->y > 20 || p->x > 79 || p->x < 0)
                                {
                                    continue;
                                }
                                else if((map->dist_hiker[p->y][p->x] > map->dist_hiker[new_y][new_x] + get_weight(map, p, type)))
                                {
                                    map->dist_hiker[p->y][p->x] = map->dist_hiker[new_y][new_x] + get_weight(map, p, type);
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
}

//TODO Check terrain type for !path for CC and MM

void map_place_pc(MapStruct *map)
{
    map->player_pos = (point_t*) malloc(sizeof(point_t*));
    do
    {
        int px = rand()%70 + 5;
        int py = rand()%15 + 3;

        if(map->map[py][px] == PATH)
        {
            map->players[py][px] = PLAYER_CHARACTER;

            map->player_pos->x = px;
            map->player_pos->y = py;
            break;
        }
    }while(1);
}

void place_char(MapStruct *map_pointer, player_type type, int x, int y)
{
    ll_node_t *this_node = (ll_node_t*) malloc(sizeof(ll_node_t));
//    this->curr_pos = malloc(sizeof(point_t));
    this_node->curr_pos_y = y;
    this_node->curr_pos_x = x;
    this_node->type = type;
    this_node->has_fought = 0;
//    const int delta[] = {-1, 0, 1};
    switch(type)
    {
        case RIVAL:
            this_node->player_type_string = "RIVAL";
        case HIKER:
            this_node->player_type_string = "HIKER";
            break;

        case PACER:
            this_node->player_type_string = "PACER";
        case WANDERER:
            this_node->player_type_string = "WANDERER";
//            this->vector = malloc(sizeof(point_t));
//            this->vector->y = rand() % 79 + 1;
//            this->vector->x = rand() % 19 + 1;
//            break;

        case SENTRIES:
            this_node->player_type_string = "SENTRY";
            break;

        default: break;
    }
    ll_push(map_pointer->player_positions, this_node, sizeof(ll_node_t));
    map_pointer->players[y][x] = type;
}

void place_npc(MapStruct *map_pointer, int numtrainers)
{
    map_pointer->player_positions = (linked_list_t*) malloc(sizeof(linked_list_t));
    srand(time(NULL));

    int i = 0;
    map_pointer->num_players = numtrainers;

    place_char(map_pointer, HIKER, rand() % 79 + 1, rand() % 19 + 1);

    for(i = 0; i<numtrainers-2; i++)
    {
//        int temp_type = rand() % 5 + 2;
        int x = rand() % 79 + 1;
        int y = rand() % 19 + 1;

//        place_char(map_pointer, temp_type, x, y);
        place_char(map_pointer, SENTRIES, x, y);
    }

    place_char(map_pointer, RIVAL, rand() % 79 + 1, rand() % 19 + 1);




//    memcpy(map_pointer->npcs, temp_npcs, sizeof(npc_t*) * numtrainers);
}


void map_gen(MapStruct *map_pointer, int nmx, int smx, int emy, int wmy, point_t *new_player_pos, int num_trainers)
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
        map_pointer->map[0][top] = EXITS;
        map_pointer->map[20][top] = EXITS;
        map_pointer->s_x = top;
        map_pointer->n_x = top;
    }
    else
    {
        if (nmx > 0 && smx < 0)
        {
            map_pointer->map[0][nmx] = EXITS;
            map_pointer->map[20][nmx] = EXITS;
            map_pointer->s_x = nmx;
            map_pointer->n_x = nmx;
        }
        else if (smx > 0 && nmx < 0)
        {
            map_pointer->map[0][smx] = EXITS;
            map_pointer->map[20][smx] = EXITS;
            map_pointer->s_x = smx;
            map_pointer->n_x = smx;
        }
        else
        {
            map_pointer->map[0][smx] = EXITS;
            map_pointer->map[20][smx] = EXITS;
            map_pointer->s_x = smx;
            map_pointer->n_x = smx;
            int i = 0;

            srand(time(NULL));

            for (i = 0; i < rand() % 10 + 8; i++)
            {
                map_pointer->map[i][nmx] = EXITS;
            }
        }
    }

    if (wmy < 0 && emy < 0)
    {
        map_pointer->map[right][0] = EXITS;
        map_pointer->map[right][79] = EXITS;
        map_pointer->e_y = right;
        map_pointer->w_y = right;
    }
    else
    {
        if (wmy < 0 && emy > 0)
        {
            map_pointer->map[emy][0] = EXITS;
            map_pointer->map[emy][79] = EXITS;
            map_pointer->e_y = emy;
            map_pointer->w_y = emy;
        }
        else if (emy < 0 && wmy > 0)
        {
            map_pointer->map[wmy][0] = EXITS;
            map_pointer->map[wmy][79] = EXITS;
            map_pointer->e_y = wmy;
            map_pointer->w_y = wmy;
        }
        else
        {
            map_pointer->map[wmy][0] = EXITS;
            map_pointer->map[wmy][79] = EXITS;

            int i = 0;

            srand(time(NULL));

            for (i = 0; i < rand() % 70 + 4; i++)
            {
                map_pointer->map[emy][i] = EXITS;
            }
        }
    }



    terrain_gen(map_pointer, treex, treey, grassx, grassy, x1, y1, x2, y2);
    path_gen(map_pointer, distance);
    if(new_player_pos == 0)
    {
        map_place_pc(map_pointer);
    }
    else
    {
        map_pointer->player_pos = new_player_pos;
        map_pointer->players[new_player_pos->y][new_player_pos->x] = PLAYER_CHARACTER;
    }
    map_djikstra(map_pointer, RIVAL);
//    map_print_dists(map_pointer, RIVAL);
    map_djikstra(map_pointer, HIKER);
//    map_print_dists(map_pointer, HIKER);
    place_npc(map_pointer, num_trainers);
//    map_debug_print(map_pointer->players);
//    map_print(map_pointer);
}

void npc_move(MapStruct *map_pointer, player_type type, int i)
{
    const int delta[] = {-1, 0, 1};
    ll_node_t *curr_node = ll_get(map_pointer->player_positions, i);
    type = curr_node->type;
    point_t pos;
    pos.x = curr_node->curr_pos_x;
    pos.y = curr_node->curr_pos_y;
    int min_cost = INT_MAX;
    int k = 0, j = 0;
    point_t move_to;
    if(curr_node->has_fought == 0)
    {
        switch(type)
        {
            case HIKER:
                for(k = 0; k < 3; k++)
                {
                    for(j = 0; j < 3; j++)
                    {
                        if(k == 1 && j == 1) continue;
                        point_t new_point;
                        new_point.x = pos.x + delta[k];
                        new_point.y = pos.y + delta[j];
                        if(map_pointer->dist_hiker[new_point.y][new_point.x] <= min_cost &&
                        map_pointer->map[new_point.y][new_point.x] != BOULDER &&
                        map_pointer->map[new_point.y][new_point.x] != WALLS &&
                        map_pointer->players[new_point.y][new_point.x] == NONE)
                        {
                            min_cost = map_pointer->dist_hiker[new_point.y][new_point.x];
                            move_to.x = new_point.x;
                            move_to.y = new_point.y;
                        }
                    }
                }
                map_pointer->players[pos.y][pos.x] = NONE;
                map_pointer->players[move_to.y][move_to.x] = type;
                curr_node->curr_pos_y = move_to.y;
                curr_node->curr_pos_x = move_to.x;
                break;

            case RIVAL:
                for(k = 0; k < 3; k++)
                {
                    for(j = 0; j < 3; j++)
                    {
                        if(k == 1 && j == 1) continue;
                        point_t new_point;
                        new_point.x = pos.x + delta[k];
                        new_point.y = pos.y + delta[j];
                        if(map_pointer->dist_rival[new_point.y][new_point.x] <= min_cost &&
                        map_pointer->map[new_point.y][new_point.x] != BOULDER &&
                        map_pointer->map[new_point.y][new_point.x] != WALLS &&
                        map_pointer->players[new_point.y][new_point.x] == NONE)
                        {
                            min_cost = map_pointer->dist_rival[new_point.y][new_point.x];
                            move_to.x = new_point.x;
                            move_to.y = new_point.y;
                        }
                    }
                }
                map_pointer->players[pos.y][pos.x] = NONE;
                map_pointer->players[move_to.y][move_to.x] = type;
                curr_node->curr_pos_y = move_to.y;
                curr_node->curr_pos_x = move_to.x;
                break;
            case PACER:
                break;
            case WANDERER:
                break;
            case SENTRIES:
                break;
            case EXPLORERS:
                break;
            default:
                break;
        }
    }
}

void simulate_movement(MapStruct *map_pointer)
{
    int i = 0;
//    priority_queue_t *turn_counter = malloc(sizeof(priority_queue_t));

    for(i = 0; i<map_pointer->num_players; i++)
    {
//        npc_t *npc;
//        ll_get((void **) &npc, map_pointer->player_positions, i);
//        push(turn_counter, npc->curr_pos, get_weight(map_pointer, npc->curr_pos, npc->type));
    }


    for(i = 0; i < map_pointer->num_players; i++)
    {
        npc_move(map_pointer, NONE, i);
    }
    map_print(map_pointer);
//    usleep(500000);

}

/**
* init_terminal()
 * {
 *  initscr();
 *
 * }
*/