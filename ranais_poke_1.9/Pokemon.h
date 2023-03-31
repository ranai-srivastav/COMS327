//
// Created by ranai on 11/14/22.
//

#ifndef RANAIS_POKEMON_POKEMON_H
#define RANAIS_POKEMON_POKEMON_H

#include <ctime>
#include "world.h"
#include "cstddef"
#include "cstdlib"
#include "ncurses.h"
#include <cmath>

class Pokemon
{
public:
    int max_health;
    int HP;
    int attack;
    int defense;
    int speed;
    int sp_attack;
    int sp_defense;
    string gender;
    string isShiny = rand()%2 ? "TRUE" : "FALSE";
    int level;

    IO_pokemon_moves::IO_pokemon_moves_struct *random_move1, *random_move2;
    IO_pokemon::IO_pokemon_struct *poke;

    World *curr_world;

    Pokemon(World *w);

    Pokemon()
    {
        level = -1;
        poke = nullptr;
        HP = -1;
        attack = -1;
        defense = -1;
        speed = -1;
        sp_attack = -1;
        sp_defense = -1;
    };

    Pokemon(Pokemon const &p)
    {
        HP = p.HP;
        attack = p.attack;
        defense = p.defense;
        speed = p.speed;
        sp_defense = p.sp_defense;
        sp_attack = p.sp_attack;
        gender = p.gender;
        isShiny = p.isShiny;
        level = p.level;

        random_move1 = new IO_pokemon_moves::IO_pokemon_moves_s;
        random_move1->level = p.random_move1->level;
        random_move1->pokemon_id = p.random_move1->pokemon_id;
        random_move1->move_id = p.random_move1->move_id;
        random_move1->pokemon_move_method_id = p.random_move1->pokemon_move_method_id;
        random_move1->version_group_id = p.random_move1->version_group_id;
        random_move1->order = p.random_move1->order;

        random_move2 = new IO_pokemon_moves::IO_pokemon_moves_s;
        random_move2->level = p.random_move2->level;
        random_move2->pokemon_id = p.random_move2->pokemon_id;
        random_move2->move_id = p.random_move2->move_id;
        random_move2->pokemon_move_method_id = p.random_move2->pokemon_move_method_id;
        random_move2->version_group_id = p.random_move2->version_group_id;
        random_move2->order = p.random_move2->order;

        poke = new IO_pokemon::IO_pokemon_s;
        poke->identifier = p.poke->identifier;
        poke->id = p.poke->id;
        poke->speciesID = p.poke->speciesID;
        poke->height = p.poke->height;
        poke->weight = p.poke->weight;
        poke->order = p.poke->order;
        poke->isDefault = p.poke->isDefault;
        p.poke->baseExperience = p.poke->baseExperience;

        curr_world = p.curr_world;
    }

    void print();
};


#endif //RANAIS_POKEMON_POKEMON_H
