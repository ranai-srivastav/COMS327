//
// Created by ranai on 11/2/22.
//

#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class IO_pokemon_species
{
public:
    typedef struct IO_pokemon_species_s
    {
        int id;
        string identifier;
        int generation_id;
        int evolves_from_species_id;
        int evolution_chain_id;
        int color_id;
        int shape_id;
        int habitat_id;
        int gender_rate;
        int capture_rate;
        int base_happiness;
        int is_baby;
        int hatch_counter;
        int has_gender_differences;
        int growth_rate_id;
        int forms_switchable;
        int is_legendary;
        int is_mythical;
        int order;
        int conquest_order;
    } IO_pokemon_species_struct;

    vector<IO_pokemon_species_struct*> pokemon_csv_species_data;

    IO_pokemon_species(std::string path)
    {
        ifstream file;
        file.open(path);

        string line, word, temp;
        while(file>>temp)
        {
            getline(file, line);
            stringstream line_stream(temp);

            int i = 0;
            IO_pokemon_species_struct *this_line = new IO_pokemon_species_struct ;
            while(getline(line_stream, word, ','))
            {
                if(word == "id")
                    break;
                switch(i)
                {
                    case 0:  this_line->id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 1:  this_line->identifier = word.empty() ? "" : word; break;
                    case 2:  this_line->generation_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 3:  this_line->evolves_from_species_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 4:  this_line->evolution_chain_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 5:  this_line->color_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 6:  this_line->shape_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 7:  this_line->habitat_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 8:  this_line->gender_rate = word.empty() ? INT32_MAX : stoi(word); break;
                    case 9:  this_line->capture_rate = word.empty() ? INT32_MAX : stoi(word); break;
                    case 10: this_line->base_happiness = word.empty() ? INT32_MAX : stoi(word); break;
                    case 11: this_line->is_baby = word.empty() ? INT32_MAX : stoi(word); break;
                    case 12: this_line->hatch_counter = word.empty() ? INT32_MAX : stoi(word); break;
                    case 13: this_line->has_gender_differences = word.empty() ? INT32_MAX : stoi(word); break;
                    case 14: this_line->growth_rate_id = word.empty() ? INT32_MAX : stoi(word); break;
                    case 15: this_line->forms_switchable = word.empty() ? INT32_MAX : stoi(word); break;
                    case 16: this_line->is_legendary = word.empty() ? INT32_MAX : stoi(word); break;
                    case 17: this_line->is_mythical = word.empty() ? INT32_MAX : stoi(word); break;
                    case 18: this_line->order = word.empty() ? INT32_MAX : stoi(word); break;
                    case 19: this_line->conquest_order = word.empty() ? INT32_MAX : stoi(word); break;
                }
                i++;
            }
            pokemon_csv_species_data.push_back(this_line);
        }
    }

    void print()
    {
        unsigned int len = pokemon_csv_species_data.size();
        unsigned int i = 0;

        for(i = 1; i<len; i++)
        {
            IO_pokemon_species_struct row = *pokemon_csv_species_data[i];

            std::cout<<
            ((row.id == INT32_MAX) ? "" : std::to_string(row.id)) << "," <<
            row.identifier << "," <<
            ((row.generation_id == INT32_MAX) ? "" : std::to_string(row.generation_id)) << "," <<
            ((row.evolves_from_species_id == INT32_MAX) ? "" : std::to_string(row.evolves_from_species_id)) << "," <<
            ((row.evolution_chain_id == INT32_MAX) ? "" : std::to_string(row.evolution_chain_id)) << "," <<
            ((row.color_id == INT32_MAX) ? "" : std::to_string(row.color_id)) << "," <<
            ((row.shape_id == INT32_MAX) ? "" : std::to_string(row.shape_id)) << "," <<
            ((row.habitat_id == INT32_MAX) ? "" : std::to_string(row.habitat_id)) << "," <<
            ((row.gender_rate == INT32_MAX) ? "" : std::to_string(row.gender_rate)) << "," <<
            ((row.capture_rate == INT32_MAX) ? "" : std::to_string(row.capture_rate)) << "," <<
            ((row.base_happiness == INT32_MAX) ? "" : std::to_string(row.base_happiness)) << "," <<
            ((row.is_baby == INT32_MAX) ? "" : std::to_string(row.is_baby)) << "," <<
            ((row.hatch_counter == INT32_MAX) ? "" : std::to_string(row.hatch_counter)) << "," <<
            ((row.has_gender_differences == INT32_MAX) ? "" : std::to_string(row.has_gender_differences)) << "," <<
            ((row.growth_rate_id == INT32_MAX) ? "" : std::to_string(row.growth_rate_id)) << "," <<
            ((row.forms_switchable == INT32_MAX) ? "" : std::to_string(row.forms_switchable)) << "," <<
            ((row.is_legendary == INT32_MAX) ? "" : std::to_string(row.is_legendary)) << "," <<
            ((row.is_mythical == INT32_MAX) ? "" : std::to_string(row.is_mythical)) << "," <<
            ((row.order == INT32_MAX) ? "" : std::to_string(row.order)) << "," <<
            ((row.conquest_order == INT32_MAX) ? "" : std::to_string(row.conquest_order)) << endl;
        }
    }
};

class IO_experience
{
public:
    typedef struct experience_s
    {
        int growth_rate_id;
        int level;
        int experience;
    } IO_experience_struct;

    vector<IO_experience_struct*> experience_csv_data;

    IO_experience(string path)
    {
        ifstream file;
        file.open(path);

        string line, word, temp;
        while(file>>temp)
        {
            getline(file, line);
            stringstream line_stream(temp);

            int i = 0;
            IO_experience_struct *this_line = new IO_experience_struct;
            while(getline(line_stream, word, ','))
            {
                if(word == "growth_rate_id")
                    break;
                switch(i)
                {
                    case 0:
                        this_line->growth_rate_id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 1:
                        this_line->level = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 2:
                        this_line->experience = word.empty() ? INT32_MAX : stoi(word);
                        break;
                }
                i++;
            }
            experience_csv_data.push_back(this_line);
        }
    }

    void print()
    {
        unsigned int len = experience_csv_data.size();
        unsigned int i = 0;

        for(i = 1; i<len; i++)
        {
            IO_experience_struct row = *experience_csv_data[i];

            std::cout<<
            ((row.growth_rate_id == INT32_MAX) ? "" : std::to_string(row.growth_rate_id)) << "," <<
            ((row.level == INT32_MAX) ? "" : std::to_string(row.level)) << "," <<
            ((row.experience == INT32_MAX) ? "" : std::to_string(row.experience)) << endl;
        }
    }
};

class IO_type_names
{
public:
    typedef struct type_names_s
    {
        int type_id;
        int local_language_id;
        string name;

    } IO_type_names_struct;

    vector<IO_type_names_struct*> type_names_csv_data;

    explicit IO_type_names(string path)
    {
        ifstream file;
        file.open(path);

        string line, word, temp;
        while(file>>temp)
        {
            getline(file, line);
            stringstream line_stream(temp);

            int i = 0;
            IO_type_names_struct *this_line = new IO_type_names_struct;
            while(getline(line_stream, word, ','))
            {
                if(word == "type_id")
                    break;
                switch(i)
                {
                    case 0:
                        this_line->type_id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 1:
                        this_line->local_language_id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 2:
                        this_line->name = word;
                        break;
                }
                i++;
            }
            type_names_csv_data.push_back(this_line);
        }
    }

    void print()
    {
        unsigned int len = type_names_csv_data.size();
        unsigned int i = 0;

        for(i = 1; i<len; i++)
        {
            IO_type_names_struct row = *type_names_csv_data[i];

            cout<<
            ((row.type_id == INT32_MAX) ? "" : std::to_string(row.type_id)) << "," <<
            ((row.local_language_id == INT32_MAX) ? "" : std::to_string(row.local_language_id)) << "," <<
            row.name << endl;
        }
    }
};


class IO_pokemon_stats
{
public:
    typedef struct pokemon_stats_s
    {
        int pokemon_id;
        int stat_id;
        int base_stat;
        int effort;
    } IO_pokemon_stats_struct;

    vector<IO_pokemon_stats_struct*> pokemon_stats_csv_data;

    explicit IO_pokemon_stats(string path)
    {
        ifstream file;
        file.open(path);

        string line, word, temp;
        while(file>>temp)
        {
            getline(file, line);
            stringstream line_stream(temp);

            int i = 0;
            IO_pokemon_stats_struct *this_line = new IO_pokemon_stats_struct;
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
                        this_line->stat_id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 2:
                        this_line->base_stat = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 3:
                        this_line->effort = word.empty() ? INT32_MAX : stoi(word);
                        break;
                }
                i++;
            }
            pokemon_stats_csv_data.push_back(this_line);
        }
    }

    void print()
    {
        unsigned int len = pokemon_stats_csv_data.size();
        unsigned int i = 0;

        for(i = 1; i<len; i++)
        {
            IO_pokemon_stats_struct row = *pokemon_stats_csv_data[i];

            cout <<
            ((row.pokemon_id == INT32_MAX) ? "" : std::to_string(row.pokemon_id)) << "," <<
            ((row.stat_id == INT32_MAX) ? "" : std::to_string(row.stat_id)) << "," <<
            ((row.base_stat == INT32_MAX) ? "" : std::to_string(row.base_stat)) << "," <<
            ((row.effort == INT32_MAX) ? "" : std::to_string(row.effort)) << endl;
        }
    }
};

class IO_stats
{
public:
    typedef struct stats_s
    {
        int id;
        int damage_class_id;
        string identifier;
        int is_battle_only;
        int game_index;

    } IO_stats_struct;

    vector<IO_stats_struct*> stats_csv_data;

    explicit IO_stats(string path)
    {
        ifstream file;
        file.open(path);

        string line, word, temp;
        while(file>>temp)
        {
            getline(file, line);
            stringstream line_stream(temp);

            int i = 0;
            IO_stats_struct *this_line = new IO_stats_struct;
            while(getline(line_stream, word, ','))
            {
                if(word == "id")
                    break;
                switch(i)
                {
                    case 0:
                        this_line->id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 1:
                        this_line->damage_class_id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 2:
                        this_line->identifier = word;
                        break;
                    case 3:
                        this_line->is_battle_only = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 4:
                        this_line->game_index = word.empty() ? INT32_MAX : stoi(word);
                        break;
                }
                i++;
            }
            stats_csv_data.push_back(this_line);
        }
    }

    void print()
    {
        unsigned int len = stats_csv_data.size();
        unsigned int i = 0;

        for(i = 1; i<len; i++)
        {
            IO_stats_struct row = *stats_csv_data[i];

            std::cout<<
            ((row.id == INT32_MAX) ? "" : std::to_string(row.id)) << "," <<
            ((row.damage_class_id == INT32_MAX) ? "" : std::to_string(row.damage_class_id)) << "," <<
            row.identifier << "," <<
            ((row.is_battle_only == INT32_MAX) ? "" : std::to_string(row.is_battle_only)) << "," <<
            ((row.game_index == INT32_MAX) ? "" : std::to_string(row.game_index)) << endl;
        }
    }
};


class IO_pokemon_types
{
public:
    typedef struct pokemon_types_s
    {
        int pokemon_id;
        int type_id;
        int slot;


    } IO_pokemon_types_struct;

    vector<IO_pokemon_types_struct*> pokemon_types_csv_data;

    explicit IO_pokemon_types(string path)
    {
        ifstream file;
        file.open(path);

        string line, word, temp;
        while(file>>temp)
        {
            getline(file, line);
            stringstream line_stream(temp);

            int i = 0;
            IO_pokemon_types_struct *this_line = new IO_pokemon_types_struct;
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
                        this_line->type_id = word.empty() ? INT32_MAX : stoi(word);
                        break;
                    case 2:
                        this_line->slot = word.empty() ? INT32_MAX : stoi(word);
                        break;
                }
                i++;
            }
            pokemon_types_csv_data.push_back(this_line);
        }
    }

    void print()
    {
        unsigned int len = pokemon_types_csv_data.size();
        unsigned int i = 0;

        for(i = 1; i<len; i++)
        {
            IO_pokemon_types_struct row = *pokemon_types_csv_data[i];

            cout <<
            ((row.pokemon_id == INT32_MAX) ? "" : std::to_string(row.pokemon_id)) << "," <<
            ((row.type_id == INT32_MAX) ? "" : std::to_string(row.type_id)) << "," <<
            ((row.slot == INT32_MAX) ? "" : std::to_string(row.slot)) << endl;
        }
    }
};