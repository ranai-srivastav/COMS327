//
// Created by ranai on 11/2/22.
//

#ifndef RANAIS_POKEMON_IO_POKEMON_H
#define RANAIS_POKEMON_IO_POKEMON_H

//
// Created by ranai on 10/31/22.
//
#include <fstream>
#include <vector>

class IO_pokemon
{
public:
    typedef struct IO_pokemon_s
    {
        int id;
        std::string identifier;
        int speciesID;
        int height;
        int weight;
        int baseExperience;
        int order;
        int isDefault;
    }IO_pokemon_struct;

public:
    std::vector<IO_pokemon_struct*> pokemon_csv_data;

    explicit IO_pokemon(std::string path);

    void print();
};


#endif //RANAIS_POKEMON_IO_POKEMON_H
