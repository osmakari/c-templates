#include "../forms.h"

struct windri *w;
struct form *f;

int main () {
    w = window_init(480, 360, "Form Example");
    f = create_form(w);
    
    struct element *l = create_label(f, "TestText", 0.3, 0.4);

    while(1) {
        form_update(f);
    }
    return 0;
}