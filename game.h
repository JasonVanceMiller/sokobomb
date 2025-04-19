#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "input.h"

//ENUMS
enum entity_id {
    empty, 
    ground, 
    frog,
    bomb,
    goal, 
    pit, 
    pit_bloody, 
    pit_metal_box, 
    wall, 
    metal_box,
    red_plate, 
    red_marker, 
    red_wall, 
    blue_plate, 
    blue_marker, 
    blue_wall, 
    indigo_plate, 
    indigo_marker, 
    indigo_wall, 
    entity_id_count
};
typedef enum entity_id entity_id;

//STRUCTS
struct game_state {
    bool holding_bomb;
    int width;
    int height;
    int depth;
    int explosion_position;
    int explosion_expiration;
    //lower entities are floor stuffs
    entity_id lower_entities[500]; //TODO
    //middle entites are the gates
    entity_id middle_entities[500]; //TODO
    //upper entiteis are typically pushable
    entity_id upper_entities[500]; //TODO
};
typedef struct game_state game_state;

struct game_state_history {
    struct game_state_history *next;
    game_state gs; 
};
typedef struct game_state_history game_state_history;
//GLOBALS

extern game_state levels[50];
extern int level_index;
extern int level_max;
extern game_state gs;
extern game_state_history* gsh;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//static int SCREEN_WIDTH  = 1600; //16:9
//static int SCREEN_HEIGHT = 900; 
static int PADDING  = 100;


//PROTOTYPES
game_state level_load(const char*);

void state_draw();
void draw_explosion(int x, int y, int starting_x, int starting_y, int cell_size);
void entity_draw_dispatch(int x, int y, int starting_x, int starting_y, int cell_size, entity_id (*entities)[500]);

bool state_move(action move);
bool push(int loc, int offset);
bool push_wrapped(int loc, int offset, int depth);
void launch (int loc, int offset);
void explode (int loc);
void state_update();

bool check_plates(entity_id); //id of plate type
bool check_win();
void win_screen(int x_offset, int y_offset);

void game_state_history_clear();
void game_state_history_clear_wrapped(game_state_history*);
void game_state_history_push(game_state gs);
game_state game_state_history_pop();
#endif
