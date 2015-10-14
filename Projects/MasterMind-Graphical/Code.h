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

    void PrintState()
    {
        std::cout<<ToString(A)<<" "<<ToString(B)<<" "<<ToString(C)<<" "<<ToString(D)<<" "<<std::endl;
    }

    inline bool Verify()
    {
        return A != NOTHING &&
               B != NOTHING &&
               C != NOTHING &&
               D != NOTHING;
    }

    inline static Peg ToPeg(const char x)
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

    inline static std::string ToString(const Peg x)
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

    inline static ALLEGRO_COLOR ToHex(const Peg x)
    {
        switch(x)
        {
            case RED:     return al_map_rgb(255, 0, 0);
            case BLUE:    return al_map_rgb(0, 0, 255);
            case YELLOW:  return al_map_rgb(255, 255, 0);
            case GREEN:   return al_map_rgb(0, 255, 0);
            case WHITE:   return al_map_rgb(255, 255, 255);
            case ORANGE:  return al_map_rgb(255, 255, 0);
            default:
            case NOTHING: return al_map_rgb(0, 0, 0); //TODO : Grayish color
        }
    }

    bool operator==(const Code& other) const
    {
        return ((A == other.A) && (B == other.B) && (C == other.C) && (D == other.D));
    }

    bool operator!=(const Code &other) const {
        return !(*this == other);
    }
};
