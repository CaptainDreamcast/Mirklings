#include "gamescreen.h"

#include <stdio.h>

#include <tari/actorhandler.h>
#include <tari/input.h>
#include <tari/collisionhandler.h>

#include "stage.h"
#include "mirklinghandler.h"
#include "player.h"
#include "deathcount.h"
#include "preciouspeople.h"
#include "upgrades.h"
#include "collision.h"
#include "particles.h"
#include "levelhandler.h"

static void loadGameScreen() {
	

	loadMirklingsCollisions();
	instantiateActor(StageBP);
	instantiateActor(MirklingHandlerBP);
	loadPreciousPeople();
	loadUpgrades();
	instantiateActor(DeathCountBP);
	instantiateActor(PlayerBP);
	instantiateActor(LevelHandlerBP);
	loadParticles();

	// activateCollisionHandlerDebugMode();
	// setCollisionHandlerDebuggingScreenPositionReference(getStagePositionReference());
}

static Screen* getNextGameScreenScreen() {
	if (hasPressedAbortFlank()) {
		abortScreenHandling();
	}

	if (!hasPreciousPeopleLeft()) {
		return &GameScreen;
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