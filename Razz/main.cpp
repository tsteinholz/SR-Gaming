#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Load(const string& file, unsigned int data[10][7])
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

void Calculate(unsigned int data[10][7])
{
    bool valid = false;
    for (unsigned int i = 0; i < 10; i++)
    {
        bool test[5] = {false};
        for (unsigned int j = 0; j < 7; j++)
        {
            if (data[i][j] != 0)
            {
                valid = true;
                if (data[i][j] < 10) cout << " ";
                cout << data[i][j] << " ";
                switch (data[i][j])
                {
                    case 1: test[0] = true; break;
                    case 2: test[1] = true; break;
                    case 3: test[2] = true; break;
                    case 4: test[3] = true; break;
                    case 5: test[4] = true; break;
                    default: break;
                }
            }
        }
        if (valid)
        {
            cout << " | ";
            if (test[0] && test[1] && test[2] && test[3] && test[4]) cout << "Bet";
            else cout << "Fold";
            cout << endl;
        }
        valid = false;
    }
}

void PlayGame(int x)
{
    ostringstream oss;
    oss << "Game" << x << ".pkr";
    unsigned int data[10][7] = {0};
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