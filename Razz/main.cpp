#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void GetLine(int line, const char* file, int arr[])
{
    ifstream game (file);
    if (game.is_open())
    {
        char data[7];
        for (unsigned int i = 0; i < line; i++)
        {
            game.get(data, 7);
        }
        game.close();
        for (unsigned int i = 0; i < 7; i++) arr[i] = (int)data[i];
    }
}

bool HasMoreLines(int line, const char* file)
{
    return true;
}

int main()
{
    const char* game = "Game.pkr";
    unsigned int i = 0;
    //while (HasMoreLines(i, game))
    //{
        int hand[7];
        GetLine(i, game, hand);
        cout << hand[0];
        for (auto& x : hand)
        {
            cout << x;
        }

        //i++;
    //}
    return 0;
}