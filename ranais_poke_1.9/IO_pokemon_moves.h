//
// Created by ranai on 11/2/22.
//

#ifndef RANAIS_POKEMON_IO_POKEMON_MOVES_H
#define RANAIS_POKEMON_IO_POKEMON_MOVES_H

#include <fstream>
#include <vector>

class IO_pokemon_moves
{
public:
    typedef struct IO_pokemon_moves_s
    {
        int pokemon_id;
        int version_group_id;
        int move_id;
        int pokemon_move_method_id;
        int level;
        int order;
    }IO_pokemon_moves_struct;

    std::vector<IO_pokemon_moves_struct*> pokemon_moves_csv_data;

    explicit IO_pokemon_moves(std::string path);

    void print();
};

#endif //RANAIS_POKEMON_IO_POKEMON_MOVES_H
