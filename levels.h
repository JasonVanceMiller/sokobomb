const char* level_first = 
".......\n"
"WWWWWWW\n"
"W_____W\n"
"W_B_#_W\n"
"W_____W\n"
"WWWWWWW\n"
".......";

const char* level_gap = 
".......\n"
"WWWWWWW\n"
"W__P__W\n"
"W_BP#_W\n"
"W__P__W\n"
"WWWWWWW\n"
".......";

const char* level_jump = 
"...WWWWWWWW\n"
"...W__P___W\n"
"...W_BP___W\n"
"...W__P___W\n"
"...WWWWPPPW\n"
"WWWWWWWPPPW\n"
"W___PPP___W\n"
"W___PPP___W\n"
"W___PPP___W\n"
"WPPPWWWWWWW\n"
"WPPPW......\n"
"W_#_W......\n"
"WPPPW......\n"
"WWWWW......";

const char* level_plate = 
"WWWWWWWWW\n"
"W___W___W\n"
"W_B_R___W\n"
"W___R_#_W\n"
"W_r_R___W\n"
"W___W___W\n"
"WWWWWWWWW";

const char* level_plate2 = 
"..........\n"
"WWWWWWWWWW\n"
"W____W__PW\n"
"W_B_rR_#PW\n"
"W____W__PW\n"
"WWWWWWWWWW\n"
"..........";

const char* level_plate3 = 
"..........\n"
"WWWWWWWWWW\n"
"W____W___W\n"
"W_BrrR_#_W\n"
"W____W___W\n"
"WWWWWWWWWW\n"
"..........";


const char* level_box = 
"WWWWWWW\n"
"W_____W\n"
"W_B_%_W\n"
"W__m__W\n"
"W_r_r_W\n"
"W_____W\n"
"WWWWWWW";

const char* level_box2 = 
"WWWWWWW\n"
"W__P__W\n"
"W_BP__W\n"
"W_rP%_W\n"
"W__Pm_W\n"
"W__P__W\n"
"WWWWWWW";

const char* level_box3 = 
"WWWWWWWWW\n"
"W__PPP__W\n"
"W_BPPP__W\n"
"W_rPPP%_W\n"
"W__PPPm_W\n"
"W__PPP__W\n"
"WWWWWWWWW";

const char* level_zigzag = 
"WWWWW\n"
"WBmPW\n"
"Wm__W\n"
"WPm_W\n"
"WWWrW\n"
"W%_rW\n"
"WWWWW";

const char* level_stuck = 
"..WWW..\n"
".WW%WW.\n"
"WW___WW\n"
"W__B__W\n"
"W_r_r_W\n"
"W__m__W\n"
"WWW_WWW\n"
"..WWW..";

const char* level_good = 
".WWW.WWW.\n"
".W%WWW_W.\n"
".W_r___W.\n"
"WWW__P_WW\n"
"WrP_B___W\n"
"W_m____WW\n"
"WWWWW_WW.\n"
"....WWW..";

//const char* level_bad = 
//"...........\n"
//"WWWWWWWWWWW\n"
//"W#PP_bmPP_W\n"
//"WWWWW_WWWWW\n"
//"WB_bb_mPP_W\n"
//"WWWWWWWWWWW\n"
//"...........";

const char* level_multi = 
".................\n"
"WWWWWWWWWWWWWWWWW\n"
"W__W__W__WWWW___W\n"
"W__R__Y__GYRP___W\n"
"WBrRmyYmgGYRP_#_W\n"
"W__R__Y__GYRP___W\n"
"W__W__W__WWWW___W\n"
"WWWWWWWWWWWWWWWWW\n"
".................";

const char* level_maze = 
"WWWWWWW\n"
"WWRyG#W\n"
"WBrYgWW\n"
"WWWWWWW";

const char* level_breeze = 
".WWW...\n"
"WWPW...\n"
"W#PWWWW\n"
"WWPPm_W\n"
"WW_WWRW\n"
"W_m_r_W\n"
"W_B_WWW\n"
"WWWWW..";

const char* level_halfway = 
".......WWWWW\n"
".....WWW_gGW\n"
".....W%W___W\n"
"...WWWPP_mWW\n"
"...W____WRWW\n"
"WWWW___BrrWW\n"
"WP__P_mP_WW.\n"
"WW___yYWWW..\n"
".WW__WWW....\n"
"..WWWW......";

const char* level_unlock = 
".......WWW\n"
"WWWWWWWW%W\n"
"WrWP__P__W\n"
"WGg__P_y_W\n"
"WWWm__Y_WW\n"
"..WB_WWWW.\n"
"..WWWW....";

const char* level_unlock2 = 
"WWWWWWW\n"
"W_m__rW\n"
"W_B_WRW\n"
"WWWWWgW\n"
"....WGW\n"
"....W%W\n"
"....WWW";

const char* level_pinch = 
".............\n"
".............\n"
"WWWW.........\n"
"W__WWWWW.....\n"
"W_B_b__WWWWWW\n"
"W__PPP__PP#PW\n"
"WWWWWWWWWWWWW\n"
".............\n"
".............";

const char* level_tennis = 
"................\n"
"..WWWWW...WWWWW.\n"
"..W___W...W___W.\n"
"WWW_r_WWWWW_m_WW\n"
"W%__m__PPPr___BW\n"
"WWW_r_WWWWW_b_WW\n"
"..W___W...W___W.\n"
"..WWWWW...WWWWW.\n"
"................";

const char* level_block_free = 
"WWWWWWWW\n"
"W_mBGPrW\n"
"W_GgWWWW\n"
"WW%WW...\n"
".WWW....";

const char* level_joseph = 
"WWWWWWW.\n"
"WW__PPW.\n"
"W___P_W.\n"
"WWmmP_W.\n"
".WB_P_WW\n"
".W_WPP#W\n"
".WWWWWWW\n"
"........";

//****************************************
// Level where you need to push a bomb onto a pressure plate within a green wall. Maybe. Or we change bomb rules. 
//****************************************
const char* level_quirky = 
"WWWWWWW\n"
"W_____W\n"
"W_%_B_W\n"
"W_____W\n"
"W_x_g_W\n"
"W_____W\n"
"WWWWWWW\n"
".......";
