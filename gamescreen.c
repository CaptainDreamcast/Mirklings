#include "gamescreen.h"

#include <stdio.h>

#include <tari/actorhandler.h>
#include <tari/input.h>
#include <tari/collisionhandler.h>
#include <tari/stagehandler.h>

#include "stage.h"
#include "mirklinghandler.h"
#include "player.h"
#include "deathcount.h"
#include "preciouspeople.h"
#include "upgrades.h"
#include "collision.h"
#include "particles.h"
#include "levelhandler.h"
#include "titlescreen.h"
#include "gameoverscreen.h"
#include "soundeffect.h"
#include "explosion.h"
#include "routehandler.h"
#include "noise.h"
#include "pausemenu.h"

static void loadGameScreen() {
	initGameSoundEffects();
	loadMirklingsCollisions();
	instantiateActor(StageBP);
	instantiateActor(MirklingHandlerBP);
	loadPreciousPeople();
	loadUpgrades();
	instantiateActor(DeathCountBP);
	instantiateActor(PlayerBP);
	instantiateActor(PauseMenuBP);
	loadParticles();
	loadExplosions();
	loadScreenNoise();
	startNewRoute();

	// activateCollisionHandlerDebugMode();
	// setCollisionHandlerDebuggingScreenPositionReference(getStagePositionReference());
}

static void updateGameScreen() {
	updateParticles();
	updateRouteHandler();
}

static Screen* getNextGameScreenScreen() {
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	if (!hasPreciousPeopleLeft()) {
		return &GameOverScreen;
	}

	return NULL;
}

Screen GameScreen = {
	.mLoad = loadGameScreen,
	.mUnload = NULL,
	.mDraw = NULL,
	.mUpdate = updateGameScreen,
	.mGetNextScreen = getNextGameScreenScreen
};
