// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <iostream>

using namespace std;

// TODO : Convert char to new Colors enum type
struct Code
{
    enum Colors
    {
        RED,
        BLUE,
        YELLOW,
        GREEN,
        WHITE,
        ORANGE
    };

    Code()
    {
        srand(time(NULL));

        A = B = C = D = '';
    }

    Code(char x)
        : A(x), B(x), C(x), D(x) {}

    Code(char a, char b, char c, char d)
        : A(a), B(b), C(c), D(d) {}

    Code(const Code& copy)
        : A(copy.A), B(copy.B), C(copy.C), D(copy.D) {}

    char A, B, C, D;

    void PrintState()
    {

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

int main()
{
    bool executing = true;
    int guesses = 0;

    while (executing && guesses < 10)
    {

        guesses++;
    }

    return 0;
}