#ifndef BUTTON_H
#define BUTTON_H

class Button
{
    public:
        Button();
        virtual ~Button();

        virtual void Update(unsigned int x, unsigned int y) {}

        virtual void Render() {}
};

#endif // BUTTON_H
