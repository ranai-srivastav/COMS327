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
#include "Pokemon.h"

/**
 * @file game.c
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The main code for the game. Syncs values between map.c and world.c and their respective data structures.
 * @version 2
 * @date 28th Oct, 2022
 */

using namespace std;

static Pokemon *pc_poke[6];
static int pc_num_poke = 0;

void clr_line(int y, int x)
{
    move(y, x);
    refresh();
    clrtoeol();
    refresh();
}


void open_bag(World *w)
{
    clear();
    refresh();

    WINDOW *bag_win = newwin(40, 40, 0, 0);
    mvwprintw(bag_win, 0, 0, "****BAG INVENTORY****");
    mvwprintw(bag_win, 1, 0, "Input the first letter to use items. `b` to exit.");
    wrefresh(bag_win);

    mvwprintw(bag_win, 3, 0, "     Item           Count");
    int i = 0;
    for(auto key: w->bag)
    {
        mvwprintw(bag_win, 5 + i, 0, "%c>  %-14s %d", key.first[0], key.first.c_str(), key.second);
        i++;
    }
    wrefresh(bag_win);
    int user_in = getch();
    switch(user_in)
    {
        case 'r':
            clear();
            refresh();
            mvprintw(1, 0, "These are your pokemon. Which Pokemon's health do you wish to restore to 50%% of max?");
            mvprintw(3, 0, "%d> %15s:   Level %5d   HP: %5d", 0, (pc_poke[0]->poke->identifier).c_str(),
                     pc_poke[0]->level, pc_poke[0]->HP);

            i = 1;
            while(i < 6)
            {
                if(pc_poke[i] != nullptr)
                    mvprintw(3 + i, 0, "%d> %15s:   Level %5d   HP: %5d", i, (pc_poke[i]->poke->identifier).c_str(),
                             pc_poke[i]->level, pc_poke[i]->HP);
                i++;
            }
            wrefresh(bag_win);
            user_in = getch()-48;

            pc_poke[user_in]->HP = pc_poke[user_in]->max_health / 2;
            w->bag["revive"] = w->bag["revive"] - 1;
            break;

        case 'e':
            clear();
            refresh();
            mvprintw(1, 0, "These are your pokemon. Which one do you wish to add 20 HP to?");
            mvprintw(3, 0, "%d> %15s:   Level %5d   HP: %5d", 0, (pc_poke[0]->poke->identifier).c_str(),
                     pc_poke[0]->level, pc_poke[0]->HP);

            i = 1;
            while(i < 6)
            {
                if(pc_poke[i] != nullptr)
                    mvprintw(3 + i, 0, "%d> %15s:   Level %5d   HP: %5d", i, (pc_poke[i]->poke->identifier).c_str(),
                             pc_poke[i]->level, pc_poke[i]->HP);
                i++;
            }

            user_in = getch()-48;

            pc_poke[user_in]->HP =
                    pc_poke[user_in]->HP + 20 > pc_poke[user_in]->max_health ?
                    pc_poke[user_in]->max_health : pc_poke[user_in]->HP + 20;
            w->bag["elixir"] = w->bag["elixir"] - 1;
            break;

        case 'p':
            break;
    }
    clear();
    refresh();
    endwin();
}

void battle_npc(World *w, string player)
{
    clear();
    refresh();

    WINDOW *battle_win = newwin(40, 66, 20, 20);
    box(battle_win, 20, 20);

    mvprintw(0, 0, "**************Entering Battle with %s******************", player.c_str());
    refresh();

    clear();
    refresh();

    int i = 0;
    bool battle = true;
    int num_npc_poke = rand() % 5 + 1;
    Pokemon non_pc_poke[num_npc_poke];

    non_pc_poke[0] = Pokemon(w);

    for(i = 1; i < num_npc_poke; i++)
    {
        non_pc_poke[i] = Pokemon(w);

        while(non_pc_poke[i].poke->speciesID == non_pc_poke[i - 1].poke->speciesID)
        {
            non_pc_poke[i] = Pokemon(w);
        }
    }

    mvprintw(0, 0, "**************You are fighting %s******************", player.c_str());
    mvprintw(1, 0, "These are your pokemon. Press any key to continue");
    mvprintw(1, 0, "These are your pokemon.");
    mvprintw(3, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", 0, (pc_poke[0]->poke->identifier).c_str(),
             pc_poke[0]->level, pc_poke[0]->HP, w->csv_moves[pc_poke[0]->random_move1->move_id]->identifier.c_str(),
             w->csv_moves[pc_poke[0]->random_move2->move_id]->identifier.c_str());

    i = 1;
    while(i < 6)
    {
        if(pc_poke[i] != nullptr)
            mvprintw(3 + i, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", i,
                     (pc_poke[i]->poke->identifier).c_str(), pc_poke[i]->level, pc_poke[i]->HP,
                     w->csv_moves[pc_poke[i]->random_move1->move_id]->identifier.c_str(),
                     w->csv_moves[pc_poke[i]->random_move2->move_id]->identifier.c_str());
        i++;
    }

    getch();
    clear();
    refresh();

    int pc_poke_choice = -1, non_pc_poke_choice = -1, pc_move_choice = -1, non_pc_move_choice = -1;
    bool validInput = true;

    while(battle)
    {
        for(i = 0; i < 6; i++)
        {
            mvprintw(20, 0, "%d", i);
            refresh();
            if(pc_poke[i] != nullptr && pc_poke[i]->HP >= 1)
            {
                break;
            }
        }
        if(i == 6)
        {
            clear();
            refresh();

            mvprintw(0, 0, "All your pokemon have passed out. Match lost.");
            getch();
            battle = false;
            return;
        }

        mvprintw(1, 0, "These are your pokemon.");
        mvprintw(3, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", 0, (pc_poke[0]->poke->identifier).c_str(),
                 pc_poke[0]->level, pc_poke[0]->HP, w->csv_moves[pc_poke[0]->random_move1->move_id]->identifier.c_str(),
                 w->csv_moves[pc_poke[0]->random_move2->move_id]->identifier.c_str());

        i = 1;
        while(i < 6)
        {
            if(pc_poke[i] != nullptr)
                mvprintw(3 + i, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", i,
                         (pc_poke[i]->poke->identifier).c_str(), pc_poke[i]->level, pc_poke[i]->HP,
                         w->csv_moves[pc_poke[i]->random_move1->move_id]->identifier.c_str(),
                         w->csv_moves[pc_poke[i]->random_move2->move_id]->identifier.c_str());
            i++;
        }

        do
        {
            mvaddstr(10, 0, "Pick a Pokemon");
            refresh();
            pc_poke_choice = getch();
            if(pc_poke_choice == 'q') return;
            pc_poke_choice = pc_poke_choice - 48;
            if(pc_poke_choice >= 6 || pc_poke[pc_poke_choice]->HP <= 1)
                mvaddstr(11, 0, "INCORRECT. Valid numbers are between 0-5 and each pokemon must have health");
        } while(pc_poke[pc_poke_choice] == nullptr || pc_poke[pc_poke_choice]->HP <= 1);

        clr_line(11, 0);
        mvaddstr(11, 0, "Pick a move. 1,2 for current Pokemon moves. 3 to change Pokemon.");
        refresh();
        pc_move_choice = getch();

        switch(pc_move_choice)
        {
            case '0':
                pc_move_choice = 1;
                mvprintw(12, 0, "You chose move %d for Pokemon %d", pc_move_choice, pc_poke_choice);
                refresh();
                validInput = true;
                break;

            case '1':
                pc_move_choice = 1;
                mvprintw(12, 0, "You chose move %d for Pokemon %d", pc_move_choice, pc_poke_choice);
                refresh();
                validInput = true;
                break;

            case '2':
                pc_move_choice = 2;
                mvprintw(12, 0, "You chose move %d for Pokemon %d", pc_move_choice, pc_poke_choice);
                refresh();
                validInput = true;
                break;

            case '3':
                mvprintw(12, 0, "Pick one of the Pokemon listed above");
                refresh();
                pc_poke_choice = getch() - 48;
                break;

            case 'q':
                validInput = true;
                break;

            default:
                validInput = false;
                clear();
                refresh();
        }

        non_pc_poke_choice = rand() % num_npc_poke;
        non_pc_move_choice = rand() % 2 + 1;

        mvprintw(35, 0, "Enemy %s has %d health", non_pc_poke[non_pc_poke_choice].poke->identifier.c_str(), non_pc_poke[non_pc_poke_choice].HP);
        refresh();

        int inner_bracket = (2 * pc_poke[pc_poke_choice]->level / 5) + 2;
        int ratio = pc_poke[pc_poke_choice]->attack / pc_poke[pc_poke_choice]->defense;
        getch();
        int left_bracket;

        if(pc_move_choice == 1)
        {
            left_bracket =
                    ((inner_bracket * w->csv_moves[pc_poke[pc_poke_choice]->random_move1->move_id]->power * ratio) /
                     50) + 2;
        }
        else
        {
            left_bracket =
                    ((inner_bracket * w->csv_moves[pc_poke[pc_poke_choice]->random_move2->move_id]->power * ratio) /
                     50) + 2;
        }

        int pc_damage = left_bracket * ((rand() % 4) / 2.0) * (rand() % 16) + 85 * 1 * 1;

        inner_bracket = (2 * pc_poke[pc_poke_choice]->level / 5) + 2;
        ratio = pc_poke[pc_poke_choice]->attack / pc_poke[pc_poke_choice]->defense;

        if(pc_move_choice == 1)
        {
            left_bracket =
                    ((inner_bracket * w->csv_moves[pc_poke[pc_poke_choice]->random_move1->move_id]->power * ratio) /
                     50) + 2;
        }
        else
        {
            left_bracket =
                    ((inner_bracket * w->csv_moves[pc_poke[pc_poke_choice]->random_move2->move_id]->power * ratio) /
                     50) + 2;
        }

        int non_pc_damage = left_bracket * ((rand() % 4) / 2.0) * (rand() % 16) + 85 * 1 * 1;

        mvprintw(12, 0, "Your %s attacked %s for %d damage.", pc_poke[pc_poke_choice]->poke->identifier.c_str(),
                 non_pc_poke[non_pc_poke_choice].poke->identifier.c_str(), pc_damage);
        mvprintw(13, 0, "Their %s attacked your %s for %d damage.",
                 non_pc_poke[non_pc_poke_choice].poke->identifier.c_str(),
                 pc_poke[pc_poke_choice]->poke->identifier.c_str(), non_pc_damage);
        getch();
        refresh();

        pc_poke[pc_poke_choice]->HP -= non_pc_damage;
        non_pc_poke[non_pc_poke_choice].HP -= pc_damage;

        erase();
        refresh();

        WINDOW *poke_battle_win = newwin(40, 66, 20, 20);
        box(poke_battle_win, 20, 20);

        for(i = 0; i < num_npc_poke; i++)
        {
            if(non_pc_poke[i].HP >= 1)
            {
                break;
            }
        }
        if(i == num_npc_poke)
        {
            clear();
            refresh();

            mvprintw(0, 0, "You won against %s", player.c_str());
            getch();
            battle = false;
            return;
        }


        for(i = 0; i < 6; i++)
        {
            mvprintw(20, 0, "%d", i);
            refresh();
            if(pc_poke[i] != nullptr && pc_poke[i]->HP >= 1)
            {
                break;
            }
        }
        if(i == 6)
        {
            clear();
            refresh();

            mvprintw(0, 0, "You lost against %s", player.c_str());
            getch();
            battle = false;
            return;
        }

        endwin();
    }
}

void battle_pokemon(World *w, Pokemon *enemy)
{
    clear();
    refresh();

    WINDOW *battle_win = newwin(40, 75, 20, 20);
    box(battle_win, 20, 20);

    int i = 0;
    bool battle = true;

    mvprintw(0, 0, "**************You are fighting %s******************", enemy->poke->identifier.c_str());
    usleep(1000);
    enemy->print();
    getch();
    clear();
    refresh();

    int pc_poke_choice = -1, pc_move_choice = -1, enemy_move_choice = -1;
    bool validInput = true;

    enemy->max_health = enemy->HP;

    while(battle)
    {
        for(i = 0; i < 6; i++)
        {
            mvprintw(20, 0, "%d", i);
            refresh();
            if(pc_poke[i] != nullptr && pc_poke[i]->HP >= 1)
            {
                break;
            }
        }
        if(i == 6)
        {
            clear();
            refresh();

            mvprintw(0, 0, "All your pokemon have passed out. Match lost.");
            getch();
            battle = false;
            return;
        }
        
        mvprintw(1, 0, "These are your pokemon.");
        mvprintw(3, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", 0, (pc_poke[0]->poke->identifier).c_str(),
                 pc_poke[0]->level, pc_poke[0]->HP, w->csv_moves[pc_poke[0]->random_move1->move_id]->identifier.c_str(),
                 w->csv_moves[pc_poke[0]->random_move2->move_id]->identifier.c_str());

        i = 1;
        while(i < 6)
        {
            if(pc_poke[i] != nullptr)
                mvprintw(3 + i, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", i,
                         (pc_poke[i]->poke->identifier).c_str(), pc_poke[i]->level, pc_poke[i]->HP,
                         w->csv_moves[pc_poke[i]->random_move1->move_id]->identifier.c_str(),
                         w->csv_moves[pc_poke[i]->random_move2->move_id]->identifier.c_str());
            i++;
        }

        do
        {
            mvprintw(1, 0, "These are your pokemon.");
            mvprintw(3, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", 0, (pc_poke[0]->poke->identifier).c_str(),
                     pc_poke[0]->level, pc_poke[0]->HP, w->csv_moves[pc_poke[0]->random_move1->move_id]->identifier.c_str(),
                     w->csv_moves[pc_poke[0]->random_move2->move_id]->identifier.c_str());

            i = 1;
            while(i < 6)
            {
                if(pc_poke[i] != nullptr)
                    mvprintw(3 + i, 0, "%d> %20s:  Level:%2d   HP:%2d   M1:%s   M2:%s", i,
                             (pc_poke[i]->poke->identifier).c_str(), pc_poke[i]->level, pc_poke[i]->HP,
                             w->csv_moves[pc_poke[i]->random_move1->move_id]->identifier.c_str(),
                             w->csv_moves[pc_poke[i]->random_move2->move_id]->identifier.c_str());
                i++;
            }

            mvaddstr(10, 0, "Pick a pokemon. `b` to use potions");
            refresh();
            pc_poke_choice = getch();
            if(pc_poke_choice == 'q') return;
            if(pc_poke_choice == 'b')
            {
                open_bag(w);
            }

            pc_poke_choice = pc_poke_choice - 48;
            if(pc_poke_choice >= 6 || pc_poke[pc_poke_choice]->HP <= 1)
                mvaddstr(11, 0, "Pick again if you chose `b`. Valid numbers are between 0-5 and each pokemon must have health");
        } while(pc_poke[pc_poke_choice] == nullptr || pc_poke[pc_poke_choice]->HP <= 1);

        mvaddstr(11, 0, "Pick a move. 1,2 for current pokemon moves. 3 to change pokemon.");
        refresh();
        pc_move_choice = getch();

        switch(pc_move_choice)
        {
            case '0':
                pc_move_choice = 1;
                mvprintw(12, 0, "You chose move %d for pokemon %d", pc_move_choice, pc_poke_choice);
                refresh();
                validInput = true;
                break;

            case '1':
                pc_move_choice = 1;
                mvprintw(12, 0, "You chose move %d for pokemon %d", pc_move_choice, pc_poke_choice);
                refresh();
                validInput = true;
                break;

            case '2':
                pc_move_choice = 2;
                mvprintw(12, 0, "You chose move %d for pokemon %d", pc_move_choice, pc_poke_choice);
                refresh();
                validInput = true;
                break;

            case '3':
                mvprintw(12, 0, "Pick one of the pokemon listed above");
                refresh();
                pc_poke_choice = getch() - 48;
                break;

            case 'b':
                open_bag(w);
            break;

            case 'p':
                mvprintw(12, 0, "Attempting to capture %s", enemy->poke->identifier.c_str());
                if(rand()%256 > 193)
                {
                    w->bag["pokeballs"] -= 1;
                    mvprintw(12, 0, "Battle over. Successfully captured %s. Press any key to continue.", enemy->poke->identifier.c_str());
                    refresh();
                    getch();
                    return;
                }
                else
                {
                    mvprintw(12, 0, "Failed to capture %s. Battle continues", enemy->poke->identifier.c_str());
                }
                break;

            case 'q':
                validInput = true;
                return;

            default:
                validInput = false;
                clear();
                refresh();
        }

        enemy_move_choice = rand() % 2 + 1;
        mvprintw(35, 0, "Enemy %s has %d health", enemy->poke->identifier.c_str(), enemy->HP);
        refresh();

        int inner_bracket = (2 * pc_poke[pc_poke_choice]->level / 5) + 2;
        int ratio = pc_poke[pc_poke_choice]->attack / pc_poke[pc_poke_choice]->defense;
        int left_bracket;

        if(pc_move_choice == 1)
        {
            left_bracket =
                    ((inner_bracket * w->csv_moves[pc_poke[pc_poke_choice]->random_move1->move_id]->power * ratio) /
                     50) + 2;
        }
        else
        {
            left_bracket =
                    ((inner_bracket * w->csv_moves[pc_poke[pc_poke_choice]->random_move2->move_id]->power * ratio) /
                     50) + 2;
        }

        int pc_damage = left_bracket * ((rand() % 4) / 2.0) * (rand() % 16) + 85 * 1 * 1;


        inner_bracket = (2 * pc_poke[pc_poke_choice]->level / 5) + 2;
        ratio = pc_poke[pc_poke_choice]->attack / pc_poke[pc_poke_choice]->defense;
        if(enemy_move_choice == 1)
        {
            left_bracket = ((inner_bracket * w->csv_moves[enemy->random_move1->move_id]->power * ratio) / 50) + 2;
        }
        else
        {
            left_bracket = ((inner_bracket * w->csv_moves[enemy->random_move2->move_id]->power * ratio) / 50) + 2;
        }

        int enemy_damage = left_bracket * ((rand() % 4) / 2.0) * (rand() % 16) + 85 * 1 * 1;

        mvprintw(14, 0, "Your %s attacked %s for %d damage.", pc_poke[pc_poke_choice]->poke->identifier.c_str(),
                 enemy->poke->identifier.c_str(), pc_damage);
        mvprintw(15, 0, "Their %s attacked your %s for %d damage.", enemy->poke->identifier.c_str(),
                 pc_poke[pc_poke_choice]->poke->identifier.c_str(), enemy_damage);
        mvprintw(16, 0, "press any button to continue");
        getch();
        refresh();

        pc_poke[pc_poke_choice]->HP -= enemy_damage;
        enemy->HP -= pc_damage;

        erase();
        refresh();

        WINDOW *poke_battle_win = newwin(40, 66, 20, 20);
        box(poke_battle_win, 20, 20);

        if(pc_poke[pc_poke_choice]->HP <= 1)
        {
            clr_line(0, 0);
            mvprintw(0, 0, "Pokemon %s is knocked out. Press any key to continue",
                     pc_poke[pc_poke_choice]->poke->identifier.c_str());
            refresh();

        }

        if(enemy->HP <= 0)
        {
            battle = false;

            mvprintw(0, 0,
                     "You won against %s. You can choose to add him to your pokemon by entering 0-5 or ignore by entering `n`",
                     enemy->poke->identifier.c_str());
            mvprintw(1, 0, "You can only add a pokemon if you have an empty spot, else it will fail");

            pc_move_choice = getch() - 48;

            if(pc_move_choice >= 0 && pc_move_choice <= 5)
            {
                pc_poke[pc_move_choice] = new Pokemon(*enemy);
                return;
            }
        }

        i = 0;

    }
}

void is_battling(World *w)
{
    int i = 0;
    MapStruct *curr_map = w->world[w->y][w->x];
    int pc_x = curr_map->player_pos->x;
    int pc_y = curr_map->player_pos->y;

    for(i = 0; i < w->world[w->y][w->x]->num_players; i++)
    {
        ll_node_t *node = ll_get(w->world[w->y][w->x]->player_positions, i);

        if((abs(pc_y - node->curr_pos_y) <= 1 && abs(pc_x - node->curr_pos_x) <= 1) && node->has_fought == 0)
        {
            clr_line(0, 0);
            mvprintw(0, 0, "Fighting with (%d %d) from (%d, %d)", node->curr_pos_y, node->curr_pos_x, pc_y, pc_x);
            node->has_fought = 1;
            battle_npc(w, node->player_type_string);
        }
    }
}

void print_trainers(World *w, int start, int end)
{
    MapStruct *curr_map = w->world[w->y][w->x];
    int i = 0;

    for(i = start; i < end && i < curr_map->num_players; i++)
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
            sprintf(vert, "%d %s", curr_node->curr_pos_y - pc_y, "SOUTH");
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
        mvprintw(28 + i, 0, "%s: %s %s", c, vert, hori);
        refresh();
    }
}

void enter_poke_mart(World *w)
{
    int i = 0;
    do
    {
        clr_line(0, 0);
        mvprintw(0, 0, "YOU are inside a Pokemart. Your bag will replenish");

        w->bag["pokeballs"] = 5;
        w->bag["revive"] = 3;
        w->bag["elixir"] = 3;
        i = getch();
    } while(i != '<');

    clr_line(0, 0);
    mvprintw(0, 0, "YOU are exiting a Pokemart");

}

void enter_poke_center(World *w)
{
    int i = 0;
    do
    {
        clr_line(0, 0);
        mvprintw(0, 0, "YOU are inside a Pokecenter. All your Pokemon will heal");

        for(i = 0; i<6; i++)
        {
            if(pc_poke[i] != nullptr)
                pc_poke[i]->HP = pc_poke[i]->max_health;
        }

        i = getch();
    } while(i != '<');

    clr_line(0, 0);
    mvprintw(0, 0, "YOU are exiting a Pokecenter. All your pokemon are healed");

}

void gen_3_pokemon(World *w)
{
    clear();

    /** Generate 3 random pokemon and have  **/
    Pokemon poke1 = Pokemon(w);     //876 ineedee-male
    Pokemon poke2 = Pokemon(w);
    Pokemon poke3 = Pokemon(w);

    do
    {
        poke2 = Pokemon(w);

    } while(poke1.poke->speciesID == poke2.poke->speciesID);

    do
    {
        poke3 = Pokemon(w);

    } while(poke2.poke->speciesID == poke3.poke->speciesID);

    bool flag = false;
    do
    {
        WINDOW *start_screen = newwin(20, 66, 0, 0);
        box(start_screen, 0, 0);
        mvprintw(1, 33, "%s", "welcome to pokemon");
        mvprintw(3, 33, "%s", "Choose one of the following three pokemon");
        mvprintw(5, 33, "a> %s", poke1.poke->identifier.c_str());
        mvprintw(6, 33, "b> %s", poke2.poke->identifier.c_str());
        mvprintw(7, 33, "c> %s", poke3.poke->identifier.c_str());

        refresh();


        int val = getch();
        endwin();
        clear();

        switch(val)
        {
            case 'a':
                mvprintw(0, 0, "You have selected %s as your first pokemon", poke1.poke->identifier.c_str());
                pc_poke[0] = new Pokemon(poke1);
                flag = false;
                break;
            case 'b':
                mvprintw(0, 0, "You have selected %s as your first pokemon", poke2.poke->identifier.c_str());
                pc_poke[0] = new Pokemon(poke2);
                flag = false;
                break;
            case 'c':
                mvprintw(0, 0, "You have selected %s as your first pokemon", poke3.poke->identifier.c_str());
                pc_poke[0] = new Pokemon(poke3);
                flag = false;
                break;
            default:
                flag = true;
        }
    } while(flag);

    pc_poke[0]->max_health = pc_poke[0]->HP;
}

int main(int argc, char *argv[])
{

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    mvaddstr(0, 0, "Welcome to Pokemon game!");
    refresh();

    World *w = new World();
    int num_trainers = 12;
    if(argc > 1)
    {
        num_trainers = atoi(argv[2]);
    }

    init(w, num_trainers);
    string path;

    //reading csv files
    path = get_database_path("pokemon");
    IO_pokemon pokemon(path);
    w->csv_pokemon = pokemon.pokemon_csv_data;
//    printf("pokemon: %zu", w->csv_pokemon.size());

    path = get_database_path("moves");
    IO_moves moves(path);
    w->csv_moves = moves.moves_csv_data;
//    mvprintw(1,0, "moves: %zu", w->csv_moves.size());
//    refresh();

    path = get_database_path("pokemon_moves");
    IO_pokemon_moves pokemon_moves(path);
    w->csv_pokemon_moves = pokemon_moves.pokemon_moves_csv_data;


    path = get_database_path("pokemon_species");
    IO_pokemon_species pokemon_species(path);
    w->csv_pokemon_species = pokemon_species.pokemon_csv_species_data;

    path = get_database_path("experience");
    IO_experience experience(path);
    w->csv_experience = experience.experience_csv_data;


    path = get_database_path("type_names");
    IO_type_names type_names(path);
    w->csv_type_names = type_names.type_names_csv_data;

    path = get_database_path("pokemon_stats");
    IO_pokemon_stats pokemon_stats(path);
    w->csv_pokemon_stats = pokemon_stats.pokemon_stats_csv_data;

    path = get_database_path("stats");
    IO_stats stats(path);
    w->csv_stats = stats.stats_csv_data;

    path = get_database_path("pokemon_types");
    IO_pokemon_types pokemon_types(path);
    w->csv_pokemon_types = pokemon_types.pokemon_types_csv_data;

    gen_3_pokemon(w);
    pc_num_poke = 1;
    int i = 0;
    for(i = 1; i < 6; i++)
    {
        pc_poke[i] = nullptr;
    }

    while(true)
    {
        map_print(w->world[w->y][w->x]);
        int user_in = getch();
        int o = 0;
        MapStruct *curr_map = w->world[w->y][w->x];
        clr_line(0, 0);
        switch(user_in)
        {
            case 52:
            case 'h':
            case 50:
            case 'j': //Down
            case 56:
            case 'k': //Up
            case 54:
            case 'l': // Right
            case 55:
            case 'y': //upper left
            case 57:
            case 'u': //upper right
            case 51:
            case 'm': //lower right
            case 49:
            case 'v': //lower right
            case 53:
            case 32:
            case 46:
                if(move_pc(w, user_in))
                {
                    Pokemon p = Pokemon(w);
                    battle_pokemon(w, &p);
                }
                simulate_movement(w->world[w->y][w->x]);
                break;

            case 'b':
                open_bag(w);
                break;
            case 't':
                do
                {
//                    user_in = getch();
//                    usleep(5000);
                    if(user_in == KEY_UP)
                    {
                        o -= 5;
                        o = (o < 0) ? 0 : o;

                    }
                    else if(user_in == KEY_DOWN)
                    {
                        o += 5;
                    }
                    else if(user_in == 27)
                    {
                        move(0, 0);
                        clrtobot();
                        map_print(w->world[w->y][w->x]);
                        break;
                    }
                    print_trainers(w, o, o + 10);
                    user_in = getch();
                } while(true);

                clr_line(0, 0);
                mvaddstr(0, 0, "Exiting T Loop");
                refresh();
                break;
            case '>': // >
                if(curr_map->map[curr_map->player_pos->y][curr_map->player_pos->x] == POKE_MART)
                {
                    enter_poke_mart(w);
                }
                else if(curr_map->map[curr_map->player_pos->y][curr_map->player_pos->x] == POKE_CENTER)
                {
                    enter_poke_center(w);
                }
                break;

            case 'f':
            {
                int nx = 0, ny = 0;
                clr_line(0, 0);
                mvaddstr(0, 0, "Fly to where? (x, y)?\n");
                mvscanw(0, 0, "%d %d \n", &nx, &ny);
                move_dir(w, ny, nx, 0, num_trainers);
            }
                break;

            case 'q':
                endwin();
                deinit(w);
                return 0;

            default:
                clr_line(0, 0);
                mvaddstr(0, 0, "Bruh. You had sooo many options to choose from and still you chose UNMAPPED INPUT");
                refresh();
        }
        map_print(w->world[w->y][w->x]);
        refresh();
        is_battling(w);

        char latitude[11];
        char longitude[11];
        if(w->x < 200)
        {
            sprintf(latitude, "%s", "W");
        }
        else
        {
            sprintf(latitude, "%s", "E");
        }

        if(w->y < 200)
        {
            sprintf(longitude, "%s", "S");
        }
        else
        {
            sprintf(longitude, "%s", "N");
        }

        mvprintw(23, 0, "%d %s %d %s", abs(w->x), latitude, abs(w->y), longitude);
//        mvprintw(23, 0, "%d %s %d %s", abs(w->x - 200), latitude, abs(w->y - 200), longitude);

    }
}