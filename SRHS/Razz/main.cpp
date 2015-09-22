#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int* GetLine(int line, const char* file, int arr[])
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
        int out[] = {(int)data[0],(int)data[0],(int)data[0],(int)data[0],(int)data[0],(int)data[0],(int)data[0]};
        return out;
    }
    return nullptr;
}

bool HasMoreLines(int line, const char* file)
{

}

int main()
{
    const char* game = "Game.pkr";
    unsigned int i = 0;
    while (HasMoreLines(i, game))
    {
        int hand[7];
        GetLine(i, game, hand);
        for (auto& x : hand)
        {

        }

        i++;
    }
    return 0;
}