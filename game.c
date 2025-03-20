#include "game.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 1600;

bool SPRITE_SHEET_INIT = false;
bool STATIC_SHEET_INIT = false;

Texture2D SPRITE_SHEET;
Texture2D STATIC_SHEET;
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
                out_gs.lower_entities[loc] = wall;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'F':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = frog;
            break;
            case 'm':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = metal_box;
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
            case 'i':
                out_gs.lower_entities[loc] = indigo_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'I':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = indigo_marker;
            break;
            case 'b':
                out_gs.lower_entities[loc] = blue_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = empty;
            break;
            case 'B':
                out_gs.lower_entities[loc] = ground;
                out_gs.middle_entities[loc] = blue_marker;
            break;
            case 'x':
                out_gs.lower_entities[loc] = red_plate;
                out_gs.middle_entities[loc] = blue_marker;
                out_gs.upper_entities[loc] = empty;
            break;
            case '1':
                out_gs.lower_entities[loc] = red_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = metal_box;
            break;
            case '2':
                out_gs.lower_entities[loc] = blue_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = metal_box;
            break;
            case '3':
                out_gs.lower_entities[loc] = indigo_plate;
                out_gs.middle_entities[loc] = empty;
                out_gs.upper_entities[loc] = metal_box;
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
        cell_size -= cell_size % 2;
        starting_x = (SCREEN_WIDTH - gs.width * cell_size) / 2;
        starting_y = PADDING;
    } else {
        //Wide
        cell_size = horrizontal_space / gs.width;
        cell_size -= cell_size % 2;
        starting_y = (SCREEN_HEIGHT - gs.height * cell_size) / 2;
        starting_x = PADDING;
    }
    for (int x = 0; x < gs.width; x++){
        for (int y = 0; y < gs.height; y++){
            int loc = x + y * gs.width;
            entity_draw_dispatch_hole(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.lower_entities[x + y * gs.width]);
        }
    }
    for (int x = 0; x < gs.width; x++){
        for (int y = 0; y < gs.height; y++){
            entity_draw_dispatch_static(x, y, starting_x, starting_y, cell_size);
        }
    }
    for (int x = 0; x < gs.width; x++){
        for (int y = 0; y < gs.height; y++){
            int loc = x + y * gs.width;
            entity_draw_dispatch_pit(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.lower_entities[x + y * gs.width]);
        }
    }
    for (int x = 0; x < gs.width; x++){
        for (int y = 0; y < gs.height; y++){
            int loc = x + y * gs.width;
            //TODO why is middle after upper
            entity_draw_dispatch_dynamic(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.lower_entities[x + y * gs.width]);
            entity_draw_dispatch_dynamic(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.upper_entities[x + y * gs.width]);
            entity_draw_dispatch_dynamic(loc, starting_x + x * cell_size, starting_y + y * cell_size, cell_size, gs.middle_entities[x + y * gs.width]);
        }
    }
}
void entity_draw_dispatch_dynamic(int loc, int x, int y, int cell_size, entity_id e){
    if (!SPRITE_SHEET_INIT) {
        SPRITE_SHEET = LoadTexture("sprite_sheet.png");
        SPRITE_SHEET_INIT = true;
    }
    switch(e){
        case frog: 
            //ALREADY DRAWN
            if (gs.holding_bomb) {
                DrawTexturePro(SPRITE_SHEET, (Rectangle){80,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            } else {
                DrawTexturePro(SPRITE_SHEET, (Rectangle){32,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case bomb: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){48,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case goal: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case red_plate: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            if(gs.upper_entities[loc] == frog || gs.upper_entities[loc] == bomb || gs.upper_entities[loc] == metal_box){
                DrawTexturePro(SPRITE_SHEET, (Rectangle){0,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case red_wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case red_marker: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){48,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case indigo_plate: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){80,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            if(gs.upper_entities[loc] == frog || gs.upper_entities[loc] == bomb || gs.upper_entities[loc] == metal_box){
                DrawTexturePro(SPRITE_SHEET, (Rectangle){0,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case indigo_wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case indigo_marker: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){0,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case blue_plate: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){16,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            if(gs.upper_entities[loc] == frog || gs.upper_entities[loc] == bomb || gs.upper_entities[loc] == metal_box){
                DrawTexturePro(SPRITE_SHEET, (Rectangle){0,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
            }
        break;
        case blue_wall: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){64,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case blue_marker: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){48,48,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case metal_box: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){0,32,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        default: 
        break;

    }
}
void entity_draw_dispatch_hole(int loc, int x, int y, int cell_size, entity_id e){
    switch(e){
        case pit: 
        case pit_bloody: 
        case pit_metal_box: 
            DrawRectangle(x, y, cell_size, cell_size, (Color){20,20,20,255});
        break;
    }
}
void entity_draw_dispatch_pit(int loc, int x, int y, int cell_size, entity_id e){
    if (!SPRITE_SHEET_INIT) {
        SPRITE_SHEET = LoadTexture("sprite_sheet.png");
        SPRITE_SHEET_INIT = true;
    }
    switch(e){
        case pit: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){80,0,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case pit_bloody: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){0,16,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        case pit_metal_box: 
            DrawTexturePro(SPRITE_SHEET, (Rectangle){32,16,16,16}, (Rectangle){x,y,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        break;
        default: 
        break;
    }
}

void entity_draw_dispatch_static(int x, int y, int starting_x, int starting_y, int cell_size){
    if (!STATIC_SHEET_INIT) {
        STATIC_SHEET = LoadTexture("ground_sheet.png");
        STATIC_SHEET_INIT = true;
    }
    //upper left, then upper right, then lower left, then lower right
    entity_id upper_left  = gs.lower_entities[y * gs.width + x];
    entity_id upper_right = gs.lower_entities[y * gs.width + x + 1];
    entity_id lower_left  = gs.lower_entities[(y+1) * gs.width + x];
    entity_id lower_right = gs.lower_entities[(y+1) * gs.width + x + 1];


    if (upper_left  == pit) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){64,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        upper_left = empty;
    }
    if (upper_right == pit) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){64,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        upper_right = empty;
    }
    if (lower_left  == pit) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){64,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        lower_left = empty;
    }
    if (lower_right == pit) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){64,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        lower_right = empty;
    }
    if (upper_left  == pit_bloody) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){80,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        upper_left = empty;
    }
    if (upper_right == pit_bloody) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){80,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        upper_right = empty;
    }
    if (lower_left  == pit_bloody) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){80,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        lower_left = empty;
    }
    if (lower_right == pit_bloody) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){80,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        lower_right = empty;
    }
    if (upper_left  == pit_metal_box) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){96,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        upper_left = empty;
    }
    if (upper_right == pit_metal_box) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){96,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        upper_right = empty;
    }
    if (lower_left  == pit_metal_box) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){96,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        lower_left = empty;
    }
    if (lower_right == pit_metal_box) {
        //DrawTexturePro(STATIC_SHEET, (Rectangle){96,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        lower_right = empty;
    }

    //Normalizing pressureplates for drawing
    if (upper_left != pit && upper_left != wall && upper_left != empty && upper_left != ground) {
        upper_left = ground;
    }
    if (upper_right != pit && upper_right != wall && upper_right != empty && upper_right != ground) {
        upper_right = ground;
    }
    if (lower_left != pit && lower_left != wall && lower_left != empty && lower_left != ground) {
        lower_left = ground;
    }
    if (lower_right != pit && lower_right != wall && lower_right != empty && lower_right != ground) {
        lower_right = ground;
    }

    //SINGLETONS
    if (upper_left == empty && upper_right == empty && lower_left == empty && lower_right == empty) {
        return;
    }
    if (upper_left == ground && upper_right == ground && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == wall && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // GROUND X EMPTY 

    // 1 GROUND X 3 EMPTY 
    if (upper_left == ground && upper_right == empty && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){16,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == ground && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){16,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 2 GROUND 2 EMPTY, not diagonal
    if (upper_left == ground && upper_right == ground && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == empty && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){16,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == ground && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){16,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 3 GROUND 1 EMPTY
    if (upper_left == empty && upper_right == ground && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){16,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == empty && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == ground && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){16,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == ground && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){0,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // WALL X EMPTY 

    // 1 wall X 3 EMPTY 
    if (upper_left == wall && upper_right == empty && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){48,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == wall && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == wall && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){48,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == empty && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 2 wall 2 EMPTY, not diagonal
    if (upper_left == wall && upper_right == wall && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == empty && lower_left == wall && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){48,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == wall && lower_left == empty && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){48,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 3 wall 1 EMPTY
    if (upper_left == empty && upper_right == wall && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){48,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == empty && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == wall && lower_left == empty && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){48,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == wall && lower_left == wall && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){32,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    

    // WALL X ground 

    // 1 WALL X 3 GROUND 
    if (upper_left == wall && upper_right == ground && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){80,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == wall && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){64,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == ground && lower_left == wall && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){80,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == ground && lower_left == ground && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){64,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 2 WALL 2 GROUND, NOT DIAGONAL
    if (upper_left == wall && upper_right == wall && lower_left == ground && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){64,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == ground && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){64,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == ground && lower_left == wall && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){80,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == wall && lower_left == ground && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){80,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 3 WALL 1 GROUND
    if (upper_left == ground && upper_right == wall && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){80,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == ground && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){64,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == wall && lower_left == ground && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){80,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == wall && lower_left == wall && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){64,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 2 EMPTY 1 GROUND 1 WALL
    if (upper_left == ground && upper_right == wall && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){112,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == ground && lower_left == empty && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){112,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    if (upper_left == empty && upper_right == empty && lower_left == wall && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){112,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == empty && lower_left == ground && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){112,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    if (upper_left == empty && upper_right == ground && lower_left == empty && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){96,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == wall && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){96,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    if (upper_left == wall && upper_right == empty && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){96,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == empty && lower_left == wall && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){96,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    //DIAGONAL
    if (upper_left == ground && upper_right == empty && lower_left == empty && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){112,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == empty && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){96,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    if (upper_left == empty && upper_right == ground && lower_left == wall && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){96,96,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == wall && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){112,80,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    // 1 EMPTY 1 GROUND 2 WALL
    if (upper_left == wall && upper_right == empty && lower_left == wall && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){128,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == wall && lower_left == ground && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){144,16,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == ground && lower_left == wall && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){128,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == wall && lower_left == empty && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){144,32,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
     
    if (upper_left == wall && upper_right == wall && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){128,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == wall && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){144,48,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == ground && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){128,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == empty && lower_left == wall && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){144,64,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }

    //some of the 2 ground 1 wall 1 empty cases
    if (upper_left == ground && upper_right == empty && lower_left == ground && lower_right == wall) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){144,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == empty && upper_right == ground && lower_left == wall && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){160,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == ground && upper_right == wall && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){176,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    if (upper_left == wall && upper_right == ground && lower_left == empty && lower_right == ground) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){192,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    // Annoying edge cases
    if (upper_left == wall && upper_right == ground && lower_left == ground && lower_right == empty) {
        DrawTexturePro(STATIC_SHEET, (Rectangle){128,0,16,16}, (Rectangle){starting_x + x * cell_size + cell_size / 2, starting_y + cell_size * y + cell_size / 2,cell_size,cell_size}, (Vector2){0.0, 0.0}, 0, WHITE);
        return;
    }
    return;
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
            level_index = 0;
        }
        gs = levels[level_index];
        game_state_history_clear();
        state_update();
        return false;
    }
    if (move == level_previous) {
        level_index--;
        if (level_index < 0) {
            level_index = sizeof(levels) / sizeof(game_state) - 1;
        }
        gs = levels[level_index];
        game_state_history_clear();
        state_update();
        return false;
    }

    int loc = 0;
    for (; loc < gs.width * gs.height; loc++){
        if (gs.upper_entities[loc] == frog) {
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
    //This stops you when you are inside the wall
    if (gs.middle_entities[loc] == red_wall || gs.middle_entities[loc] == indigo_wall || gs.middle_entities[loc] == blue_wall) {
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
        case frog: 
        case metal_box: 
        case bomb: 
            //PUSHABLE
            if (push_wrapped(loc + offset, offset, depth + 1)) {
                gs.upper_entities[loc + offset] = gs.upper_entities[loc];
                gs.upper_entities[loc] = empty;
            } else {
                return false;
            }
        break;
        case goal: 
            return false;
        break;
    }
    switch(gs.lower_entities[loc]) {
        case wall: 
            return false;
        break;
    }
    switch(gs.middle_entities[loc]) {
        case red_wall:
        case indigo_wall:
        case blue_wall:
            return false;
        default:
        break;
    }
    return true; 
}

void launch (int loc, int offset){
    switch(gs.upper_entities[loc]) {
        case frog: 
        case metal_box: 
        case bomb: 
            if (gs.middle_entities[loc] == red_wall || gs.middle_entities[loc] == indigo_wall || gs.middle_entities[loc] == blue_wall) {
                return;
            }
            int steps = 1;
            //LAUNCH FOREVER
            while(true) {
                if (gs.upper_entities[loc + steps * offset] != empty || 
                    gs.lower_entities[loc + steps * offset] == wall ||
                    gs.middle_entities[loc + steps * offset] == red_wall ||
                    gs.middle_entities[loc + steps * offset] == indigo_wall ||
                    gs.middle_entities[loc + steps * offset] == blue_wall) {
                    //HIT A THING
                    break;
                }
                if (offset == -1 && (loc + steps * offset) % gs.width == 0) {
                    //left edge and still moving. Error out of bounds 
                    gs.upper_entities[loc] = empty;
                    return;
                } else if (offset == 1 && (loc + steps * offset) % gs.width == gs.width - 1) {
                    //right edge and still moving. Error out of bounds 
                    gs.upper_entities[loc] = empty;
                    return;

                } else if (offset == -1 * gs.width && (loc + steps * offset) / gs.width == 0) {
                    //top edge and still moving. Error out of bounds 
                    gs.upper_entities[loc] = empty;
                    return;

                } else if (offset == gs.width && (loc + steps * offset) / gs.width == gs.height - 1) {
                    //bottom edge and still moving. Error out of bounds 
                    gs.upper_entities[loc] = empty;
                    return;
                }
                steps++;
            }
            steps--;
            if (steps > 0){
                //pushual swap needs to happen
                //if (gs.upper_entities[loc + steps * offset] == empty) {
                gs.upper_entities[loc + steps * offset] = gs.upper_entities[loc];
                //}
                gs.upper_entities[loc] = empty;
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
    bool red_on    = check_plates(red_plate);
    bool blue_on   = check_plates(blue_plate);
    bool indigo_on = check_plates(indigo_plate);
    for (int loc = 0; loc < gs.width * gs.height; loc++) {
        switch (gs.lower_entities[loc]) {
            case pit: 
                switch (gs.upper_entities[loc]) {
                    case frog:
                        gs.lower_entities[loc] = pit_bloody;
                    break;
                    case bomb:
                    break;
                    case metal_box:
                        gs.lower_entities[loc] = pit_metal_box;
                    break;
                }
                gs.upper_entities[loc] = empty;
            break;
            case empty: 
                gs.upper_entities[loc] = empty;
            break;
        }
        switch (gs.middle_entities[loc]) {
            //RED
            case red_marker: 
                if (!red_on){
                    gs.middle_entities[loc] = red_wall;
                }
            break;
            case red_wall: 
                if (red_on){
                    gs.middle_entities[loc] = red_marker;
                }
            break;

            //BLUE
            case blue_marker: 
                if (!blue_on){
                    gs.middle_entities[loc] = blue_wall;
                }
            break;
            case blue_wall: 
                if (blue_on){
                    gs.middle_entities[loc] = blue_marker;
                }
            break;

            //INDIGO
            case indigo_marker: 
                if (!indigo_on){
                    gs.middle_entities[loc] = indigo_wall;
                }
            break;
            case indigo_wall: 
                if (indigo_on){
                    gs.middle_entities[loc] = indigo_marker;
                }
            break;
        }
    }
}

//STATUS

void win_screen(int x_offset, int y_offset){
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GREEN);
        DrawText("YOU WIN!!!! AMAZING JOB!!!!", x_offset - 350, y_offset, 40, BLACK);

        EndDrawing();
    }

}

//returns true if all are pressed
bool check_plates(entity_id plate){
    int loc = 0;
    if (plate != red_plate && plate != indigo_plate && plate != blue_plate){
        printf("Checking plates on a non plate\n");
        exit(1);
    }
    for (; loc < gs.width * gs.height; loc++){
        if (gs.lower_entities[loc] == plate) {
            if (gs.upper_entities[loc] != bomb && gs.upper_entities[loc] != frog && gs.upper_entities[loc] != metal_box) {
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
            if (gs.upper_entities[loc] == frog) {
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
