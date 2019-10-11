#include <iostream>
#include <fstream>
using namespace std;

int checkblocks(char input[])
{
    if (input[0] == 'T')
        return 0 + (input[1] - '1');
    else if (input[0] == 'L')
        return 4 + (input[1] - '1');
    else if (input[0] == 'J')
        return 8 + (input[1] - '1');
    else if (input[0] == 'S')
        return 12 + (input[1] - '1');
    else if (input[0] == 'Z')
        return 14 + (input[1] - '1');
    else if (input[0] == 'I')
        return 16 + (input[1] - '1');
    else if (input[0] == 'O')
        return 18 + (input[1] - '1');
    return -1;
}

bool check()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].y >= M + 4)
            return 0;
        else if (field[a[i].x][a[i].y])
            return 0;
    }
    return 1;
}

void set_init_position(int startpoint)
{
    for (int i = 0; i < 4; i++)
    {
        a[i].x = startpoint + a[i].x - 1;
        if (a[i].x < 0 || a[i].x >= N)
            gameover = 1;
    }
}