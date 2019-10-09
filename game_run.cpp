#include <iostream>
#include <fstream>
using namespace std;

int **field;
int M, N;
int checkblocks(char input[]);
void buildmap(int rows, int cols);
bool check();
struct Point
{
    int x, y;
} a[4], b[4];

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
int main()
{
    char data[3];
    bool gameover = 0;

    ifstream infile;
    infile.open("input.txt");
    //rear the rows and cols and set the game matrix
    infile >> M >> N;
    field[M][N] = {0};
    cout << M << N;

    //while read block success, game continue
    while (infile >> data && data != "End" && !gameover)
    {
        //rear the start position of the current block
        int startpos;
        infile >> startpos;
        //check which type of block it is
        int n = checkblocks(data);
        if (n == -1)
            cout << "wrong block";

        //set block component to a[]
        for (int i = 0; i < 4; i++)
        {
            a[i].x = figure[n][i] % 3;
            a[i].y = figure[n][i] / 3;
        }
        if (n == 18) //special case
        {
            a[3].x = 3;
            a[3].y = 3;
        }
    }
    infile.close();

    // write the result to output.txt
    ofstream outfile;
    outfile.open("output.txt");
    //cout << "Writing to the file" << endl;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            outfile << "#" << i << field[i][j] << endl;
    outfile.close();

    //read out file on terminal
    infile.open("output.txt");
    cout << "Reading from the file" << endl;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << field[i][j];
        }
        cout << endl;
    }
    infile.close();
    return 0;
}

void buildmap(int rows, int cols)
{
}

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
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return 0;
        else if (field[a[i].y][a[i].x])
            return 0;
    }
    return 1;
}