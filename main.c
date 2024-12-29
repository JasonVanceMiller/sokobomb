#include "raylib/include/raylib.h"

#include "input.h"
#include "game.h"
#include "levels.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <unistd.h> // For sleep()

//GLOBAL VARIABLES

bool win_pause = false;

game_state levels[10];
int level_index;
game_state gs;
game_state_history* gsh;

int main() {
    levels[0] = level_load(first);
    levels[1] = level_load(gap);
    levels[2] = level_load(jump);
    levels[3] = level_load(box);
    levels[4] = level_load(box2);
    levels[5] = level_load(stuck);
    levels[6] = level_load(good);
    levels[7] = level_load(bad);
    levels[8] = level_load(pinch);
    levels[9] = level_load(tennis);
    level_index = 0;
    gs = levels[0];
    gsh = NULL;


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boomer Boy!");
    SetTargetFPS(60);

    //Vector2 mouse   = GetMousePosition();
    //bool mouse_down     = false;
    input inputs = {0};
    action move;
    
    char str[20];
    while (!WindowShouldClose()) {
        //GET INPUT
        input_set(&inputs);
        move = move_get(&inputs);
        bool err = state_update(move);
        //DRAW
        BeginDrawing();

        ClearBackground(DARKBLUE);
        DrawText("WASD to move. E to place / explode bomb. R to reset. Z to undo. Esc to close.", 5, 5, 30, BLACK);
        sprintf(str, "Level %d / %d", level_index + 1, sizeof(levels) / sizeof(game_state));
        DrawText(str, 5, 50, 30, BLACK);
        if (err) {
            ClearBackground(RED);
        }
        if (check_win()) {
            ClearBackground(GREEN);
            win_pause = true;
        }
        state_draw();

        EndDrawing();
        if (win_pause) {
            sleep(1);
            win_pause = false;
            level_index++;
            if (level_index == sizeof(levels) / sizeof(game_state)) {
                win_screen();
                break;
            }
            gs = levels[level_index];
            game_state_history_clear();
        }
    }
    CloseWindow();
    return 0;
}
