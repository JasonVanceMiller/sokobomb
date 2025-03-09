#include "game.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 1600;

bool SPRITE_SHEET_INIT = false;
Texture2D SPRITE_SHEET;
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
                out_gs.upper_entities[loc] = empty;
            break;
            case '#':
                out_gs.lower_entities[loc] = goal;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case '%':
                out_gs.lower_entities[loc] = goal;
                out_gs.middle_entities[loc] = red_marker;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'r':
                out_gs.lower_entities[loc] = red_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'R':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = red_marker;
            break;
            case 'y':
                out_gs.lower_entities[loc] = yellow_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'Y':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = yellow_marker;
            break;
            case 'g':
                out_gs.lower_entities[loc] = green_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'G':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = green_marker;
            break;
            case 'x':
                out_gs.lower_entities[loc] = red_plate;
                out_gs.middle_entities[loc] = green_marker;
                out_gs.upper_entities[loc] = empty;
            break;
            default: 
                loc--;
                if (i >= len) {
                    printf("Error loading level, oob\n");
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
    int vertical_space = SCREEN_HEIGHT - 2 * PADDING;
    int horrizontal_space = SCREEN_WIDTH - 2 * PADDING;
    int cell_size = vertical_space / gs.height;
    int starting_x;
    int starting_y;
    if (cell_size <= horrizontal_space / gs.width) {
        //Tall
        starting_x = (SCREEN_WIDTH - gs.width * cell_size) / 2;
        starting_y = PADDING;
    } else {
        //Wide
        cell_size = horrizontal_space / gs.width;
        starting_y = (SCREEN_HEIGHT - gs.height * cell_size) / 2;
        starting_x = PADDING;
    }

    for (int x = 0; x < gs.width; x++){
        for (int y = 0; y < gs.height; y++){
            int loc = x + y * gs.width;
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.lower_entities[x + y * gs.width]);
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.upper_entities[x + y * gs.width]);
            entity_draw_dispatch(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.middle_entities[x + y * gs.width]);
        }
    }
}
Color entity_draw_dispatch(int loc, int x, int y, int cell_size, entity_id e){
    if (!SPRITE_SHEET_INIT) {
        SPRITE_SHEET = LoadTexture("sprite_sheet.png");
        SPRITE_SHEET_INIT = true;
    }
    switch(e){
        case ground: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            //ALREADY DRAWN
        break;
        case boomer: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            //ALREADY DRAWN
            if (gs.holding_bomb) {
                DrawTexturePro(SPRITE_SHEET, (Rectangle){48,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case bomb: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){48,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case goal: 
            //draw ground first
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);

        break;
        case pit: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){80,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case pit_bloody: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){0,16,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case pit_wood_box: 
        break;
        case pit_metal_box: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,16,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case pit_bomb_box: 
        break;
        case wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,16,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case red_plate: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            if(gs.upper_entities[loc] == boomer || gs.upper_entities[loc] == bomb || gs.upper_entities[loc] == metal_box || gs.upper_entities[loc] == wood_box || gs.upper_entities[loc] == bomb_box){
                DrawTexturePro(SPRITE_SHEET, (Rectangle){0,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case red_wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case red_marker: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){48,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case yellow_plate: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){80,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            if(gs.upper_entities[loc] == boomer || gs.upper_entities[loc] == bomb || gs.upper_entities[loc] == metal_box || gs.upper_entities[loc] == wood_box || gs.upper_entities[loc] == bomb_box){
                DrawTexturePro(SPRITE_SHEET, (Rectangle){0,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case yellow_wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case yellow_marker: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){80,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case green_plate: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            if(gs.upper_entities[loc] == boomer || gs.upper_entities[loc] == bomb || gs.upper_entities[loc] == metal_box || gs.upper_entities[loc] == wood_box || gs.upper_entities[loc] == bomb_box){
                DrawTexturePro(SPRITE_SHEET, (Rectangle){0,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case green_wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case green_marker: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){48,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case wood_box: 
        break;
        case metal_box: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){0,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case bomb_box: 
        break;
        default: 
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
