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
    bool playing = true;
    while (playing)
    {
#if DEBUG
        std::cout << "DEBUG: Pile = " << Pile << std::endl;
        std::cout << "DEBUG: Difficulty = " << Difficulty << std::endl;
        std::cout << "DEBUG: Human First = " << HumanFirst << std::endl;
#endif
        playing = HumanFirst ? HumanTurn() : AiTurn();
        if (playing) playing = HumanFirst ? AiTurn() : HumanTurn();
    }
    Shutdown();
}

void MasterMine::Shutdown()
{

}

bool MasterMine::AiTurn()
{
    std::cout << "AI's Turn!" << std::endl;
    int turns = 0;
    switch (Difficulty)
    {
        default:
        case SMART:
            // TODO : Fix "Smart" difficulty
            while ((Pile % 2 != 0) && (Pile > 1) && (turns <= (Pile/2)))
            { Pile--; turns++; }
            //Pile--;
            break;
        case EASY:
            if(Pile == 1)
            {
                std::cout << "-------------" << std::endl;
                std::cout << "You just WON!" << std::endl;
                std::cout << "-------------" << std::endl;
                return false;
            }
            else Pile -= rand() % (Pile/2) + 1;
            break;
    }
    std::cout << "Done AI's Turn!" << std::endl;
    return true;
}

bool MasterMine::HumanTurn()
{
    int turn;
    std::cout << "Your Turn!" << std::endl << "How many marbles do you want to take out?" << std::endl;
    std::cin >> turn;
    if ((turn < 1) || ((turn > (Pile / 2)) && turn != 1))
    {
        std::cout << std::endl << "--------------------------------" << std::endl;
        std::cout << "This Move is Invalid! Try again!" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        return HumanTurn();
    }
    Pile -= turn;
    if(Pile < 1)
    {
        std::cout << "-----------------------" << std::endl;
        std::cout << "You just LOST! AI WINS!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        return false;
    }
    else return true;

}
