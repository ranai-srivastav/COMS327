//
// Created by ranai on 11/2/22.
//

#ifndef RANAIS_POKEMON_IO_MOVES_H
#define RANAIS_POKEMON_IO_MOVES_H
#include <fstream>
#include <vector>

class IO_moves
{
public:
    typedef struct IO_moves_s
    {
        int id;
        std::string identifier;
        int generation_id;
        int type_id;
        int power;
        int pp;
        int accuracy;
        int priority;
        int target_id;
        int damage_class_id;
        int effect_id;
        int effect_chance;
        int contest_type_id;
        int contest_effect_id;
        int super_contest_effect_i;
    }IO_moves_struct;

    std::vector<IO_moves_struct*> moves_csv_data;


    explicit IO_moves(std::string path);

    void print(void);
};


#endif //RANAIS_POKEMON_IO_MOVES_H
