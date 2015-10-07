#ifndef OBJECT_H
#define OBJECT_H

#include <allegro.h>

class Object {
public:
       virtual void Render() {};

       virtual void Update(float dt) {};                 
};

#endif
