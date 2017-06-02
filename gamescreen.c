#include "gamescreen.h"

#include <stdio.h>

#include <tari/actorhandler.h>
#include <tari/input.h>

#include "stage.h"
#include "mirklinghandler.h"
#include "player.h"
#include "deathcount.h"
#include "preciouspeople.h"
#include "upgrades.h"

static void loadGameScreen() {
	instantiateActor(StageBP);
	instantiateActor(MirklingHandlerBP);
	loadPreciousPeople();
	loadUpgrades();
	instantiateActor(DeathCountBP);
	instantiateActor(PlayerBP);
}

static Screen* getNextGameScreenScreen() {
	if (hasPressedAbortFlank()) {
		abortScreenHandling();
	}
	
	return NULL;
}

Screen GameScreen = {
	.mLoad = loadGameScreen,
	.mUnload = NULL,
	.mDraw = NULL,
	.mUpdate = NULL,
	.mGetNextScreen = getNextGameScreenScreen
};