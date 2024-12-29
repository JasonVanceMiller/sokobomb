#ifndef INPUT_H
#define INPUT_H

#include "raylib/include/raylib.h"
#include <stdio.h> 
#include <stdlib.h> 

//ENUMS
enum action {
    none,
    up,
    down,
    left, 
    right,
    interact,
    reset,
    undo,
    level_skip,
    level_previous,
    action_count
};
typedef enum action action;

enum button {
    released,
    pressed,
    held,
    button_count
};
typedef enum button button;

//STRUCTS
struct input {
    button up;
    button down;
    button left; 
    button right;
    button interact;
    button reset;
    button undo;
    button level_skip;
    button level_previous;
};
typedef struct input input;

//GLOBALS

//PROTOTYPES
void input_set(input* inputs);
action move_get(input* inputs);

#endif
