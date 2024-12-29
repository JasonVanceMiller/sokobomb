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
                out_gs.static_entities[loc] = empty;
                out_gs.dynamic_entities[loc] = empty;
            break;
            case '_':
                out_gs.static_entities[loc] = ground;
                out_gs.dynamic_entities[loc] = empty;
            break;
            case 'W':
                out_gs.static_entities[loc] = wall;
                out_gs.dynamic_entities[loc] = empty;
            break;
            case 'B':
                out_gs.static_entities[loc] = ground;
                out_gs.dynamic_entities[loc] = boomer;
            break;
            case 'w':
                out_gs.static_entities[loc] = ground;
                out_gs.dynamic_entities[loc] = wood_box;
            break;
            case 'm':
                out_gs.static_entities[loc] = ground;
                out_gs.dynamic_entities[loc] = metal_box;
            break;
            case 'b':
                out_gs.static_entities[loc] = ground;
                out_gs.dynamic_entities[loc] = bomb_box;
            break;
            case 'p':
                out_gs.static_entities[loc] = pressure_plate;
                out_gs.dynamic_entities[loc] = none;
            break;
            case 'P':
                out_gs.static_entities[loc] = pit;
                out_gs.dynamic_entities[loc] = none;
            break;
            case 'G':
                out_gs.static_entities[loc] = goal;
                out_gs.dynamic_entities[loc] = none;
            break;
            default: 
                loc--;
                if (i >= len) {
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
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.static_entities[x + y * gs.width]);
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.dynamic_entities[x + y * gs.width]);
        }
    }
}

Color entity_draw_dispatch(int loc, int x, int y, int cell_size, entity_id e){
    switch(e){
        case ground: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BEIGE); 
            //ALREADY DRAWN
        break;
        case boomer: 
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.45 , DARKPURPLE);
            if (gs.holding_bomb) {
                //DrawRectangle(x + cell_size / 4, y + cell_size / 4, cell_size / 2, cell_size / 2, BLACK);
                DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.8, y + cell_size * 0.2}, cell_size * 0.1, BROWN);
                DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.7, y + cell_size * 0.3}, cell_size * 0.3, BLACK);
                DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.25, BLACK);
            }
        break;
        case bomb: 
            DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.8, y + cell_size * 0.2}, cell_size * 0.1, BROWN);
            DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.7, y + cell_size * 0.3}, cell_size * 0.3, BLACK);
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.25, BLACK);
            //DrawRectangle(x + cell_size / 4, y + cell_size / 4, cell_size / 2, cell_size / 2, BLACK);
        break;
        case goal: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BEIGE); 

            if(check_plates()){
                DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size / 2, LIME);
                break;
            }
            if(gs.dynamic_entities[loc] == boomer && !check_win()){
                DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size / 2, RED);
                break;
            }
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size / 2, GOLD);

        break;
        case pit: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BLACK); 
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
        break;
        case pit_bloody: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BLACK); 
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.45 , DARKPURPLE);
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
        break;
        case pit_wood_box: 
        break;
        case pit_metal_box: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BLACK); 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, GRAY); 
            DrawRectangle(x+20, y+20, cell_size-40, cell_size-40, DARKGRAY); 
        break;
        case pit_bomb_box: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BLACK); 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, MAROON); 
            DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.8, y + cell_size * 0.2}, cell_size * 0.1, BROWN);
            DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.7, y + cell_size * 0.3}, cell_size * 0.3, BLACK);
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.25, BLACK);
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
        break;
        case wall: 
            DrawRectangle(x, y, cell_size, cell_size, LIGHTGRAY); 
        break;
        case pressure_plate: 
            DrawRectangle(x, y, cell_size, cell_size, WHITE); 
            DrawRectangle(x+1, y+1, cell_size-2, cell_size-2, BEIGE); 
            if(gs.dynamic_entities[loc] == boomer || gs.dynamic_entities[loc] == metal_box || gs.dynamic_entities[loc] == metal_box || gs.dynamic_entities[loc] == wood_box || gs.dynamic_entities[loc] == bomb_box){
                DrawRectangle(x+5, y+5, cell_size-10, cell_size-10, LIME); 
            }else{
                DrawRectangle(x+5, y+5, cell_size-10, cell_size-10, GOLD); 
            }
        break;
        case wood_box: 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, BROWN); 
        break;
        case metal_box: 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, GRAY); 
            DrawRectangle(x+20, y+20, cell_size-40, cell_size-40, DARKGRAY); 
            //DrawCircle(x + cell_size * 0.7, y + cell_size *0.7, cell_size * 0.1, DARKGRAY);
            //DrawCircle(x + cell_size * 0.3, y + cell_size *0.7, cell_size * 0.1, DARKGRAY);
            //DrawCircle(x + cell_size * 0.3, y + cell_size *0.3, cell_size * 0.1, DARKGRAY);
            //DrawCircle(x + cell_size * 0.7, y + cell_size *0.3, cell_size * 0.1, DARKGRAY);
        break;
        case bomb_box: 
            DrawRectangle(x+10, y+10, cell_size-20, cell_size-20, MAROON); 
            DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.8, y + cell_size * 0.2}, cell_size * 0.1, BROWN);
            DrawLineEx((Vector2){x + cell_size / 2, y + cell_size / 2}, (Vector2){x + cell_size * 0.7, y + cell_size * 0.3}, cell_size * 0.3, BLACK);
            DrawCircle(x + cell_size / 2, y + cell_size / 2, cell_size * 0.25, BLACK);
        break;
        default: 
            //NOT GOOD BECAUSE MOST OF DYNAMIC LAYER IS EMPTY
            //DrawRectangle(x, y, cell_size, cell_size, PINK); 
        break;

    }
}

//MOVEMENT 

//return true if error
bool state_update(action move){
    if (move == reset) {
        game_state_history_push(gs);
        gs = levels[level_index];
        return false;
    }
    if (move == undo) {
        gs = game_state_history_pop();
        return false;
    }
    if (move == level_skip) {
        level_index++;
        if (level_index >= sizeof(levels) / sizeof(game_state)) {
            level_index = (sizeof(levels) / sizeof(game_state)) - 1;
        }
        gs = levels[level_index];
        game_state_history_clear();
        return false;
    }
    if (move == level_previous) {
        level_index--;
        if (level_index < 0) {
            level_index = 0;
        }
        gs = levels[level_index];
        game_state_history_clear();
        return false;
    }

    int loc = 0;
    for (; loc < gs.width * gs.height; loc++){
        if (gs.dynamic_entities[loc] == boomer) {
            goto found;
        }
    }
    return true;
found:

    if (move != none) {
        game_state_history_push(gs);
    }
    if (move == up) {
        push(loc, -1 * gs.width);
        gravity();
        return false;
    }
    if (move == down) {
        push(loc, gs.width);
        gravity();
        return false;
    }
    if (move == left) {
        push(loc, -1);
        gravity();
        return false;
    }
    if (move == right) {
        push(loc, 1);
        gravity();
        return false;
    }
    if (move == interact) {
        for (int i = 0; i < gs.width * gs.height; i++){
            if (gs.dynamic_entities[i] == bomb) {
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
            if (gs.dynamic_entities[loc] == empty) {
                gs.dynamic_entities[loc] = bomb;
                gs.holding_bomb = false;
            }
        }
        return true;
    }
    return false;
}

bool push_wrapped(int loc, int offset, int depth){
    if (depth >= 3) {
        //Not strong enough to push 2 things + the empty space
        return false;
    }
    //DEBUG
    if (offset != -1 * gs.width && offset != -1 && offset != 1 && offset != gs.width) {
        printf("Bad offset of %d\n", offset);
        exit(1);
    }
    switch(gs.static_entities[loc]) {
        case wall: 
            return false; 
        break;
        default:
            //PASS THROUGH TO DYNAMIC CASE
        break;
    }
    switch(gs.dynamic_entities[loc]) {
        case boomer: 
        case wood_box: 
        case metal_box: 
        case bomb_box: 
        case bomb: 
            //PUSHABLE
            if (push_wrapped(loc + offset, offset, depth + 1)) {
                gs.dynamic_entities[loc + offset] = gs.dynamic_entities[loc];
                gs.dynamic_entities[loc] = empty;
            } else {
                return false;
            }
        break;
        default:
        break;
    }
    return true; 
}

void launch (int loc, int offset){
    switch(gs.dynamic_entities[loc]) {
        case boomer: 
        case metal_box: 
        case bomb_box: 
        case bomb: 
            int steps = 1;
            for (;steps < 5; steps++) {
                if (gs.dynamic_entities[loc + steps * offset] != empty || gs.static_entities[loc + steps * offset] == wall) {
                    //HIT A THING
                    break;
                }
            }
            steps--;
            if (steps > 0){
                //pushual swap needs to happen
                //if (gs.dynamic_entities[loc + steps * offset] == empty) {
                gs.dynamic_entities[loc + steps * offset] = gs.dynamic_entities[loc];
                //}
                gs.dynamic_entities[loc] = empty;
            }
            if (gs.dynamic_entities[loc + steps * offset] == bomb_box || gs.dynamic_entities[loc + steps * offset] == bomb) {
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
    gs.dynamic_entities[loc] = empty;
    launch(loc - gs.width, -1 * gs.width);
    launch(loc - 1, -1);
    launch(loc + 1, 1);
    launch(loc + gs.width, gs.width);
    gravity();
}

void gravity(){
    for (int loc = 0; loc < gs.width * gs.height; loc++) {
        switch (gs.static_entities[loc]) {
            case pit_bomb_box: 
            case pit: 
                switch (gs.dynamic_entities[loc]) {
                    case boomer:
                        gs.static_entities[loc] = pit_bloody;
                    break;
                    case bomb:
                    break;
                    case wood_box:
                    break;
                    case metal_box:
                        gs.static_entities[loc] = pit_metal_box;
                    break;
                    case bomb_box:
                        gs.static_entities[loc] = pit_bomb_box;
                    break;
                }
                gs.dynamic_entities[loc] = empty;
            break;
            case empty: 
                gs.dynamic_entities[loc] = empty;
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

bool check_plates(){
    int loc = 0;
    for (; loc < gs.width * gs.height; loc++){
        if (gs.static_entities[loc] == pressure_plate) {
            if (gs.dynamic_entities[loc] != boomer && gs.dynamic_entities[loc] != metal_box && gs.dynamic_entities[loc] != wood_box && gs.dynamic_entities[loc] != bomb_box) {
                return false;
            }
        }
    }
    return true;
}

bool check_win(){
    int loc = 0;
    for (; loc < gs.width * gs.height; loc++){
        if (gs.static_entities[loc] == pressure_plate) {
            if (gs.dynamic_entities[loc] != metal_box && gs.dynamic_entities[loc] != wood_box && gs.dynamic_entities[loc] != bomb_box) {
                return false;
            }
        }
        if (gs.static_entities[loc] == goal) {
            if (gs.dynamic_entities[loc] != boomer) {
                return false;
            }
        }
    }
    return true;
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
