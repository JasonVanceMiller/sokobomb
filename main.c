#include <raylib.h>

#include "input.h"
#include "game.h"
#include "levels.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <unistd.h> // For sleep()

//GLOBAL VARIABLES

bool win_pause = false;

game_state levels[20];
int level_index;
game_state gs;
game_state_history* gsh;

int main() {
    bool err = false;
    int win_timer = 0;
    level_index = 0;
    levels[level_index++] = level_load(level_first);
    levels[level_index++] = level_load(level_gap);
    levels[level_index++] = level_load(level_jump);
    levels[level_index++] = level_load(level_plate);
    levels[level_index++] = level_load(level_box);
    levels[level_index++] = level_load(level_box2);
    levels[level_index++] = level_load(level_box3);
    levels[level_index++] = level_load(level_plate3);
    levels[level_index++] = level_load(level_plate2);
    levels[level_index++] = level_load(level_stuck);
    levels[level_index++] = level_load(level_zigzag);
    levels[level_index++] = level_load(level_good);
    //levels[level_index++] = level_load(level_bad);
    levels[level_index++] = level_load(level_multi);
    levels[level_index++] = level_load(level_maze);
    levels[level_index++] = level_load(level_unlock2);
    levels[level_index++] = level_load(level_quirky);
    levels[level_index++] = level_load(level_breeze);
    levels[level_index++] = level_load(level_block_free);
    levels[level_index++] = level_load(level_halfway);
    levels[level_index++] = level_load(level_unlock);
    //levels[level_index++] = level_load(level_joseph); // BROKEN
    //levels[level_index++] = level_load(level_pinch);
    //levels[level_index++] = level_load(level_tennis);
    level_index = 0;
    gs = levels[level_index];
    state_update();
    gsh = NULL;


    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boomer Boy!");
    SetTargetFPS(60);

    //Vector2 mouse   = GetMousePosition();
    //bool mouse_down     = false;
    input inputs = {0};
    action move;
    
    char str[20];
    while (!WindowShouldClose()) {
        //GET INPUT
        if (!win_pause) {
            input_set(&inputs);
            move = move_get(&inputs);
            err = state_move(move);
        }
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
            win_timer++;
            if (win_timer > 60) {
                win_timer = 0;
                win_pause = false;
                level_index++;
                if (level_index == sizeof(levels) / sizeof(game_state)) {
                    win_screen();
                    break;
                }
                gs = levels[level_index];
                game_state_history_clear();
                state_update();
            }
        }
    }
    CloseWindow();
    return 0;
}
