
const char* level_test = 
"....................\n"
".____...............\n"
"._F__...............\n"
".____...............\n"
"....................\n"
"........WWWWWW......\n"
"..W____.W_____......\n"
"..W____.W_____......\n"
"..WWWWW.W__.__......\n"
"........W_____......\n"
"........W_____......\n"
"....................\n"
"..........W.W.......\n"
"..........._........\n"
"..........W.W.......\n"
"....................";

const char* level_island = 
".......................\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WP_____PR____P____RPW.\n"
".WP_F___PR____P____RPW.\n"
".WP___r_PR_W__P__#_RPW.\n"
".WP_m___PR____P____RPW.\n"
".WP_____PR____P____RPW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".......................";

const char* level_island2 = 
".......................\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WP_____PR____P_____PW.\n"
".WP_F___PR____P_____PW.\n"
".WP___r_PR_W__P__#__PW.\n"
".WP_m___PR____P_____PW.\n"
".WP_____PR____P_____PW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".......................";

const char* level_island3 = 
".......................\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WP_____PR____P_____PW.\n"
".WP_F___PR____P_____PW.\n"
".WP___r_PR____P__#__PW.\n"
".WP_m___PR____P_____PW.\n"
".WP_____PR____P_____PW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".......................";

const char* level_island4 = 
".......................\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WP_____PR____P_____PW.\n"
".WP_F___PR____P_____PW.\n"
".WP_r___PR_m__P__#__PW.\n"
".WP_m___PR____P_____PW.\n"
".WP_____PR____P_____PW.\n"
".WPPPPPPPPPPPPPPPPPPPW.\n"
".WWWWWWWWWWWWWWWWWWWWW.\n"
".......................";

const char* level_island5 = 
"..................\n"
"........WWWWWWWWW.\n"
"........WPPPPPPPW.\n"
"........WP____RPW.\n"
".WWWWWWWWP____RPW.\n"
".WPPPPPPPP____RPW.\n"
".WP_____PP____RPW.\n"
".WP_F___PP____RPW.\n"
".WP__r__PPPPPPPPW.\n"
".WP_m___PPR____PW.\n"
".WP_____PPR____PW.\n"
".WPPPPPPPPR_%__PW.\n"
".WWWWWWWWPR____PW.\n"
"........WPR____PW.\n"
"........WPPPPPPPW.\n"
"........WWWWWWWWW.\n"
"..................";

const char* level_first = 
"...........\n"
".WWWWWWWWW.\n"
".W_______W.\n"
".W_______W.\n"
".W_F___#_W.\n"
".W_______W.\n"
".W_______W.\n"
".WWWWWWWWW.\n"
"...........";

const char* level_gap = 
"...........\n"
".WWWWWWWWW.\n"
".W___P___W.\n"
".W___P___W.\n"
".W_F_P_#_W.\n"
".W___P___W.\n"
".W___P___W.\n"
".WWWWWWWWW.\n"
"...........";

const char* level_gaps = 
".............\n"
"....WWWWWWWW.\n"
"....W__P___W.\n"
"....W_FP___W.\n"
"....W__P___W.\n"
"....WWWWPPPW.\n"
".WWWWWWWPPPW.\n"
".W___PPP___W.\n"
".W___PPP___W.\n"
".W___PPP___W.\n"
".WPPPWWWWWWW.\n"
".WPPPW.......\n"
".W_#_W.......\n"
".WWWWW.......\n"
".............";

const char* level_plate = 
"...........\n"
".WWWWWWWWW.\n"
".W___W___W.\n"
".W_F_R___W.\n"
".W___R_#_W.\n"
".W_r_R___W.\n"
".W___W___W.\n"
".WWWWWWWWW.\n"
"...........";

const char* level_plate2 = 
"............\n"
".WWWWWWWWWW.\n"
".W____W___W.\n"
".W_FrrR_#_W.\n"
".W____W___W.\n"
".WWWWWWWWWW.\n"
"............";

const char* level_plate3 = 
".............\n"
".WWWWWWWWWWW.\n"
".W____W___PW.\n"
".W_F_rR_#_PW.\n"
".W____W___PW.\n"
".WWWWWWWWWWW.\n"
".............";



const char* level_box = 
".........\n"
".WWWWWWW.\n"
".W_____W.\n"
".W_F_%_W.\n"
".W__m__W.\n"
".W_r_r_W.\n"
".W_____W.\n"
".WWWWWWW.\n"
".........";

const char* level_box2 = 
"...........\n"
".WWWWWWWWW.\n"
".W___P___W.\n"
".W_F_P___W.\n"
".W___P___W.\n"
".W_r_P_%_W.\n"
".W___P___W.\n"
".W___P_m_W.\n"
".W___P___W.\n"
".WWWWWWWWW.\n"
"...........";

const char* level_box3 = 
".............\n"
".WWWWWWWWWWW.\n"
".W___PPP___W.\n"
".W_F_PPP___W.\n"
".W___PPP___W.\n"
".Wr__PPP_%_W.\n"
".W___PPP___W.\n"
".W___PPP_m_W.\n"
".W___PPP___W.\n"
".WWWWWWWWWWW.\n"
".............";

const char* level_box4 = 
".............\n"
".WWWWWWWWWWW.\n"
".W___PPP___W.\n"
".W_F_PPP_m_W.\n"
".W___PPP___W.\n"
".W_r_PPP_%_W.\n"
".W___PPP___W.\n"
".W___PPP_m_W.\n"
".W___PPP___W.\n"
".WWWWWWWWWWW.\n"
".............";


const char* level_stuck = 
".........\n"
"..WWWWW..\n"
"..W___W..\n"
"..W_%_W..\n"
".WW___WW.\n"
".W__F__W.\n"
".W_r_r_W.\n"
".W__m__W.\n"
".WWW_WWW.\n"
"...WWW...\n"
".........";

const char* level_stuck2 = 
".........\n"
"...WWW...\n"
"..WW%WW..\n"
".WW___WW.\n"
".W__F__W.\n"
".W_r_r_W.\n"
".W__m__W.\n"
".WWW_WWW.\n"
"...WWW...\n"
".........";

const char* level_zigzag = 
"........\n"
".WWWWW..\n"
".W___W..\n"
".W_F_W..\n"
".W_m_W..\n"
".WWW_W..\n"
".W%__WW.\n"
".WWWrrW.\n"
"...WWWW.\n"
"........";

const char* level_zigzag2 = 
".......\n"
".WWWWW.\n"
".W___W.\n"
".W_F_W.\n"
".W_m_W.\n"
".WWWrW.\n"
".W%_rW.\n"
".WWWWW.\n"
".......";

const char* level_good = 
"...........\n"
"..WWW.WWW..\n"
"..W%WWW_W..\n"
"..W_r___W..\n"
".WWW__P_WW.\n"
".WrP_F___W.\n"
".W_m____WW.\n"
".WWWWW_WW..\n"
".....WWW...\n"
"...........";

const char* level_halved = 
"..........\n"
"...WWWWWW.\n"
"...W__W#W.\n"
".WWWm__PW.\n"
".W__PF_PW.\n"
".W___rRWW.\n"
".WW__WWW..\n"
"..WWWW....\n"
"..........";

const char* level_multi = 
"...............\n"
".WWWWWWWWWWWWW.\n"
".W__W__WWW___W.\n"
".W__R__BPR___W.\n"
".WFrRmbBPR_#_W.\n"
".W__R__BPR___W.\n"
".W__W__WWW___W.\n"
".WWWWWWWWWWWWW.\n"
"...............";

const char* level_bridge = 
".........\n"
"..WWW....\n"
".WWPW....\n"
".W#PWWWW.\n"
".WWPPm_W.\n"
".WW_WWRW.\n"
".W_F_r_W.\n"
".W_m_WWW.\n"
".W___WWW.\n"
".WWWWW...\n"
".........";


const char* level_unlock = 
".............\n"
"........WWWW.\n"
".WWWWWWWW_%W.\n"
".WrWP__P__WW.\n"
".WBb__P_imW..\n"
".WWWm__I__W..\n"
"...WF_WWWWW..\n"
"...WWWW......\n"
".............";

const char* level_unlock_x = 
".............\n"
"........WWWW.\n"
".WWWWWWWW_%W.\n"
".WrWP_P___WW.\n"
".WBb__P__m_W.\n"
".WWWm_P____W.\n"
"...WF_WWWWWW.\n"
"...WWWW......\n"
".............";

const char* level_unlock_xx = 
".........\n"
".WWWWWWW.\n"
".WrWW__W.\n"
".WBb___W.\n"
".WWWm_WW.\n"
"..W%F_W..\n"
"..WWWWW..\n"
".........";

const char* level_unlock_variant = 
".............\n"
".WWWWWWWWWW..\n"
".WrW__W___WW.\n"
".WBb__P_m_%W.\n"
".WWWm_W___WW.\n"
"...WF_WWWWW..\n"
"...WWWW......\n"
".............";

const char* level_unlock2 = 
".........\n"
".WWWWWWW.\n"
".W_F__rW.\n"
".W_m_WRW.\n"
".W___WbW.\n"
".WWWWWBW.\n"
".....W%W.\n"
".....WWW.\n"
".........";

const char* level_block_free = 
"..........\n"
".WWWW.....\n"
".W__WWWWW.\n"
".W_mFBPrW.\n"
".W_BbWWWW.\n"
".WW%WW....\n"
"..WWW.....\n"
"..........";

const char* level_quirky = 
".........\n"
".WWWWWWW.\n"
".W_____W.\n"
".W_%_F_W.\n"
".W_____W.\n"
".W_x_b_W.\n"
".W_____W.\n"
".WWWWWWW.\n"
".........";
