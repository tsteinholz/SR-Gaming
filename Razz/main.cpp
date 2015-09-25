#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Load(const string file, int data[10][7])
{
    fstream game(file, ios_base::in);
    if (game.good())
    {
        cout << "Loading " << file << "..." << endl;
        unsigned int x = 0, i = 0, j = 0;
        while (game >> x)
        {
            data[i][j] = x;
            i = i > 6 ? i + 1 : 0;
            j = i == 0 ? j + 1 : j;
        }
    }
    else
    {
        cout << "Not loading " << file << "..." << endl;
    }
}

void Calculate(int data[10][7])
{
    bool used = false;
    int total = 0;
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 7; j++)
        {
            if (data[i][j] != 0)
            {
                if (data[i][j] < 10) cout << "0";
                cout << data[i][j] << " ";
                used = true;
                total += data[i][j];
            }
        }
        if (used)
        {
            cout << " | ";
            if (total - 28 == 0) cout << "Bet";
            else cout << "Fold";
            cout << " " << total << endl;
            total = 0;
        }
        used = false;
    }
}

void PlayGame(int x)
{
    ostringstream oss;
    oss << "Game" << x << ".pkr";
    int data[10][7] = {0};
    Load(oss.str(), data);
    Calculate(data);
    oss.clear();
}

int main(int argc, char* argv[])
{
    PlayGame(1);
    PlayGame(2);
    PlayGame(3);
    PlayGame(4);
    return 0;
}