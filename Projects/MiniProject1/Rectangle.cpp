#include "Rectangle.h"

Rectangle::Rectangle(int xc, int yc, int xs, int ys, BITMAP* bmp, int color)
: xc(xc), yc(yc), xs(xs), ys(ys), bmp(bmp), color(color) {
    if (!bmp) bmp = create_bitmap_ex(color, xs, ys);
}

Rectangle::~Rectangle() {
   if (!bmp) destroy_bitmap(bmp);
}

void Rectangle::Render() {
     rectfill(bmp, xc, yc, SCREEN_W, SCREEN_H, color);
     blit(bmp, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
     clear_bitmap(bmp);
}

void Rectangle::Update(float dt) {
     
}
