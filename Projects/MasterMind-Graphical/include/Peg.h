#ifndef PEG_H
#define PEG_H

#include "Button.h"

class Peg : public Button
{
public:
    Peg();
    virtual ~Peg();

    void Update(unsigned int x, unsigned int y);

    void Render();
};

#endif // PEG_H
