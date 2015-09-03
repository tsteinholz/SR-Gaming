// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#ifndef MASTERMINE_MASTERMINE_H
#define MASTERMINE_MASTERMINE_H
#define OVERRIDE_SMART 0
#define OVERRIDE_EASY 0
#define OVERRIDE_PLAYER_FIRST 0
#define DEBUG 1

#include <ctime>
#include <stdlib.h>

#include "Game.h"
#include "Utils.h"

using namespace SRHSCode;

class MasterMine : public Game
{
public:
    MasterMine();
    virtual ~MasterMine();

    virtual void Initialize() override;

    virtual void Execute() override;

    virtual void Shutdown() override;

    enum Mode
    {
        EASY,
        SMART,
    };

private:

    bool HumanFirst;
    Mode Difficulty = EASY;
    int Pile;

    bool HumanTurn();

    bool AiTurn();
};


#endif //MASTERMINE_MASTERMINE_H
