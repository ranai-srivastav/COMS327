//
// Created by ranai on 10/31/22.
//

#include "IO_Pokemon.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

IO_pokemon::IO_pokemon(string path)
{
    ifstream file;
    file.open(path);

    string line, word, temp, temp2;
    while(file>>temp)
    {
        getline(file, line);
        stringstream line_stream(temp);

        int i = 0;
//        IO_pokemon_struct *this_line = (IO_pokemon_struct *) malloc(sizeof(IO_pokemon_struct));
        IO_pokemon_struct *this_line = new IO_pokemon_struct;
        while(getline(line_stream, word, ','))
        {
            if(word == "id")
                break;
            switch(i)
            {
                case 0:
                    this_line->id = stoi(word);
                    break;
                case 1:
                    this_line->identifier = word;
                    break;
                case 2:
                    this_line->speciesID = stoi(word);
                    break;
                case 3:
                    this_line->height = stoi(word);
                    break;
                case 4:
                    this_line->weight = stoi(word);
                    break;
                case 5:
                    this_line->baseExperience = stoi(word);
                    break;
                case 6:
                    this_line->order = stoi(word);
                    break;
                case 7:
                    this_line->isDefault = stoi(word);
                    break;
            }
            i++;
        }
        pokemon_csv_data.push_back(this_line);
    }
}

void IO_pokemon::print()
{
    unsigned int len = pokemon_csv_data.size();
    unsigned int i = 0;

    for(i = 1; i<len; i++)
    {
        IO_pokemon_struct row = *pokemon_csv_data[i];

        std::cout<<
        ((row.id == INT32_MAX) ? "" : std::to_string(row.id)) << "," <<
        row.identifier << "," <<
        ((row.speciesID == INT32_MAX) ? "" : std::to_string(row.speciesID)) << "," <<
        ((row.height == INT32_MAX) ? "" : std::to_string(row.height)) << "," <<
        ((row.weight == INT32_MAX) ? "" : std::to_string(row.weight)) << "," <<
        ((row.baseExperience == INT32_MAX) ? "" : std::to_string(row.baseExperience)) << "," <<
        ((row.order == INT32_MAX) ? "" : std::to_string(row.order)) << "," <<
        ((row.isDefault == INT32_MAX) ? "" : std::to_string(row.isDefault)) << endl;
    }
}