/**
 * @file map.h
 * @author Ranai Srivastav - ranais@iastate.edu
 * @brief The file that contains the structure definitions for the map struct
 * @version 1.2
 * @date 2022-09-10
 * 
 */
typedef struct map_struct
{
    int map[21][80];
    int n_x;
    int s_x;
    int e_y;
    int w_y;

} map_t;