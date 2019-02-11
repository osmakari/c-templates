#include "forms.h"
#include <stdio.h>

struct form *create_form (struct windri *window) {
    if(window == NULL)
        return NULL;

    struct form *f = (struct form *)malloc(sizeof(struct form));
    f->window = window;
    f->need_draw = 1;
    return f;
}

struct element *create_element (struct form *form, enum ELEMENT_TYPE type, char *name, char *value) {
    if(form == NULL)
        return NULL;

    struct element *e = (struct element *)malloc(sizeof(struct element));
    e->type = type;
    e->name = name;
    e->value = value;
    uint8_t s = 0;
    for(int x = 0; x < FORM_MAX_ELEMENTS; x++) {
        if(form->elements[x] == NULL) {
            form->elements[x] = e;
            s = 1;
            break;
        }
    }
    if(!s) {
        free(e);
        return NULL;
    }
    form->need_draw = 1;
    return e;
}

struct element *create_label (struct form *form, char *value, float x, float y) {
    struct element *e = create_element(form, E_LABEL, "label", value);
    if(e == NULL)
        return NULL;

    e->posx = x;
    e->posy = y;
    form->need_draw = 1;
    return e;
}

int form_update (struct form *form) {
    if(form->need_draw) {
        printf("Drawing form!\n");
        window_clear(form->window, 0, 0, 0, 0);
        for(int x = 0; x < FORM_MAX_ELEMENTS; x++) {
            if(form->elements[x] != NULL) {
                struct element *e = form->elements[x];
                if(e->type == E_LABEL) {
                    draw_text_prop(form->window, e->posx, e->posy, e->value);
                }
            }
        }
        form->need_draw = 0;
    }
    
    window_update(form->window);
    return 0;
}