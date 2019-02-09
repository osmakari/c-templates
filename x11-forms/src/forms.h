#ifndef FORMS_H
#define FORMS_H

#define FORM_MAX_ELEMENTS 64


#include "../../x11-window/src/window_driver.h"
#include <stdint.h>

enum ELEMENT_TYPE { E_LABEL, E_BUTTON, E_TEXTBOX };

struct element {
    char *name;
    struct element *parent;
    float posx;
    float posy;
    float width;
    float height;
    enum ELEMENT_TYPE type;
    uint8_t _properties;
    uint32_t _properties_length;
};
/*
    Properties:
    
*/

struct form {
    struct windri *window;
    struct element *elements[FORM_MAX_ELEMENTS];
};

#endif