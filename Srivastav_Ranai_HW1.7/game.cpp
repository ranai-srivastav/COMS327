#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include "world.h"
#include "FileIO.cpp"
#include <string>
#include <fstream>
#include <iostream>
#include "IO_Pokemon.h"
#include "IO_moves.h"
#include "IO_pokemon_moves.h"

/**
 * @file game.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The main code for the game. Syncs values between map.c and world.c and their respective data structures.
 * @version 2
 * @date 28th Oct, 2022
 */

using namespace std;

void clr_line(int y, int x)
{
    move(y,x);
    refresh();
    clrtoeol();
    refresh();
}

void battle()
{
    clr_line(0,0);
    mvprintw(0,0,"---------!!!-------FIGHT--------!!-----------");
}

void is_battling(World *w)
{
    int i = 0;
    MapStruct *curr_map = w->world[w->y][w->x];
    int pc_x = curr_map->player_pos->x;
    int pc_y = curr_map->player_pos->y;

    for (i = 0; i<w->world[w->y][w->x]->num_players; i++)
    {
        ll_node_t *node = ll_get(w->world[w->y][w->x]->player_positions, i);

//        clr_line(0,0);
//        mvprintw(0,0, "has fought has value %5d for %5d", node->has_fought, i);
//        usleep(1000000);
        if( (abs(pc_y - node->curr_pos_y) <= 1 && abs(pc_x - node->curr_pos_x) <= 1) && node->has_fought == 0 )
        {
                clr_line(0,0);
                mvprintw(0,0,"Fighting with (%d %d) from (%d, %d)", node->curr_pos_y, node->curr_pos_x, pc_y, pc_x);
            node->has_fought = 1;
            battle();
        }
    }
}

void print_trainers(World *w, int start, int end)
{
    MapStruct *curr_map = w->world[w->y][w->x];
    int i = 0;

    for (i = start; i < end && i<curr_map->num_players; i++)
    {
        char s[80];
        char c[20];
        char vert[20];
        char hori[20];
        int pc_x = -1;
        int pc_y = -1;

        ll_node_t *curr_node = ll_get(curr_map->player_positions, i);

        switch(curr_node->type)
        {
            case HIKER:
                sprintf(c, "%-8s", "HIKER");
            break;
            case RIVAL:
                sprintf(c, "%-8s", "RIVAL");
            break;
            case PACER:
                sprintf(c, "%-8s", "PACER");
            break;
            case WANDERER:
                sprintf(c, "%-8s", "WANDERER");
            break;
            case SENTRIES:
                sprintf(c, "%-8s", "SENTRY");
                break;
            case EXPLORERS:
                sprintf(c, "%-8s", "EXPLORER");
                break;
        }

        pc_x = curr_map->player_pos->x;
        pc_y = curr_map->player_pos->y;

        int x_dist = 0, y_dist = 0;

        //TODO just take the abs value of the distance
        if(pc_y > curr_node->curr_pos_y)
        {
            y_dist = pc_y - curr_node->curr_pos_y;
            sprintf(vert, "%d %s", pc_y - curr_node->curr_pos_y, "NORTH");
        }
        else
        {
            y_dist = curr_node->curr_pos_y - pc_y;
            sprintf(vert, "%d %s",curr_node->curr_pos_y - pc_y,  "SOUTH");
        }

        if(pc_x > curr_node->curr_pos_x)
        {
            x_dist = pc_x - curr_node->curr_pos_x;
            sprintf(hori, "%d %s", pc_x - curr_node->curr_pos_x, "EAST");
        }
        else
        {
            x_dist = curr_node->curr_pos_x - pc_x;
            sprintf(hori, "%d %s", curr_node->curr_pos_x - pc_x, "WEST");
        }


            sprintf(s, "Character: %s %s %s", c, vert, hori);
            mvprintw(28+i, 0, "%s: %s %s", c, vert, hori);
            refresh();
    }
}

void enter_poke_mart(World *w)
{
    int i = 0;
    do
    {
        clr_line(0,0);
        mvprintw(0,0, "YOU are inside a pokemart");
        i = getch();
    }while(i != '<');

    clr_line(0,0);
    mvprintw(0,0, "YOU are exiting a Pokemart");

}

void enter_poke_center(World *w)
{
    int i = 0;
    do
    {
        clr_line(0,0);
        mvprintw(0,0, "YOU are inside a Pokecenter");
        i = getch();
    }while(i != '<');

    clr_line(0,0);
    mvprintw(0,0, "YOU are exiting a Pokecenter");

}


int main(int argc, char* argv[])
{
    World *w = new World();
    int num_trainers = 12;
    if(argc > 1)
    {
        num_trainers = atoi(argv[2]);
    }

    init(w, num_trainers);
    string file_input, path;
    bool flag = false;

    cout << "Enter what file to output. Enter \"all\" to output everything\n";
    cin >> file_input;

    if(file_input == "all")
    {
        flag = true;
    }


    if(flag || file_input == "pokemon")
    {
        cout << "*************************************POKEMON*************************" << endl;
        path = get_database_path("pokemon");
        IO_pokemon pokemon(path);
        w->csv_pokemon = pokemon.pokemon_csv_data;
        pokemon.print();
    }
    if(flag || file_input == "moves")
    {
    cout << "*****************************************MOVES************************" << endl;
    path = get_database_path("moves");
    IO_moves moves(path);
    w->csv_moves = moves.moves_csv_data;
    moves.print();
    }
    if(flag || file_input == "pokemon_moves")
    {
        cout << "*********************************POKEMON**MOVES*************************" << endl;
        path = get_database_path("pokemon_moves");
        IO_pokemon_moves pokemon_moves(path);
        w->csv_pokemon_moves = pokemon_moves.pokemon_moves_csv_data;
        pokemon_moves.print();
    }
    if(flag || file_input == "pokemon_species")
    {
        cout << "******************************POKEMON**SPECIES*************************" << endl;
        path = get_database_path("pokemon_species");
        IO_pokemon_species pokemon_species(path);
        w->csv_pokemon_species = pokemon_species.pokemon_csv_species_data;
        pokemon_species.print();
    }
    if(flag || file_input == "experience")
    {
        cout << "******************************EXPERIENCE******************************" << endl;
        path = get_database_path("experience");
        IO_experience experience(path);
        w->csv_experience = experience.experience_csv_data;
        experience.print();
    }
    if(flag || file_input == "type_names")
    {
        cout << "******************************TYPE**NAMES******************************" << endl;
        path = get_database_path("type_names");
        IO_type_names type_names(path);
        w->csv_type_names = type_names.type_names_csv_data;
        type_names.print();
    }
    if(flag || file_input == "pokemon_stats")
    {
        cout << "******************************POKEMON**STATS******************************" << endl;
        path = get_database_path("pokemon_stats");
        IO_pokemon_stats pokemon_stats(path);
        w->csv_pokemon_stats = pokemon_stats.pokemon_stats_csv_data;
        pokemon_stats.print();
    }
    if(flag || file_input == "stats")
    {
        cout << "**************************************STATS******************************" << endl;
        path = get_database_path("stats");
        IO_stats stats(path);
        w->csv_stats = stats.stats_csv_data;
        stats.print();
    }
    if(flag || file_input == "pokemon_types")
    {
        cout << "********************************POKEMON**TYPES******************************" << endl;
        path = get_database_path("pokemon_types");
        IO_pokemon_types pokemon_types(path);
        w->csv_pokemon_types = pokemon_types.pokemon_types_csv_data;
        pokemon_types.print();
    }
    else{
        cout<< "ERRRRRRRR: Did not match any file name" << endl;
    }


//    initscr();
//    noecho();
//    curs_set(FALSE);
//    keypad(stdscr, TRUE);
//
//    mvaddstr(0,0, "Welcome to Pokemon game!");
//    refresh();
//
//    while(true)
//    {
//        int user_in = getch();
//        int o = 0;
//        MapStruct *curr_map = w->world[w->y][w->x];
//        clr_line(0,0);
//        switch (user_in)
//        {
//            case 52:
//            case 'h':
//            case 50:
//            case 'j': //Down
//            case 56:
//            case 'k': //Up
//            case 54:
//            case 'l': // Right
//            case 55:
//            case 'y': //upper left
//            case 57:
//            case 'u': //upper right
//            case 51:
//            case 'm': //lower right
//            case 49:
//            case 'b': //lower right
//            case 53:
//            case 32:
//            case 46:
//                move_pc(w, user_in);
//                simulate_movement(w->world[w->y][w->x]);
//                break;
//            case 't':
//                do
//                {
////                    user_in = getch();
//                    usleep(5000);
//                    if(user_in == KEY_UP)
//                    {
//                        o -= 5;
//                        o = (o < 0) ? 0 : o;
//
//                    }
//                    else if(user_in == KEY_DOWN)
//                    {
//                        o += 5;
//                    }
//                    else if(user_in == 27)
//                    {
//                        move(0, 0);
//                        clrtobot();
//                        map_print(w->world[w->y][w->x]);
//                        break;
//                    }
//                    print_trainers(w, o, o + 10);
//                    user_in = getch();
//                } while(true);
//
//                clr_line(0, 0);
//                mvaddstr(0, 0, "Exiting T Loop");
//                refresh();
//                break;
//            case '>': // >
//                if(curr_map->map[curr_map->player_pos->y][curr_map->player_pos->x] == POKE_MART)
//                {
//                    enter_poke_mart(w);
//                }
//                else if(curr_map->map[curr_map->player_pos->y][curr_map->player_pos->x] == POKE_CENTER)
//                {
//                    enter_poke_center(w);
//                }
//                break;
//
//            case 'f':
//            {
//                int nx = 0, ny = 0;
//                clr_line(0,0);
//                mvaddstr(0, 0, "Fly to where? (x, y)?\n");
//                mvscanw(0, 0, "%d %d \n", &nx, &ny);
//                move_dir(w, ny, nx, 0, num_trainers);
//            }
//            break;
//
//            case 'q':
//                endwin();
//                deinit(w);
//            return 0;
//
//            default:
//                clr_line(0, 0);
//                mvaddstr(0, 0, "Bruh. You had sooo many options to choose from and still you chose UNMAPPED INPUT");
//                refresh();
//        }
//        is_battling(w);
//
//        char latitude[11];
//        char longitude[11];
//        if(w->x < 200)
//        {
//            sprintf(latitude, "%s", "W");
//        }
//        else
//        {
//            sprintf(latitude, "%s", "E");
//        }
//
//        if(w->y < 200)
//        {
//            sprintf(longitude, "%s", "S");
//        }
//        else
//        {
//            sprintf(longitude, "%s", "N");
//        }
//
//        mvprintw(23, 0, "%d %s %d %s", abs(w->x), latitude, abs(w->y), longitude);
////        mvprintw(23, 0, "%d %s %d %s", abs(w->x - 200), latitude, abs(w->y - 200), longitude);
//
//    }
}