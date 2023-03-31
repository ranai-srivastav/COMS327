//
// Created by ranai on 11/14/22.
//

#include "Pokemon.h"

Pokemon::Pokemon(World *w)
{
    curr_world = w;
    unsigned int i = 0;
    srand(time(NULL));

    unsigned int rand_id = rand() % 1093;
    poke = w->csv_pokemon[rand_id];

    vector<IO_pokemon_moves::IO_pokemon_moves_struct*> possible_moves;  // get all possible moves for theat poke

    clear();
    for(i = 0; i<w->csv_pokemon_moves.size(); i++)
    {
        if(w->csv_pokemon_moves[i]->pokemon_id == poke->speciesID && w->csv_pokemon_moves[i]->pokemon_move_method_id == 1)
        {
            possible_moves.push_back(w->csv_pokemon_moves[i]);
        }
    }


    unsigned int moveID1 = 0, moveID2 = 0;
    do
    {
        moveID1 = rand() % possible_moves.size();
        moveID2 = rand() % possible_moves.size();

    }while(moveID1 == moveID2);

    random_move1 = possible_moves[moveID1];
    random_move2 = possible_moves[moveID2];


//    do
//    {
//        random_move1 = possible_moves[rand() % possible_moves.size()];
//        random_move2 = possible_moves[rand() % possible_moves.size()];
//    }while(random_move1->move_id != random_move2->move_id);


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
    level = rand() % (int) man_dist + 1;

    if(level > 200)
    {
        level = 200;
    }

    HP = (int) floor(((HP_base+HP_IV)*2*level)/100) + level + 10;
    attack = (int) floor(((attack_base+attack_IV)*2*level)/100) + 5;
    defense = (int) floor(((defense_base+defense_IV)*2*level)/100) + 5;
    speed = (int) floor(((speed_base+speed_IV)*2*level)/100) + 5;
    sp_attack = (int) floor(((sp_att_base+sp_att_IV)*2*level)/100) + 5;
    sp_defense = (int) floor(((sp_def_base+sp_def_IV)*2*level)/100) + 5;


    switch(rand()%3){ case 0: gender = "MALE"; break; case 1: gender = "FEMALE"; break; case 2: gender = "NONE";}
    isShiny = rand()%2 ? "TRUE" : "FALSE";
}

void Pokemon::print()
{
    clear();
    WINDOW *pokemon_window = newwin(15,40, 0, 0);
    box(pokemon_window, 0, 0);
    mvprintw(1,1, "A Wild %s has appeared. Press any key to continue", poke->identifier.c_str());
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

    mvprintw(15,1, "This Pokemon has 2 moves");
    mvprintw(16,1, "Move 1 %s", curr_world->csv_moves[random_move1->move_id]->identifier.c_str());
    mvprintw(17,1, "Move 2 %s", curr_world->csv_moves[random_move2->move_id]->identifier.c_str());

    refresh();
}

/**
void Pokemon::gen_pokemon(World *w)
{
    srand(time(NULL));

    int poke_id = rand() % w->csv_pokemon.size();  // generate random Pokemon id
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
    int level = rand() % (int) man_dist + 1;

    if(level > 200)
    {
        level = 200;
    }

    HP = (int) floor(((HP_base+HP_IV)*2*level)/100) + level + 10;
    attack = (int) floor(((attack_base+attack_IV)*2*level)/100) + 5;
    defense = (int) floor(((defense_base+defense_IV)*2*level)/100) + 5;
    speed = (int) floor(((speed_base+speed_IV)*2*level)/100) + 5;
    sp_attack = (int) floor(((sp_att_base+sp_att_IV)*2*level)/100) + 5;
    sp_defense = (int) floor(((sp_def_base+sp_def_IV)*2*level)/100) + 5;
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


    mvprintw(15,1, "This Pokemon has 2 moves");
    mvprintw(16,1, "Move 1 %s", w->csv_moves[possible_moves[rand() % possible_moves.size()]->move_id]->identifier.c_str());
    mvprintw(17,1, "Move 2 %s", w->csv_moves[possible_moves[rand() % possible_moves.size()]->move_id]->identifier.c_str());

    refresh();
    getch();
}
**/
