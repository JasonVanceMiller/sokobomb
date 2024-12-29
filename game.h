#ifndef GAME_H
#define GAME_H

#include "raylib/include/raylib.h"
#include "input.h"

//ENUMS
enum entity_id {
    empty, 
    ground, 
    boomer,
    bomb,
    goal, 
    pit, 
    pit_bloody, 
    pit_wood_box, 
    pit_metal_box, 
    pit_bomb_box, 
    wall, 
    pressure_plate, 
    wood_box,
    metal_box,
    bomb_box,
    entity_id_count
};
typedef enum entity_id entity_id;

//STRUCTS
struct game_state {
    bool holding_bomb;
    int width;
    int height;
    entity_id static_entities[200]; //TODO
    entity_id dynamic_entities[200]; //TODO
};
typedef struct game_state game_state;

struct game_state_history {
    struct game_state_history *next;
    game_state gs; 
};
typedef struct game_state_history game_state_history;
//GLOBALS

extern game_state levels[10];
extern int level_index;
extern game_state gs;
extern game_state_history* gsh;

static int SCREEN_WIDTH  = 1600;
static int SCREEN_HEIGHT = 1000;
static int VERTICAL_PADDING  = 50;


//PROTOTYPES
game_state level_load(const char*);

void state_draw();
Color entity_draw_dispatch(int loc, int x, int y, int cell_size, entity_id e);

bool state_update(action move);
bool push(int loc, int offset);
bool push_wrapped(int loc, int offset, int depth);
void launch (int loc, int offset);
void explode (int loc);
void gravity();

bool check_plates();
bool check_win();
void win_screen();

void game_state_history_clear();
void game_state_history_clear_wrapped(game_state_history*);
void game_state_history_push(game_state gs);
game_state game_state_history_pop();
#endif
