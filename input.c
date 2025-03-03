#include "input.h"
//NOCHECKIN. This  never resets to none. This can be done a lot simpler

////FUNCTIONS
//void button_update(button* b, bool press) {
//    if (*b == released) {
//        *b = none;
//    }
//    if (*b == pressed) {
//        *b = held;
//    }
//    if (*b == none && press) {
//        *b = pressed;
//    }
//    if (*b == held && !press) {
//        *b = released;
//    }
//}
//
//void player_input_update(player_input* input){
//    input->mouse_position = GetMousePosition();
//    button_update(&(input->mouse_button_state), IsMouseButtonDown(MOUSE_BUTTON_LEFT));
//    button_update(&(input->up), IsKeyDown(KEY_W));
//    button_update(&(input->down), IsKeyDown(KEY_S));
//    button_update(&(input->left), IsKeyDown(KEY_A));
//    button_update(&(input->right), IsKeyDown(KEY_D));
//
//}
void input_set(input* inputs){
    if (inputs->up == pressed) {
        inputs->up = held;
    }
    if (inputs->down == pressed) {
        inputs->down = held;
    }
    if (inputs->left == pressed) {
        inputs->left = held;
    }
    if (inputs->right == pressed) {
        inputs->right = held;
    }
    if (inputs->interact == pressed) {
        inputs->interact = held;
    }
    if (inputs->reset == pressed) {
		inputs->reset = held;
    }
    if (inputs->undo == pressed) {
		inputs->undo = held;
    }
    if (inputs->level_next == pressed) {
		inputs->level_next = held;
    }
    if (inputs->level_previous == pressed) {
		inputs->level_previous = held;
    }

    if (!IsKeyDown(KEY_W)) {
        inputs->up = released;
    }
    if (!IsKeyDown(KEY_S)) {
        inputs->down = released;
    }
    if (!IsKeyDown(KEY_A)) {
        inputs->left = released;
    }
    if (!IsKeyDown(KEY_D)) {
        inputs->right = released;
    }
    if (!IsKeyDown(KEY_E)) {
        inputs->interact = released;
    }
    if (!IsKeyDown(KEY_R)) {
		inputs->reset = released;
    }
    if (!IsKeyDown(KEY_Z)) {
		inputs->undo = released;
    }
    if (!IsKeyDown(KEY_P)) {
		inputs->level_next = released;
    }
    if (!IsKeyDown(KEY_O)) {
		inputs->level_previous = released;
    }


    if (inputs->up != held && IsKeyDown(KEY_W)) {
        inputs->up = pressed;
    }
    if (inputs->down != held && IsKeyDown(KEY_S)) {
        inputs->down = pressed;
    }
    if (inputs->left != held && IsKeyDown(KEY_A)) {
        inputs->left = pressed;
    }
    if (inputs->right != held && IsKeyDown(KEY_D)) {
        inputs->right = pressed;
    }
    if (inputs->interact != held && IsKeyDown(KEY_E)) {
        inputs->interact = pressed;
    }
    if (inputs->reset != held && IsKeyDown(KEY_R)) {
		inputs->reset = pressed;
    }
    if (inputs->undo != held && IsKeyDown(KEY_Z)) {
		inputs->undo = pressed;
    }
    if (inputs->level_next != held && IsKeyDown(KEY_P)) {
		inputs->level_next = pressed;
    }
    if (inputs->level_previous != held && IsKeyDown(KEY_O)) {
		inputs->level_previous = pressed;
    }


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
