#ifndef FORMS_H
#define FORMS_H

#define FORM_MAX_ELEMENTS 64

#define FORM_MAX_PROPERTIES 32

#include "../../x11-window/src/window_driver.h"
#include <stdint.h>
#include <stdlib.h>

enum ELEMENT_TYPE { E_NONE, E_LABEL, E_BUTTON, E_TEXTBOX };

struct property {
    char *key;
    uint8_t *value;
    uint16_t len;
};

struct element {
    char *name;
    char *value;
    struct element *parent;
    float posx;
    float posy;
    float width;
    float height;
    enum ELEMENT_TYPE type;
    struct property *properties[FORM_MAX_PROPERTIES];
};

struct form {
    struct windri *window;
    struct element *elements[FORM_MAX_ELEMENTS];
    uint8_t need_draw;
};

struct form *create_form (struct windri *window);
struct element *create_element (struct form *form, enum ELEMENT_TYPE type, char *name, char *value);
struct element *create_label (struct form *form, char *value, float x, float y);

int form_update (struct form *form);

#endif