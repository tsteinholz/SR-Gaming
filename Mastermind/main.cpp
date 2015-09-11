// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <ctime>
#include <iostream>
#include <string>

struct Code
{
    enum Peg
    {
        RED, BLUE, YELLOW,
        GREEN, WHITE, ORANGE,
        NOTHING,
    };

    Code()
    {
        Peg temp[4];
        for(int i = 0; i < 4; i++)
        {
            switch(rand() % 6)
            {
                case 0:  temp[i] = RED;    break;
                case 1:  temp[i] = BLUE;   break;
                case 2:  temp[i] = YELLOW; break;
                case 3:  temp[i] = GREEN;  break;
                case 4:  temp[i] = WHITE;  break;
                case 5:  temp[i] = ORANGE; break;
                default: temp[i] = NOTHING;
            }
        }
        A = temp[0]; B = temp[1];
        C = temp[2]; D = temp[3];
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
        std::cout<<ToString(A)<<" "<<ToString(B)<<" "<<ToString(C)<<" "<<ToString(D)<<" "<<std::endl;
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
            case 'R': return RED;
            case 'b':
            case 'B': return BLUE;
            case 'y':
            case 'Y': return YELLOW;
            case 'g':
            case 'G': return GREEN;
            case 'w':
            case 'W': return WHITE;
            case 'o':
            case 'O': return ORANGE;
            default:  return NOTHING;
        }
    }

    static std::string ToString(const Peg x)
    {
        switch(x)
        {
            case RED:     return "Red";
            case BLUE:    return "Blue";
            case YELLOW:  return "Yellow";
            case GREEN:   return "Green";
            case WHITE:   return "White";
            case ORANGE:  return "Orange";
            default:
            case NOTHING: return "Nothing";
        }
    }

    bool operator==(const Code& other) const
    {
        // TODO : Fix this sheet
        return ((A == other.A) && (B == other.B) && (C == other.C) && (D == other.D));
    }

    bool operator!=(const Code &other) const {
        return !(*this == other);
    }
};

Code* Turn()
{
    std::string result;
    std::cout << "GUESS: ";
    std::getline(std::cin, result);

    if (result.length() > 3)
    {
        Code::Peg A = Code::ToPeg(result.at(0));
        if (A != Code::Peg::NOTHING)
        {
            Code::Peg B = Code::ToPeg(result.at(1));
            if (B != Code::Peg::NOTHING)
            {
                Code::Peg C = Code::ToPeg(result.at(2));
                if (C != Code::Peg::NOTHING)
                {
                    Code::Peg D = Code::ToPeg(result.at(3));
                    if (D != Code::Peg::NOTHING)
                    {
                        Code* out = new Code(A, B, C, D);
                        out->PrintState();
                        return out;
                    }
                    else std::cout << std::endl << "ERROR: Col 4 '" << result.at(3) << "'" << std::endl << std::endl;
                }
                else std::cout << std::endl << "ERROR: Col 3 '" << result.at(2) << "'" << std::endl << std::endl;
            }
            else std::cout << std::endl << "ERROR: Col 2 '" << result.at(1) << "'" << std::endl << std::endl;
        }
        else std::cout << std::endl << "ERROR: Col 1 '" << result.at(0) << "'" << std::endl << std::endl;
    }
    return NULL;
}

bool Feedback(Code* code, Code* guess)
{
    std::string result = "";
    Code::Peg codePeg[4] = {code->A, code->B, code->C, code->D}, guessPeg[4]= {guess->A, guess->B, guess->C, guess->D};

    for (int i = 0; i < 4; i++)
    {
        for (int j = i; j < 4; j++)
        {
            if (codePeg[i] == guessPeg[j])
            {
                if (i == j) result += "o";
            }
            else
            {
                for (int k = i+1; k < 4; k++)
                {
                    if ((codePeg[k] == guessPeg[j]) && (codePeg[k] != guessPeg[k]))
                    {
                        result += "~";
                    }
                }
            }
        }
    }

    std::cout << "Results : " << result << std::endl;

    return (bool) !result.compare("oooo");
}

int main()
{
    srand(time(NULL));
    bool executing = true;
    int guesses = 1;
    Code* code = new Code();
    //code->PrintState();//DEBUG
    Code* guess = NULL;
    std::cout << "Welcome to Mastermind by Thomas Steinholz!" << std::endl;
    std::cout << "You are playing as the \"Code Breaker\" that means you will need to guess the combonations" << std::endl;
    std::cout << "of colors that the AI will generate. Your options are R-B-Y-G-W-O. For example to type in" << std::endl;
    std::cout << "the colors red, blue, yellow, and orange you would type \"RBYO\" untill you get the right combo." << std::endl;
    std::cout << "Scoring Code:" << std::endl << "o - Right Color, Right Place" << std::endl;
    std::cout << "~ - Right Color, Wrong Place" << std::endl << "x - Neither" << std::endl;
    std::cout << "Good Luck, and don't forget to have fun!" << std::endl << std::endl;

    while (executing)
    {
        std::cout << "|------------|" << std::endl;
        std::cout << "[ Guess " << guesses << "/10 ]" << std::endl;
        std::cout << "|------------|" << std::endl;

        guess = NULL;
        while (!guess) guess = Turn();

        if (Feedback(code, guess))
        {
            executing = false;
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Good Work! You just won the game!!" << std::endl;
            std::cout << "----------------------------------" << std::endl;
        }

        if (guesses > 9)
        {
            executing = false;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "Sorry! You lost because you have used all 10 guesses!" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
        }
        guesses++;
    }

    delete code;
    delete guess;

    return 0;
}
