#include "cprocessing.h"
#include "level1.h"
#include "game.h"

//need a method to run level select as well

void startLevel1(void) {

	CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);

}

void startGame(void) {

	CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
}
