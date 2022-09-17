// author = ranais

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

void init(char pile[23][23])
{
    int i = 0, j = 0;

    for(i=0; i<23; i++)
    {
        for(j=0; j<23; j++)
        {
            pile[i][j] = 0;
        }
    }
}

void increment(char pile[23][23], int x, int y)
{
    if(pile[y][x] >= 0)
    {
        if(pile[y][x]<8)
        {
            pile[y][x] = pile[y][x] + 1;
        }
        else
        {
            pile[y][x] = 1;

            if(y != 0 && x != 0)
                increment(pile, x-1, y-1);
            if(y != 0)
                increment(pile, x, y-1);
            if(y != 0 && x != 22)
                increment(pile, x+1, y-1);

            if(x != 0)
                increment(pile, x-1, y);
            if(x != 22)
                increment(pile, x+1, y);

            if(y != 22 && x != 22)
                increment(pile, x+1, y+1);
            if(y != 22)
                increment(pile, x, y+1);
            if(y != 22 && x != 0)
                increment(pile, x-1, y+1);
        }
    }
}


void printPile(char pile[23][23])
{
    int i = 0, j = 0;

    for(i=0; i<23; i++)
    {
        for(j=0; j<23; j++)
        {
            if(pile[i][j] < 0)
                printf("%3c", '#');
            else
                printf("%3d", pile[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void setPile(char pile[23][23], int x, int y, int h)
{
    pile[y][x] = h;
}


int main(int argc, char* argv[])
{
    int i = 1;
    char pile[23][23];
    int fps = 1000;

    if(argc > 1 && !strcmp(argv[i],"--fps"))    
    {
        fps = atoi(argv[2]);
        i = 3;
    }

    init(pile);

    while(i<argc)
    {
        int y = atoi(argv[i]);
        int x = atoi(argv[i+1]);
        int h = atoi(argv[i+2]);

        i = i + 3;
        setPile(pile, x, y, h); 
    }

    printPile(pile);

    while(1)
    {
        increment(pile, 11, 11);
        printPile(pile);
        usleep(1000000/fps);
    }
    
    return 0;
}
