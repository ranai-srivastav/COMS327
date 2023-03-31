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
void gen_pokemon(World *w)
{
    srand(time(NULL));

    int poke_id = rand() % w->csv_pokemon.size();  // generate random pokemon id
    IO_pokemon::IO_pokemon_struct *poke = w->csv_pokemon[poke_id];  // get pokemon_id.name

    unsigned int i = 0;
    vector<IO_pokemon_moves::IO_pokemon_moves_struct*> possible_moves;  // get all possible moves for theat poke

    clear();
    for(i = 0; i<w->csv_pokemon_moves.size(); i++)
    {
        if(w->csv_pokemon_moves[i]->pokemon_id == poke->speciesID && w->csv_pokemon_moves[i]->pokemon_move_method_id == 1)
        {
            possible_moves.push_back(w->csv_pokemon_moves[i]);
        }
    }

    IO_pokemon_moves::IO_pokemon_moves_struct *random_move1, *random_move2;

    do
    {
        random_move1 = possible_moves[rand() % possible_moves.size()];
        random_move2 = possible_moves[4];
    }while(random_move1->move_id != random_move2->move_id);

    int HP_IV = rand()%15, attack_IV = rand()%15, defense_IV = rand()%15, speed_IV = rand()%15, sp_att_IV = rand()%15, sp_def_IV = rand()%15;
    int HP_base, attack_base, defense_base, speed_base, sp_att_base, sp_def_base;
    for(i = 0; i<w->csv_pokemon_stats.size(); i++)
    {
        if(w->csv_pokemon_stats[i]->pokemon_id == poke->speciesID)
            break;
    }

    HP_base = w->csv_pokemon_stats[i]->base_stat;
    attack_base = w->csv_pokemon_stats[i+1]->base_stat;
    defense_base = w->csv_pokemon_stats[i+2]->base_stat;
    sp_att_base = w->csv_pokemon_stats[i+3]->base_stat;
    sp_def_base = w->csv_pokemon_stats[i+4]->base_stat;
    speed_base = w->csv_pokemon_stats[i+5]->base_stat;

    double man_dist = (((w->x)-200) * ((w->x)-200))+ (((w->y)-200) * ((w->y)-200));
    if(man_dist == 0 || man_dist==1)
    {
        man_dist = 2;
    }
    int level = rand() % (int) man_dist;

    if(level > 200)
    {
        level = 200;
    }

    int HP = (int) floor(((HP_base+HP_IV)*2*level)/100) + level + 10;
    int attack = (int) floor(((attack_base+attack_IV)*2*level)/100) + 5;
    int defense = (int) floor(((defense_base+defense_IV)*2*level)/100) + 5;
    int speed = (int) floor(((speed_base+speed_IV)*2*level)/100) + 5;
    int sp_attack = (int) floor(((sp_att_base+sp_att_IV)*2*level)/100) + 5;
    int sp_defense = (int) floor(((sp_def_base+sp_def_IV)*2*level)/100) + 5;
    string gender;
    switch(rand()%3){ case 0: gender = "MALE"; break; case 1: gender = "FEMALE"; break; case 2: gender = "NONE";}
    string isShiny = rand()%2 ? "TRUE" : "FALSE";
    clear();
    WINDOW *pokemon_window = newwin(15,40, 0, 0);
    box(pokemon_window, 0, 0);
    mvprintw(1,1, "A Wild %s has appeared", poke->identifier.c_str());
    mvprintw(2,1, "Weight: %d", poke->weight);
    mvprintw(3,1, "Height: %d", poke->height);
    mvprintw(4,1, "Level: %d", level);
    mvprintw(5,1, "HP: %d", HP);
    mvprintw(6,1, "Attack: %d", attack);
    mvprintw(7,1, "Defense: %d", defense);
    mvprintw(8,1, "Speed: %d", speed);
    mvprintw(9,1, "Spcl Attack: %d", sp_attack);
    mvprintw(10,1, "Spcl Defense: %d", sp_defense);
    mvprintw(11,1, "Gender: %s", gender.c_str());
    mvprintw(12,1, "isShiny: %s", isShiny.c_str());
//    mvprintw(11,1, "Dist from center %d^2 + %d^2 = %f", w->y, w->x, man_dist);


    mvprintw(15,1, "This pokemon has 2 moves");
    mvprintw(16,1, "Move 1 %s", w->csv_moves[possible_moves[rand() % possible_moves.size()]->move_id]->identifier.c_str());
    mvprintw(17,1, "Move 2 %s", w->csv_moves[possible_moves[rand() % possible_moves.size()]->move_id]->identifier.c_str());

    refresh();
    getch();

}


void move_pc(World *w, int in)
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
            if(rand()%100 > 85)
            {
                gen_pokemon(w);
            }
        }
    }
    else
    {
        mvprintw(0, 0, "%s", ERROR);
    }

    refresh();
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