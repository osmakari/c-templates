#include "window_driver.h"
#include <stdio.h>
#include <time.h>

struct windri *w;

void onresize () {
    printf("Window resized %i %i\n", w->window_width, w->window_height);
}

int main () {

    w = window_init(200, 200, "This is a window");
    draw_line_prop(w, 0.1, 0.1, 0.9, 0.9);
    draw_text_prop(w, 0.1, 0.8, "text");
    w->onresize = onresize;
    while(1) {
        window_update ();
        if(get_mouse(w)) {
            printf("Mouse clicked: %i\n", get_mouse(w));
            draw_rectangle(w, w->mouse_x - 5, w->mouse_y - 5, 10, 10);
        }
    }
    return 0;
}