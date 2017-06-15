#include "levelhandler.h"

#include <stdio.h>

#include <tari/texthandler.h>
#include <tari/timer.h>
#include <tari/math.h>

#include "mirklinghandler.h"
#include "player.h"
#include "soundeffect.h"


static void loadLevelHandler(void* tData) {
	(void)tData;
	
	
}




static void updateLevelHandler(void* tData) {
	(void)tData;

	
}

ActorBlueprint LevelHandlerBP = {
	.mLoad = loadLevelHandler,
	.mUpdate = updateLevelHandler
};
