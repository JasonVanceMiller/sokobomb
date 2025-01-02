#include "game.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


//LEVEL LOADING
game_state level_load(const char* level){
    int len = strlen(level);
    int height = 1;
    int width;
    int cells = 0;
    for (int i = 0; i < len; i++){
        if (level[i] == '\n'){
            height++;
        }
        if (level[i] != '\n' && level[i] != '\0'){
            cells++;
        }
    }
    if (cells % height != 0) {
        printf("%s\n", level);
        printf("Poorly formed level, ragged rows\n");
        exit(1);
    }
    width = cells / height;

    game_state out_gs = {0};
    out_gs.width = width;
    out_gs.height = height;

    int i = 0;
    for (int loc = 0; loc < cells; loc++){
        switch (level[i]) {
            case '.':
                out_gs.lower_entities[loc] = empty;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case '_':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'W':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = wall;
            break;
            case 'B':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = boomer;
            break;
            case 'w':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = wood_box;
            break;
            case 'm':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = metal_box;
            break;
            case 'b':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = bomb_box;
            break;
            case 'P':
                out_gs.lower_entities[loc] = pit;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = none;
            break;
            case '#':
                out_gs.lower_entities[loc] = goal;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = none;
            break;
            case '%':
                out_gs.lower_entities[loc] = goal;
                out_gs.middle_entities[loc] = red_marker;
                out_gs.upper_entities[loc] = none;
            break;
            case 'r':
                out_gs.lower_entities[loc] = red_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = none;
            break;
            case 'R':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = red_marker;
            break;
            case 'y':
                out_gs.lower_entities[loc] = yellow_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = none;
            break;
            case 'Y':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = yellow_marker;
            break;
            case 'g':
                out_gs.lower_entities[loc] = green_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = none;
            break;
            case 'G':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = green_marker;
            break;
            default: 
                loc--;
                if (i >= len) {
                    printf("Error loading level\n");
                    exit(1);
                }
            break;
        }
        i++;
    }
    return out_gs;
}

//DRAWING 

void state_draw(){
    int vertical_space = SCREEN_HEIGHT - 2 * VERTICAL_PADDING;
    int cell_size = vertical_space / gs.height;

    int starting_x = (SCREEN_WIDTH - gs.width * cell_size) / 2;
    int starting_y = VERTICAL_PADDING;

    for (int x = 0; x < gs.width; x++){
        for (int y = 0; y < gs.height; y++){
            int loc = x + y * gs.width;
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.lower_entities[x + y * gs.width]);
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.upper_entities[x + y * gs.width]);
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.middle_entities[x + y * gs.width]);
        }
    }
}
void draw_bomb(int x, int y, int cell_size){
    DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.8, y + cell_size * 0.2}, cell_size * 0.1, BROWN);
    DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.7, y + cell_size * 0.3}, cell_size * 0.3, BLACK);
    DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.25, BLACK);
}
void draw_pit_bottom(int x, int y, int cell_size){
    DrawRectangle(x, y, cell_size, cell_size, WHITE); 
    DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BLACK); 
}
void draw_pit_spikes(int x, int y, int cell_size){
    DrawTriangle(
        (Vector2){x + cell_size * 0.55, y + cell_size * 0.5},
        (Vector2){x + cell_size * 0.65, y + cell_size * 0.5},
        (Vector2){x + cell_size * 0.6, y + cell_size * 0.2},
        LIGHTGRAY
    );            
    DrawTriangle(
        (Vector2){x + cell_size * 0.25, y + cell_size * 0.4},
        (Vector2){x + cell_size * 0.35, y + cell_size * 0.4},
        (Vector2){x + cell_size * 0.3, y + cell_size * 0.1},
        LIGHTGRAY
    );            
    DrawTriangle(
        (Vector2){x + cell_size * 0.45, y + cell_size * 0.8},
        (Vector2){x + cell_size * 0.55, y + cell_size * 0.8},
        (Vector2){x + cell_size * 0.5, y + cell_size * 0.5},
        LIGHTGRAY
    );            
}
void draw_pit_blood(int x, int y, int cell_size){
    DrawTriangle(
        (Vector2){x + cell_size * 0.575, y + cell_size * 0.35},
        (Vector2){x + cell_size * 0.625, y + cell_size * 0.35},
        (Vector2){x + cell_size * 0.6, y + cell_size * 0.2},
        RED
    );            
    DrawTriangle(
        (Vector2){x + cell_size * 0.275, y + cell_size * 0.25},
        (Vector2){x + cell_size * 0.325, y + cell_size * 0.25},
        (Vector2){x + cell_size * 0.3, y + cell_size * 0.1},
        RED
    );            
    DrawTriangle(
        (Vector2){x + cell_size * 0.475, y + cell_size * 0.65},
        (Vector2){x + cell_size * 0.525, y + cell_size * 0.65},
        (Vector2){x + cell_size * 0.5, y + cell_size * 0.5},
        RED
    );            
}
void draw_marker(int x, int y, int cell_size){
    DrawRectangle(x, y, cell_size, cell_size, WHITE); 
    DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BEIGE); 
}
void draw_plate(int loc, int x, int y, int cell_size, Color color){
    draw_marker(x, y, cell_size);
    if(gs.upper_entities[loc] == boomer || gs.upper_entities[loc] == metal_box || gs.upper_entities[loc] == metal_box || gs.upper_entities[loc] == wood_box || gs.upper_entities[loc] == bomb_box){
        DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, PURPLE); 
    }
    DrawRectangle(x+5, y+5, cell_size-10, cell_size-10, color); 
}
Color entity_draw_dispatch(int loc, int x, int y, int cell_size, entity_id e){
    switch(e){
        case ground: 
            draw_marker(x, y, cell_size);
            //ALREADY DRAWN
        break;
        case boomer: 
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.45 , DARKPURPLE);
            if (gs.holding_bomb) {
                draw_bomb(x, y, cell_size);
            }
        break;
        case bomb: 
            draw_bomb(x, y, cell_size);
            //DrawRectangle(x + cell_size / 4, y + cell_size / 4, cell_size / 2, cell_size / 2, BLACK);
        break;
        case goal: 
            draw_marker(x, y, cell_size);
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.48 , DARKPURPLE);
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.40 , BEIGE);

        break;
        case pit: 
            draw_pit_bottom(x, y, cell_size);
            draw_pit_spikes(x, y, cell_size);
        break;
        case pit_bloody: 
            draw_pit_bottom(x, y, cell_size);
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.45 , DARKPURPLE);
            draw_pit_spikes(x, y, cell_size);
            draw_pit_blood(x, y, cell_size);
        break;
        case pit_wood_box: 
        break;
        case pit_metal_box: 
            draw_pit_bottom(x, y, cell_size);
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, GRAY); 
            DrawRectangle(x+20, y+20, cell_size-40, cell_size-40, DARKGRAY); 
        break;
        case pit_bomb_box: 
            draw_pit_bottom(x, y, cell_size);
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, MAROON); 
            draw_bomb(x, y, cell_size);
            draw_pit_spikes(x, y, cell_size);
        break;
        case wall: 
            DrawRectangle(x, y, cell_size, cell_size, GRAY); 
        break;
        case red_plate: 
            draw_plate(loc, x, y, cell_size, RED);
        break;
        case yellow_plate: 
            draw_plate(loc, x, y, cell_size, GOLD);
        break;
        case green_plate: 
            draw_plate(loc, x, y, cell_size, DARKGREEN);
        break;
        case red_marker: 
            DrawRectangleLinesEx((Rectangle){x+1, y+1, cell_size-2, cell_size-2}, 10, RED);
        break;
        case yellow_marker: 
            DrawRectangleLinesEx((Rectangle){x+1, y+1, cell_size-2, cell_size-2}, 10, GOLD);
        break;
        case green_marker: 
            DrawRectangleLinesEx((Rectangle){x+1, y+1, cell_size-2, cell_size-2}, 10, DARKGREEN);
        break;
        case red_wall: 
            DrawRectangleLinesEx((Rectangle){x+1, y+1, cell_size-2, cell_size-2}, 10, RED);
            DrawLineEx((Vector2){x + 4, y + 4}, (Vector2){x + cell_size - 8, y + cell_size - 8}, cell_size * 0.05, RED);
            DrawLineEx((Vector2){x + 4, (y + cell_size) - 8}, (Vector2){(x + cell_size) - 8, y + 4}, cell_size * 0.05, RED);
        break;
        case yellow_wall: 
            DrawRectangleLinesEx((Rectangle){x+1, y+1, cell_size-2, cell_size-2}, 10, GOLD);
            DrawLineEx((Vector2){x + 4, y + 4}, (Vector2){x + cell_size - 8, y + cell_size - 8}, cell_size * 0.05, GOLD);
            DrawLineEx((Vector2){x + 4, y + cell_size - 8}, (Vector2){x + cell_size - 8, y + 4}, cell_size * 0.05, GOLD);
        break;
        case green_wall: 
            DrawRectangleLinesEx((Rectangle){x+1, y+1, cell_size-2, cell_size-2}, 10, DARKGREEN);
            DrawLineEx((Vector2){x + 4, y + 4}, (Vector2){x + cell_size - 8, y + cell_size - 8}, cell_size * 0.05, DARKGREEN);
            DrawLineEx((Vector2){x + 4, y + cell_size - 8}, (Vector2){x + cell_size - 8, y + 4}, cell_size * 0.05, DARKGREEN);
        break;
        case wood_box: 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, BROWN); 
        break;
        case metal_box: 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, GRAY); 
            DrawRectangle(x+20, y+20, cell_size-40, cell_size-40, DARKGRAY); 
        break;
        case bomb_box: 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, MAROON); 
            draw_bomb(x, y, cell_size);
        break;
        default: 
            //NOT GOOD BECAUSE MOST OF upper LAYER IS EMPTY
            //DrawRectangle(x, y, cell_size, cell_size, PINK); 
        break;

    }
}

//MOVEMENT 

//return true if error
bool state_move(action move){
    if (move == reset) {
        game_state_history_push(gs);
        gs = levels[level_index];
        state_update();
        return false;
    }
    if (move == undo) {
        gs = game_state_history_pop();
        return false;
    }
    if (move == level_next) {
        level_index++;
        if (level_index >= sizeof(levels) / sizeof(game_state)) {
            level_index = (sizeof(levels) / sizeof(game_state)) - 1;
        }
        gs = levels[level_index];
        game_state_history_clear();
        state_update();
        return false;
    }
    if (move == level_previous) {
        level_index--;
        if (level_index < 0) {
            level_index = 0;
        }
        gs = levels[level_index];
        game_state_history_clear();
        state_update();
        return false;
    }

    int loc = 0;
    for (; loc < gs.width * gs.height; loc++){
        if (gs.upper_entities[loc] == boomer) {
            goto found;
        }
    }
    return true;
found:

    if (move != none) {
        game_state_history_push(gs);
    }
    if (move == up) {
        if (!push(loc, -1 * gs.width)){
            game_state_history_pop();
        }
        state_update();
        return false;
    }
    if (move == down) {
        if (!push(loc, gs.width)){
			game_state_history_pop();
        }
        state_update();
        return false;
    }
    if (move == left) {
        if (!push(loc, -1)){
			game_state_history_pop();
        }
        state_update();
        return false;
    }
    if (move == right) {
        if (!push(loc, 1)){
			game_state_history_pop();
        }
        state_update();
        return false;
    }
    if (move == interact) {
        for (int i = 0; i < gs.width * gs.height; i++){
            if (gs.upper_entities[i] == bomb) {
                explode(i);
                return false; //TODO SHOULD BE ONLY ONE BOMB?
            }
        }
        gs.holding_bomb = !gs.holding_bomb;
    }
    return false;
}

bool push(int loc, int offset){
    if (push_wrapped(loc, offset, 0)){
        if (gs.holding_bomb) {
            if (gs.upper_entities[loc] == empty) {
                gs.upper_entities[loc] = bomb;
                gs.holding_bomb = false;
            }
        }
        return true;
    }
    return false;
}

//We will only interact with items on our level, and the trust state_update to do gravity based interactions
bool push_wrapped(int loc, int offset, int depth){
    if (gs.middle_entities[loc] == red_wall || gs.middle_entities[loc] == yellow_wall || gs.middle_entities[loc] == green_wall) {
        return false;
    }
    if (depth >= 3) {
        //Not strong enough to push 2 things + the empty space
        return false;
    }
    //DEBUG
    if (offset != -1 * gs.width && offset != -1 && offset != 1 && offset != gs.width) {
        printf("Bad offset of %d\n", offset);
        exit(1);
    }
    switch(gs.upper_entities[loc]) {
        case boomer: 
        case wood_box: 
        case metal_box: 
        case bomb_box: 
        case bomb: 
            //PUSHABLE
            if (push_wrapped(loc + offset, offset, depth + 1)) {
                gs.upper_entities[loc + offset] = gs.upper_entities[loc];
                gs.upper_entities[loc] = empty;
            } else {
                return false;
            }
        break;
        case wall: 
            return false;
        break;
    }
    switch(gs.middle_entities[loc]) {
        case red_wall:
        case yellow_wall:
        case green_wall:
            return false;
        default:
        break;
    }
    return true; 
}

void launch (int loc, int offset){
    switch(gs.upper_entities[loc]) {
        case boomer: 
        case metal_box: 
        case bomb_box: 
        case bomb: 
            if (gs.middle_entities[loc] == red_wall || gs.middle_entities[loc] == yellow_wall || gs.middle_entities[loc] == green_wall) {
                return;
            }
            int steps = 1;
            for (;steps < 5; steps++) {
                if (gs.upper_entities[loc + steps * offset] != empty || 
                    gs.middle_entities[loc + steps * offset] == red_wall ||
                    gs.middle_entities[loc + steps * offset] == yellow_wall ||
                    gs.middle_entities[loc + steps * offset] == green_wall) {
                    //HIT A THING
                    break;
                }
            }
            steps--;
            if (steps > 0){
                //pushual swap needs to happen
                //if (gs.upper_entities[loc + steps * offset] == empty) {
                gs.upper_entities[loc + steps * offset] = gs.upper_entities[loc];
                //}
                gs.upper_entities[loc] = empty;
            }
            if (gs.upper_entities[loc + steps * offset] == bomb_box || gs.upper_entities[loc + steps * offset] == bomb) {
                explode(loc + steps * offset);
            }
        break;
        default:
            return;
        break;
    }
    //EXPLODE DISTANCE
        
}

void explode (int loc){
    gs.upper_entities[loc] = empty;
    launch(loc - gs.width, -1 * gs.width);
    launch(loc - 1, -1);
    launch(loc + 1, 1);
    launch(loc + gs.width, gs.width);
    state_update();
}

void state_update(){
    for (int loc = 0; loc < gs.width * gs.height; loc++) {
        switch (gs.lower_entities[loc]) {
            case pit_bomb_box: 
            case pit: 
                switch (gs.upper_entities[loc]) {
                    case boomer:
                        gs.lower_entities[loc] = pit_bloody;
                    break;
                    case bomb:
                    break;
                    case wood_box:
                    break;
                    case metal_box:
                        gs.lower_entities[loc] = pit_metal_box;
                    break;
                    case bomb_box:
                        gs.lower_entities[loc] = pit_bomb_box;
                    break;
                }
                gs.upper_entities[loc] = empty;
            break;
            case empty: 
                //gs.upper_entities[loc] = empty;
            break;
        }
        switch (gs.middle_entities[loc]) {
            case red_marker: 
                if (!check_plates(red_plate)){
                    gs.middle_entities[loc] = red_wall;
                }
            break;
            case red_wall: 
                if (check_plates(red_plate)){
                    gs.middle_entities[loc] = red_marker;
                }
            break;
            case yellow_marker: 
                if (!check_plates(yellow_plate)){
                    gs.middle_entities[loc] = yellow_wall;
                }
            break;
            case yellow_wall: 
                if (check_plates(yellow_plate)){
                    gs.middle_entities[loc] = yellow_marker;
                }
            break;
            case green_marker: 
                if (!check_plates(green_plate)){
                    gs.middle_entities[loc] = green_wall;
                }
            break;
            case green_wall: 
                if (check_plates(green_plate)){
                    gs.middle_entities[loc] = green_marker;
                }
            break;
        }
    }
}

//STATUS

void win_screen(){
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GREEN);
        DrawText("YOU WIN!!!! AMAZING JOB!!!!", 550, 500, 40, BLACK);

        EndDrawing();
    }

}

//returns true if all are pressed
bool check_plates(entity_id plate){
    int loc = 0;
    if (plate != red_plate && plate != yellow_plate && plate != green_plate){
        printf("Checking plates on a non plate\n");
        exit(1);
    }
    for (; loc < gs.width * gs.height; loc++){
        if (gs.lower_entities[loc] == plate) {
            if (gs.upper_entities[loc] != bomb && gs.upper_entities[loc] != boomer && gs.upper_entities[loc] != metal_box && gs.upper_entities[loc] != wood_box && gs.upper_entities[loc] != bomb_box) {
                return false;
            }
        }
    }
    return true;
}

bool check_win(){
    int loc = 0;
    for (; loc < gs.width * gs.height; loc++){
        if (gs.lower_entities[loc] == goal) {
            if (gs.upper_entities[loc] == boomer) {
                return true;
            }
        }
    }
    return false;
}

//HISTORY

void game_state_history_clear(){
    game_state_history_clear_wrapped(gsh);
    gsh = NULL;
}

void game_state_history_clear_wrapped(game_state_history *gsht){
    if (!gsht) {
        return;
    }
    game_state_history_clear_wrapped(gsht->next);
    free(gsht);
    return;
}

void game_state_history_push(game_state gs){
    game_state_history * node = (game_state_history *)malloc(sizeof(game_state_history));
    node->gs = gs;
    node->next = gsh;
    gsh = node;
}

game_state game_state_history_pop(){
    if (gsh == NULL) {
        return gs;
    }
    game_state_history *node = gsh;
    gsh = gsh->next;
    game_state out = node->gs;
    free(node);
    return out;
}
