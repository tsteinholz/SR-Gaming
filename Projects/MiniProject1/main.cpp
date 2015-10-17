// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main(){
    printf("We started.\n");

    ALLEGRO_DISPLAY *display = NULL;

    //Initializing Allegro and see if it is allright.
    if(!al_init()) {
        printf("al_init Failed!\n");
        return -1;
    }

    //Initializing the primitives addon.
    if(!al_init_primitives_addon()) {
        printf("al_init_primitives_addon Failed!\n");
        return -1;
    }

    //Create the display (window).
    display = al_create_display(640, 480);

    //Check if the window was created Successfully.
    if(!display) {
        printf("al_create_display Failed!\n");
        return -1;
    }

    //Paint, paint, paint, Paint it black!
    //Actually, paind a hidden screen (a buffer), that we'll apply later.
    al_clear_to_color(al_map_rgb(0,0,0));

    //Draw an ugly red triangle to the buffer.
    al_draw_filled_triangle(10, 10, 200, 200, 350, 230, al_map_rgb(255,0,0));

    //Apply the buffer to the front.
    al_flip_display();

    //Wait for 3 secs.
    al_rest(3.0);

    //Destroying the display we created, to avoid memory leaking.
    al_destroy_display(display);

    return 0;
}
