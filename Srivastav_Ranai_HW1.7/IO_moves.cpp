//
// Created by ranai on 11/2/22.
//

#include "IO_moves.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

IO_moves::IO_moves(std::string path)
{
    ifstream file;
    file.open(path);

    string line, word, temp;
    while(file>>line)
    {
        getline(file, temp);
        stringstream line_stream(line);

        int i = 0;
//        IO_pokemon_struct *this_line = (IO_pokemon_struct *) malloc(sizeof(IO_pokemon_struct));
        IO_moves_struct *this_line = new IO_moves_struct ;
        while(getline(line_stream, word, ','))
        {
            if(word == "id")
                break;
            switch(i)
            {
                case 0:
                    if(word.empty())
                        this_line->id = INT32_MAX;
                    else
                        this_line->id = stoi(word);
                    break;
                case 1:
                    this_line->identifier = word;
                    break;
                case 2:
                    if(word.empty())
                        this_line->generation_id = INT32_MAX;
                    else
                        this_line->generation_id = stoi(word);
                    break;
                case 3:
                    if(word.empty())
                        this_line->type_id = INT32_MAX;
                    else
                        this_line->type_id = stoi(word);
                    break;
                case 4:
                    if(word .empty())
                        this_line->power = INT32_MAX;
                    else
                        this_line->power = stoi(word);
                    break;
                case 5:
                    if(word.empty())
                        this_line->pp = INT32_MAX;
                    else
                        this_line->pp = stoi(word);
                    break;
                case 6:
                    if(word.empty())
                        this_line->accuracy = INT32_MAX;
                    else
                        this_line->accuracy = stoi(word);
                    break;
                case 7:
                    if(word.empty())
                        this_line->priority = INT32_MAX;
                    else
                        this_line->priority = stoi(word);
                    break;
                case 8:
                    if(word.empty())
                        this_line->target_id = INT32_MAX;
                    else
                        this_line->target_id = stoi(word);
                    break;
                case 9:
                    if(word.empty())
                        this_line->damage_class_id = INT32_MAX;
                    else
                        this_line->damage_class_id = stoi(word);
                    break;
                case 10:
                    if(word.empty())
                        this_line->effect_id = INT32_MAX;
                    else
                        this_line->effect_id = stoi(word);
                    break;
                case 11:
                    if(word.empty())
                        this_line->effect_chance = INT32_MAX;
                    else
                        this_line->effect_chance = stoi(word);
                    break;
                case 12:
                    if(word.empty())
                        this_line->contest_type_id = INT32_MAX;
                    else
                        this_line->contest_type_id = stoi(word);
                    break;
                case 13:
                    if(word.empty())
                        this_line->contest_effect_id = INT32_MAX;
                    else
                        this_line->contest_effect_id = stoi(word);
                    break;
                case 14:
                    if(word.empty())
                        this_line->super_contest_effect_i = INT32_MAX;
                    else
                        this_line->super_contest_effect_i = stoi(word);
                    break;
            }
            i++;
        }
        moves_csv_data.push_back(this_line);
    }
}

void IO_moves::print()
{
    unsigned int len = moves_csv_data.size();
    unsigned int i = 0;

    for(i = 1; i<len; i++)
    {
        IO_moves_struct row = *moves_csv_data[i];

        std::cout <<
        ((row.id == INT32_MAX) ? "" : std::to_string(row.id)) << "," <<
        row.identifier << "," <<
        ((row.generation_id == INT32_MAX) ? "" : std::to_string(row.generation_id)) << "," <<
        ((row.type_id == INT32_MAX) ? "" : std::to_string(row.type_id)) << "," <<
        ((row.power == INT32_MAX) ? "" : std::to_string(row.power)) << "," <<
        ((row.pp == INT32_MAX) ? "" : std::to_string(row.pp)) << "," <<
        ((row.accuracy == INT32_MAX) ? "" : std::to_string(row.accuracy) )<< "," <<
        ((row.priority == INT32_MAX) ? "" : std::to_string(row.priority)) << "," <<
        ((row.target_id == INT32_MAX) ? "" : std::to_string(row.target_id)) << "," <<
        ((row.damage_class_id == INT32_MAX) ? "" : std::to_string(row.damage_class_id)) << "," <<
        ((row.effect_id == INT32_MAX) ? "" : std::to_string(row.effect_id)) << "," <<
        ((row.effect_chance == INT32_MAX) ? "" : std::to_string(row.effect_chance)) << "," <<
        ((row.contest_type_id == INT32_MAX) ? "" : std::to_string(row.contest_type_id)) << "," <<
        ((row.contest_effect_id == INT32_MAX) ? "" : std::to_string(row.contest_effect_id)) << "," <<
        ((row.super_contest_effect_i == INT32_MAX) ? "" : std::to_string(row.super_contest_effect_i)) << endl;
    }

}
