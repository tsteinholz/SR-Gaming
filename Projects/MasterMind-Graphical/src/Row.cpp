#include "Row.h"

Row::Row(unsigned int x, unsigned int y, bool results)
: m_x(x), m_y(y), m_Results(results)
{
    m_Coords[0] = m_x;
    m_Coords[1] = m_Coords[0] + 50;
    m_Coords[2] = m_Coords[2] + 50;
    m_Coords[3] = m_Coords[6] + 50;

    if (m_Results)
    {
        //TODO: results math
    }
}

Row::~Row()
{
    //dtor
}

void Row::Render()
{
    int x = 0;
    for (unsigned int i = 0; i < 4; i++)
    {
        m_Pegs[i].Render(m_Coords[x], m_y, 25);
        x++;
    }

    if (m_Results)
    {
        x = 0;
        for (unsigned int i = 0; i < 4; i++)
        {
            m_ResultPegs[i].Render(m_Coords[x], m_Coords[x++], 5);
            x++;
        }
    }
}
