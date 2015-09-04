// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <iostream>
#include <string>

struct Code
{
    enum Peg
    {
        RED,
        BLUE,
        YELLOW,
        GREEN,
        WHITE,
        ORANGE,
        NOTHING,
    };

    Code()
    {
        srand(time(NULL));
        Peg temp[4];
        for(int i = 0; i < 4; i++)
        {
            switch(rand() % 6)
            {
                default:
                    temp[i] = NOTHING;
                case 0:
                    temp[i] = RED;
                    break;
                case 1:
                    temp[i] = BLUE;
                    break;
                case 2:
                    temp[i] = YELLOW;
                    break;
                case 3:
                    temp[i] = GREEN;
                    break;
                case 4:
                    temp[i] = WHITE;
                    break;
                case 5:
                    temp[i] = ORANGE;
                    break;
            }
        }
        A = temp[0];
        B = temp[1];
        C = temp[2];
        D = temp[4];
    }

    Code(Peg x)
        : A(x), B(x), C(x), D(x) {}

    Code(Peg a, Peg b, Peg c, Peg d)
        : A(a), B(b), C(c), D(d) {}

    Code(const Code& copy)
        : A(copy.A), B(copy.B), C(copy.C), D(copy.D) {}

    Peg A, B, C, D;

    //TODO
    void PrintState()
    {
        std::cout << std::endl;
    }

    bool Verify()
    {
        return A != NOTHING &&
               B != NOTHING &&
               C != NOTHING &&
               D != NOTHING;
    }

    static Peg ToPeg(const char x)
    {
        switch (x)
        {
            case 'r':
            case 'R':
                return RED;
            case 'b':
            case 'B':
                return BLUE;
            case 'y':
            case 'Y':
                return YELLOW;
            case 'g':
            case 'G':
                return GREEN;
            case 'w':
            case 'W':
                return WHITE;
            case 'o':
            case 'O':
                return ORANGE;
            default:
                return NOTHING;
        }
    }

    static std::string ToString(const Peg x)
    {
        switch(x)
        {
            case RED:
                return "Red";
            case BLUE:
                return "Blue";
            case YELLOW:
                return "Yellow";
            case GREEN:
                return "Green";
            case WHITE:
                return "White";
            case ORANGE:
                return "Orange";
            default:
            case NOTHING:
                return "Nothing";
        }
    }

    bool operator==(const Code &c) const
    {
        return (A == c.A) &&
               (B == c.B) &&
               (C == c.C) &&
               (D == c.D);
    }

    bool operator!=(const Code &c) const
    {
        return !((A == c.A) &&
                 (B == c.B) &&
                 (C == c.C) &&
                 (D == c.D));
    }
};

Code* Turn()
{
    Code* out = NULL;
    bool correct = false;
    char result[4];
    while (!correct)
    {
        std::cout << "GUESS: ";
        std::getline(std::cin, result);

        out = new Code(
            Code::ToPeg(result[0]),
            Code::ToPeg(result[1]),
            Code::ToPeg(result[2]),
            Code::ToPeg(result[3])
        );

        correct = out->Verify();
    }
    return out;
}

//TODO
void Feedback(Code* code)
{

}

int main()
{
    bool executing = true;
    int guesses = 0;
    Code* code = new Code();
    Code* guess = NULL;

    std::cout << "Welcome to Mastermind by Thomas Steinholz!" << std::endl;
    std::cout << "You are playing as the \"Code Breaker\" that means you will need to guess the combonations" << std::endl;
    std::cout << "of colors that the AI will generate. Your options are R-B-Y-G-W-O. For example to type in" << std::endl;
    std::cout << "the colors red, blue, yellow, and orange you would type \"RBYO\" untill you get the right combo." << std::endl;
    std::cout << "Good Luck, and don't forget to have fun!" << std::endl << std::endl;

    while (executing)
    {
        guesses++;

        code->PrintState();

        guess = Turn();
        Feedback(guess);

        if (code == guess)
        {
            executing = false;
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Good Work! You just won the game!!" << std::endl;
            std::cout << "----------------------------------" << std::endl;
        }

        if (guesses > 10)
        {
            executing = false;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "Sorry! You lost because you have used all 10 guesses!" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
        }
    }

    delete code;
    delete guess;

    return 0;
}