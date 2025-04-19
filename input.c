#include "input.h"

////FUNCTIONS
void button_update(button* b, bool press) {
    if (*b == pressed) {
        *b = held;
    }
    if (*b == released && press) {
        *b = pressed;
    }
    if (*b == held && !press) {
        *b = released;
    }
}

void input_set(input* input){
    button_update(&(input->up),              IsKeyDown(KEY_UP)   || IsKeyDown(KEY_W));
    button_update(&(input->down),            IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    button_update(&(input->left),            IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)); 
    button_update(&(input->right),           IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D));
    button_update(&(input->interact),        IsKeyDown(KEY_E));
    button_update(&(input->reset),           IsKeyDown(KEY_R));
    button_update(&(input->undo),            IsKeyDown(KEY_Z));
    button_update(&(input->level_next),      IsKeyDown(KEY_P));
    button_update(&(input->level_previous),  IsKeyDown(KEY_O));

}

action move_get(input* inputs){
    if (inputs->up == pressed) {
        return up;
    }
    if (inputs->down == pressed) {
        return down;
    }
    if (inputs->left == pressed) {
        return left;
    }
    if (inputs->right == pressed) {
        return right;
    }
    if (inputs->interact == pressed) {
        return interact;
    }
    if (inputs->reset == pressed) {
        return reset;
    }
    if (inputs->undo == pressed) {
        return undo;
    }
    if (inputs->level_next == pressed) {
        return level_next;
    }
    if (inputs->level_previous == pressed) {
        return level_previous;
    }
 
    return none;
}
