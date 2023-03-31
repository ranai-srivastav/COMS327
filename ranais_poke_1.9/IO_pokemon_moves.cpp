//
// Created by ranai on 11/2/22.
//

#include "IO_pokemon_moves.h"
#include <vector>
#include <sstream>
#include<iostream>

using namespace std;

IO_pokemon_moves::IO_pokemon_moves(string path)
{
    ifstream file;
    file.open(path);

    string line, word, temp, temp2; //TODO remove temp2
    while(file>>temp)
    {
        getline(file, line);
        stringstream line_stream(temp);

        int i = 0;
//        IO_pokemon_struct *this_line = (IO_pokemon_struct *) malloc(sizeof(IO_pokemon_struct));
        IO_pokemon_moves_struct *this_line = new IO_pokemon_moves_struct;
        while(getline(line_stream, word, ','))
        {
            if(word == "pokemon_id")
                break;
            switch(i)
            {
                case 0:
                    this_line->pokemon_id = word.empty() ? INT32_MAX : stoi(word);
                    break;
                case 1:
                    this_line->version_group_id = word.empty() ? INT32_MAX : stoi(word);
                    break;
                case 2:
                    this_line->move_id = word.empty() ? INT32_MAX : stoi(word);
                    break;
                case 3:
                    this_line->pokemon_move_method_id = word.empty() ? INT32_MAX : stoi(word);
                    break;
                case 4:
                    this_line->level = word.empty() ? INT32_MAX : stoi(word);
                    break;
                case 5:
                    this_line->order = word.empty() ? INT32_MAX : stoi(word);
                    break;

            }
            i++;
        }
        pokemon_moves_csv_data.push_back(this_line);
    }
}

void IO_pokemon_moves::print()
{
    unsigned int len = pokemon_moves_csv_data.size();
    unsigned int i = 0;

    for(i = 1; i<len; i++)
    {
        IO_pokemon_moves_struct row = *pokemon_moves_csv_data[i];

        std::cout<<
        ((row.pokemon_id == INT32_MAX) ?  "" : std::to_string(row.pokemon_id)) << "," <<
        ((row.version_group_id == INT32_MAX) ? "" : std::to_string(row.version_group_id)) << "," <<
        ((row.move_id == INT32_MAX) ? "" : std::to_string(row.move_id)) << "," <<
        ((row.pokemon_move_method_id == INT32_MAX) ? "" : std::to_string(row.pokemon_move_method_id)) << "," <<
        ((row.level == INT32_MAX) ? "" : std::to_string(row.level)) << "," <<
        ((row.order == INT32_MAX) ? "" : std::to_string(row.order)) << "," << endl;
    }
}
