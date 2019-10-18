#include <iostream>
#include <fstream>
using namespace std;

int M, N;
int checkblocks(char input[]);
void moveline(int line, int **map);
void set_init_position(int startpoint);
bool check(int **map);
void check_line(int **map, int line);
struct Point
{
    int x, y;
} a[4], b[4];
bool gameover = 0;

int figure[19][4] =
    {
        6, 7, 8, 10,   //T1
        4, 6, 7, 10,   //T2
        7, 9, 10, 11,  //T3
        3, 6, 7, 9,    //T3
        3, 6, 9, 10,   //L1
        6, 7, 8, 9,    //L2
        3, 4, 7, 10,   //L3
        8, 9, 10, 11,  //L4
        4, 7, 9, 10,   //J1
        6, 9, 10, 11,  //J2
        3, 4, 6, 9,    //J3
        6, 7, 8, 11,   //J4
        7, 8, 9, 10,   //S1
        3, 6, 7, 10,   //S2
        6, 7, 10, 11,  //Z1
        4, 7, 6, 9,    //Z2
        0, 3, 6, 9,    //I1
        9, 10, 11, 12, //I2
        6, 7, 9, 10    //O
};
/*********************main start*******************************/
int main()
{
    char data[3];
    /*read the rows and cols and set the game matrix*/
    ifstream infile;
    infile.open("tetris.data");
    infile >> M >> N;

    /*dynamically set my 2-d map*/
    int **field; /* something's wrong with this initialization : int  field[M][N] = {0}; */
    field = new int *[M + 4];
    for (int i = 0; i < M + 4; i++)
        field[i] = new int[N];
    for (int i = 0; i < M + 4; i++)
    {
        for (int j = 0; j < N; j++)
        {
            field[i][j] = 0;
        }
    };

    /*while read block success, game continue*/
    while (infile >> data && !gameover) /* what's wrong with : (&& data != "End") ???*/
    {
        int startpos;
        infile >> startpos;        //read the start position of the current block
        int n = checkblocks(data); //check what type of block it is
        if (n == -1)               //if "End", end the game
        {
            break;
        }
        /*setting the block's 4 bricks into a[]*/
        for (int i = 0; i < 4; i++)
        {
            a[i].x = figure[n][i] % 3;
            a[i].y = figure[n][i] / 3;
        }
        if (n == 17) //special case of I2
        {
            a[3].x = 3;
            a[3].y = 3;
        }
        /*place the block at the right position in map*/
        set_init_position(startpos);
        while (check(field))
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
                //cout << a[i].x << a[i].y << endl;
            }
        }
        for (int i = 0; i < 4; i++)
            field[b[i].y][b[i].x] = 1;
        /*check whether the fallen bricks makes a vertical line in map, if so, move each upper line down*/
        for (int i = 0; i < 4; i++)
            check_line(field, b[i].y); //base on descending bricks
        /*if the bricks is on the illegal region, gameover=1 */
        for (int j = 0; j < N; j++)
            if (field[3][j])
                gameover = 1;
    }
    infile.close();

    /*  write the result to output.final */
    ofstream outfile;
    outfile.open("tetris.final");
    for (int i = 4; i < M + 4; i++)
    {
        for (int j = 0; j < N; j++)
        {
            outfile << field[i][j];
        }
        outfile << endl;
    }
    outfile.close();
    return 0;
}
/********************main end ********************************/
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
        return 18;
    return -1;
}

bool check(int **map)
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].y >= M + 4)
        {
            return 0; //cout << "on the bottom of the map" << endl;
        }
        else if (map[a[i].y][a[i].x])
        {
            return 0; //cout << "onto previous brick" << endl;
        }
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

void check_line(int **map, int line)
{
    int count = 0;
    for (int j = 0; j < N; j++)
    {
        if (map[line][j])
            count++;
    }
    if (count == N)
        moveline(line, map);
}

void moveline(int line, int **map)
{
    for (int i = line; i > 0; i--)
    {
        for (int j = 0; j < N; j++)
        {
            map[i][j] = map[i - 1][j];
        }
    }
}