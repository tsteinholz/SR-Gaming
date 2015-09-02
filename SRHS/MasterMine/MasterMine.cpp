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

#ifdef OVERRIDE_SMART
    Difficulty = SMART;
#endif
#ifdef OVERRIDE_EASY
    Difficulty = EASY;
#endif
}

void MasterMine::Execute()
{
    switch (Difficulty)
    {
        default:
        case SMART:

            break;
        case EASY:
            rand() % (Pile/2) + 1;
            break;
    }
}

void MasterMine::Shutdown()
{

}
