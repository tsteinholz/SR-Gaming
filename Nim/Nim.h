// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#ifndef Nim_Nim_H
#define Nim_Nim_H

#define OVERRIDE_SMART 0
#define OVERRIDE_EASY 0
#define OVERRIDE_PLAYER_FIRST 0
#define DEBUG 0

#include <ctime>
#include <stdlib.h>

#include "Game.h"
#include "Utils.h"

using namespace SRHSCode;

class Nim : public Game
{
public:
    Nim();
    virtual ~Nim();

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


#endif //Nim_Nim_H
