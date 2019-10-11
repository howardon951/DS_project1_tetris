#include <iostream>
#include <fstream>
using namespace std;

int M, N;
int checkblocks(char input[]);
void buildmap(int rows, int cols);
void set_init_position(int startpoint);
bool check(int **map);
struct Point
{
    int x, y;
} a[4], b[4];
bool gameover = 0;
static int count = 1;

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

    ifstream infile;
    infile.open("input.txt");
    //rear the rows and cols and set the game matrix
    infile >> M >> N;
    //something's wrong here: int  field[M][N] = {0};
    //dynamically set my 2-d map
    int **field;
    field = new int *[M + 4];
    for (int i = 0; i < M + 4; i++)
        field[i] = new int[N];
    cout << "initial map" << endl;
    for (int i = 0; i < M + 4; i++)
    {
        for (int j = 0; j < N; j++)
        {
            field[i][j] = 0;
            cout << field[i][j];
        }
        cout << endl;
    };

    //while read block success, game continue
    while (infile >> data && !gameover) // what's wrong?!(&& data != "End")
    {
        //rear the start position of the current block
        int startpos;
        infile >> startpos;
        //check which type of block it is
        int n = checkblocks(data);
        if (n == -1)
        {
            cout << "wrong block/End" << endl;
            break;
        }

        else
            cout << "suc" << n << endl;

        //set block component to a[]
        for (int i = 0; i < 4; i++)
        {
            a[i].x = figure[n][i] % 3;
            a[i].y = figure[n][i] / 3;
        }
        if (n == 17) //special case
        {
            a[3].x = 3;
            a[3].y = 3;
        }
        for (int i = 0; i < 4; i++)
        {
            cout << a[i].x << " " << a[i].y << endl;
        }
        set_init_position(startpos);
        for (int i = 0; i < 4; i++)
        {
            cout << a[i].x << " " << a[i].y << endl;
        }
        //place the block at right position in map
        while (check(field))
        {
            for (int i = 0; i < 4; i++)
            {
                b[i].x = a[i].x;
                b[i].y = a[i].y;
                a[i].y += 1;
                cout << a[i].x << a[i].y << endl;
            }
        }
        for (int i = 0; i < 4; i++)
            field[b[i].y][b[i].x] = 1;
        for (int i = 0; i < M + 4; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << field[i][j];
            }
            cout << endl;
        }
    }
    infile.close();

    // write the result to output.txt
    /*ofstream outfile;
    outfile.open("output.txt");
    //cout << "Writing to the file" << endl;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            outfile << field[i][j] << endl;
    outfile.close();

    //read out file on terminal
    infile.open("output.txt");*/
    cout << "Reading from the file" << endl;

    for (int i = 0; i < M + 4; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << field[i][j];
        }
        cout << endl;
    }
    //infile.close();
    cout << count;
    return 0;
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
        return 18;
    return -1;
}

bool check(int **map)
{
    cout << "#" << count << endl;
    count++;
    for (int i = 0; i < 4; i++)
    {
        if (a[i].y >= M + 4)
        {
            cout << "out of the map" << endl;
            return 0;
        }

        else if (map[a[i].y][a[i].x])
        {
            cout << "onto previous brick" << endl;
            return 0;
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