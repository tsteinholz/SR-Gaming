#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Object.h"

class Rectangle : public Object {
      
public:
       Rectangle(int xc, int yc, int xs, int ys, BITMAP* bmp = 0, int color = 0x56b69f);
       ~Rectangle();
       
       void Render();
       
       void Update(float dt);

private:
        int xc, yc, xs, ys, color;
        BITMAP* bmp;
};

#endif
