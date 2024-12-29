#include "input.h"

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
    if (inputs->level_skip == pressed) {
		inputs->level_skip = held;
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
		inputs->level_skip = released;
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
    if (inputs->level_skip != held && IsKeyDown(KEY_P)) {
		inputs->level_skip = pressed;
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
    if (inputs->level_skip == pressed) {
        return level_skip;
    }
    if (inputs->level_previous == pressed) {
        return level_previous;
    }
 
    return none;
}
