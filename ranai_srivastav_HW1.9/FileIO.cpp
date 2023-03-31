//
// Created by ranai on 10/31/22.
//

#include <string>
#include<cstring>
#include <istream>
#include <fstream>

using namespace std;


string home_path = getenv("HOME");
string base_paths[3] = {"/share/cs327/", home_path + "/" + ".poke327/", home_path + "/" + "Ranai/Fall22/COMS327/database_pokedex/"};
const string file_path("pokedex/pokedex/data/csv/");

string get_database_path(string type)
{
    int i = 0;
    string file_name = file_path + type + ".csv";


    for(i = 0; i < base_paths->length(); i++)
    {
        string total_path(base_paths[i] + file_name);
        ifstream csv_file(total_path);
        if(csv_file.good())
        {
            return base_paths[i] + file_name;
        }
    }

    return "";
}