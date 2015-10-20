// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT* century_gothic24;

    if(!al_init())
    {
        printf("al_init Failed!\n");
        return -1;
    }
    if(!al_init_primitives_addon())
    {
        printf("al_init_primitives_addon Failed!\n");
        return -1;
    }
    display = al_create_display(640, 480);
    if(!display)
    {
        printf("al_create_display Failed!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    century_gothic24  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 24, ALLEGRO_ALIGN_CENTRE);
    // Paint a hidden screen (a buffer), that we'll apply later.
    al_clear_to_color(al_map_rgb(0,0,0));
    // Draw an ugly red triangle to the buffer.
    al_draw_filled_triangle(10, 10, 200, 200, 350, 230, al_map_rgb(255,0,0));
    // Draw text to the buffer
    al_draw_text(century_gothic24, al_map_rgb(255,255,255), 550, 440, ALLEGRO_ALIGN_CENTRE, "Hello World!");
    // Draw a line to the buffer
    al_draw_line(400,400,500,34,al_map_rgb(255,255,255), 5);
    // Draw a circle
    al_draw_circle(300,300, 50, al_map_rgb(255,255,0), 5);
    // Draw Eclipse
    al_draw_filled_ellipse(500, 300, 40, 56, al_map_rgb(255,0,255));
    // Draw a rectangle
    al_draw_rectangle(100,200,200,300,al_map_rgb(0,255,0), 6);s
    // Draw a polygon
    al_draw_filled_rectangle(0,480,50,400,al_map_rgb(25,185,35));
    al_draw_filled_rectangle(0,480,200,450,al_map_rgb(25,185,35));
    // Apply the buffer to the front.
    al_flip_display();
    // Wait for 3 secs.
    al_rest(10.0);
    // Destroying the display we created, to avoid memory leaking.
    al_destroy_display(display);

    return 0;
}
