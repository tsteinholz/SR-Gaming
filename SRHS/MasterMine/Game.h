// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#ifndef MASTERMINE_GAME_H
#define MASTERMINE_GAME_H

namespace SRHSCode
{
    class Game
    {
    public:
        Game() {}
        virtual ~Game() {}

        virtual void Initialize() = 0;

        virtual void Execute() = 0;

        virtual void Shutdown() = 0;
    };
}

#endif //MASTERMINE_GAME_H
