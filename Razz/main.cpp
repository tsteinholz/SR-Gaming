#include <iostream>
#include <fstream>
//#include <string>
#include <sstream>

using namespace std;

void Load(const string file, int data[10][7])
{
    fstream game(file);
    if (game.good())
    {
        cout << "Loading File...";
        unsigned int x = 0, i = 0, j = 0;
        while (game >> x) {
            data[j][i] = x;
            i = i > 6 ? i + 1 : 0;
            j = i == 0 ? j + 1 : j;
        }
        getchar();
    }
    else
    {
        cout << "Not loading " << file << "..." << endl;
    }
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 7; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void PlayGame(int x)
{
    ostringstream oss;
    oss << "Game" << x << ".pkr";
    int data[10][7] = {0};
    Load(oss.str(), data);
    oss.clear();
}

int main()
{
    PlayGame(1);
    PlayGame(2);
    PlayGame(3);
    PlayGame(4);
    return 0;
}