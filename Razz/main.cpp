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

/*
 * Output :
 *
 * Loading Game1.pkr...
 * 1  2  3  4  5  6  7  | Bet
 * 1  2  3  4  6  7  8  | Fold
 * 1  2  3  3  4  4  4  | Fold
 * 11  1  5  4 12  2  3 | Bet
 * 5  1  3  2  6  7  9  | Fold
 * Loading Game2.pkr...
 * 12 12 12 12 11 11 11 | Fold
 * 13 13 13 13  1  1  1 | Fold
 * 1  1  1  1  2  2  2  | Fold
 * 5  5  5  5  3  3  3  | Fold
 * Loading Game3.pkr...
 * 1  2  1  2  3  4  5  | Bet
 * 2  2  1  2  3  4  5  | Bet
 * 3  2  1  2  3  4  5  | Bet
 * 13 13  1  2  3  4  5 | Bet
 * 12 12  1  2  3  4  5 | Bet
 * Loading Game4.pkr...
 * 5  4  3  2  1  6  7  | Bet
 * 5  4  3  2  1 13 12  | Bet
 * 5  4  3  2  1  8  8  | Bet
 * 8  5  4  3  2  1  8  | Bet
 * 5  8  4  3  2  8  1  | Bet
 * 8  2  5  4  3 10  1  | Bet
 *
 * Process finished with exit code 0
 */