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

game_state levels[50];
int level_index;
int level_max;
game_state gs;
game_state_history* gsh;


int main() {
    bool err = false;
    int win_timer = 0;
    level_index = 0;

    //GOOD BUT RETIRED LEVELS
    //levels[level_max++] = level_load(level_platform);
    //levels[level_max++] = level_load(level_platform2);
    //levels[level_max++] = level_load(level_callback);
    //levels[level_max++] = level_load(level_callback2);
    //levels[level_max++] = level_load(level_halfmeasures);
    //levels[level_max++] = level_load(level_quirky2);
    //levels[level_max++] = level_load(level_quirky3);

    //MOVEMENT LEVELS
    //levels[level_max++] = level_load(level_test);
    //levels[level_max++] = level_load(level_huh);
    //levels[level_max++] = level_load(level_huh2);
    //levels[level_max++] = level_load(level_unstable);
    //levels[level_max++] = level_load(level_unstable2);
    //levels[level_max++] = level_load(level_airlock);
    //levels[level_max++] = level_load(level_callback);

    //MOVEMENT LEVELS
    //levels[level_max++] = level_load(level_idk_dude);
    levels[level_max++] = level_load(level_first);
    levels[level_max++] = level_load(level_gap);
    levels[level_max++] = level_load(level_gaps);
    //INTRO TO BOXES FOR MOVEMENT 
    
    //INTRO TO BOXES ON PLATES
    levels[level_max++] = level_load(level_plate_agg);
    //levels[level_max++] = level_load(level_plate);
    //levels[level_max++] = level_load(level_plate3);
    //levels[level_max++] = level_load(level_plate2);
    levels[level_max++] = level_load(level_box);
    levels[level_max++] = level_load(level_box_);
    levels[level_max++] = level_load(level_box2);
    levels[level_max++] = level_load(level_box3);
    levels[level_max++] = level_load(level_box4);
    levels[level_max++] = level_load(level_box5);
    levels[level_max++] = level_load(level_box6);
    
    //levels[level_max++] = level_load(level_ibox2); //GOOD LEVEL, but out of place


    //UNSTICKING A BOX
    levels[level_max++] = level_load(level_stuck);
    //levels[level_max++] = level_load(level_stuck2); Redundant
    //levels[level_max++] = level_load(level_zigzag);
    levels[level_max++] = level_load(level_zigzag2);
    //levels[level_max++] = level_load(level_good);
    //levels[level_max++] = level_load(level_halved);
    levels[level_max++] = level_load(level_bridge);

    //ISLAND, UNDER CONSTRUCTION

    //levels[level_max++] = level_load(level_island);
    //levels[level_max++] = level_load(level_island_maze);
    //levels[level_max++] = level_load(level_island3);
    //levels[level_max++] = level_load(level_pit_bridge);
    //levels[level_max++] = level_load(level_unstable3);

    //MULTI COLORED

    //levels[level_max++] = level_load(level_multi);
    //levels[level_max++] = level_load(level_locked_explode);
    levels[level_max++] = level_load(level_locked_explode2);
    //levels[level_max++] = level_load(level_locked_explode3);
    levels[level_max++] = level_load(level_cannon);

    levels[level_max++] = level_load(level_unlock2);
    //levels[level_max++] = level_load(level_unlock_xx);
    levels[level_max++] = level_load(level_unlock_xxxx);
    levels[level_max++] = level_load(level_unlock_xxx);
    //levels[level_max++] = level_load(level_unlock_variant);

    levels[level_max++] = level_load(level_quirky);
    //levels[level_max++] = level_load(level_quirky2);
    //levels[level_max++] = level_load(level_quirky3);
    //levels[level_max++] = level_load(level_quirky4);

    
    level_index = 0;
    gs = levels[level_index];
    state_update();
    gsh = NULL;


    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sokobomb!");
    SetTargetFPS(60);

    //InitAudioDevice(); //TODO
    //Vector2 mouse   = GetMousePosition();
    //bool mouse_down     = false;
    input inputs = {0};
    action move;
    
    //Music music = LoadMusicStream("western.mp3"); //TODO
    //PlayMusicStream(music);

    char str[20];
    while (!WindowShouldClose()) {
        //UpdateMusicStream(music); //TODO

        SCREEN_WIDTH = GetScreenWidth();
        SCREEN_HEIGHT = GetScreenHeight();
        //GET INPUT
        if (!win_pause) {
            input_set(&inputs);
            move = move_get(&inputs);
            err = state_move(move);
        }
        //DRAW
        BeginDrawing();

        ClearBackground(DARKBLUE);
        DrawText("WASD or Arrow Keys to move. E to place / explode bomb. R to reset. Z to undo.", 10, 10, 30, BLACK);
        sprintf(str, "Level %d / %d", level_index + 1, level_max);
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
                if (level_index == level_max) {
                    win_screen(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                    break;
                }
                gs = levels[level_index];
                game_state_history_clear();
                state_update();
            }
        }
    }
    //UnloadMusicStream(music); TODO
    //CloseAudioDevice(); TODO
    CloseWindow();
    return 0;
}
