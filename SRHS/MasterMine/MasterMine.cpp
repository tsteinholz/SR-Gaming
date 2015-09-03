// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include "MasterMine.h"

MasterMine::MasterMine()
{ Initialize(); }

MasterMine::~MasterMine()
{ Shutdown(); }

void MasterMine::Initialize()
{
    srand(time(NULL));
    HumanFirst = (bool) (rand() % 2);
    Pile = rand() % 91 + 10;

    switch(rand() % 2)
    {
        default:
        case 0:
            Difficulty = SMART;
            break;
        case 1:
            Difficulty = EASY;
            break;
    }

#if OVERRIDE_SMART
    Difficulty = SMART;
#endif
#if OVERRIDE_EASY
    Difficulty = EASY;
#endif
#if OVERRIDE_PLAYER_FIRST
    HumanFirst = true;
#endif
}

void MasterMine::Execute()
{
#if DEBUG
    std::cout << "DEBUG: Difficulty = " << Difficulty << std::endl;
    std::cout << "DEBUG: Pile = " << Pile << std::endl;
    std::cout << "DEBUG: Human First = " << HumanFirst << std::endl;
#endif
    bool playing = true;
    while (playing)
    {
        playing = HumanFirst ? HumanTurn() : AiTurn();
        playing = HumanFirst ? AiTurn() : HumanTurn();
    }
    Shutdown();
}

void MasterMine::Shutdown()
{

}

bool MasterMine::AiTurn()
{
    int turn = 0;
    switch (Difficulty)
    {
        default:
        case SMART:
            turn = rand() % (Pile/2) + 1;
            while (turn % 2 != 0)
            {

            }
            break;
        case EASY:
            turn = rand() % (Pile/2) + 1;
            break;
    }
    return false;
}

bool MasterMine::HumanTurn()
{
    int turn;
    std::cout << "Your Turn!" << std::endl << "How many marbles do you want to take out?" << std::endl;
    std::cin >> turn;
    if ((turn < 2) || (turn > (Pile / 2)))
    {
        std::cout << "This Move is Invalid! Try again!" << std::endl;
        // something, i guess
        //return HumanTurn();
    }
    if((Pile -= turn) <= 0)
    {
        std::cout << "You just loss!" << std::endl;
        return true;
    }
    else return false;

}
