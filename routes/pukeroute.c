#include "pukeroute.h"

#include "../levelhandler.h"

#include "pukeroute/rotatelevel.h"
#include "pukeroute/shakelevel.h"


static struct {
	int mCurrentLevel;
	int mAmount;

	int mIsFinished;
	
} gData;


static Level* gLevels[] = {
	&RotateLevel,
	&ShakeLevel
};

static void loadPukeRoute() {
	gData.mAmount = (sizeof gLevels) / sizeof(Level*);
	gData.mCurrentLevel = 0;

	gLevels[gData.mCurrentLevel]->mLoadLevel();
}

static void resetPukeRoute() {
	gData.mIsFinished = 0;
}

static void loadNextLevelInRoute() {
	if (gLevels[gData.mCurrentLevel]->mUnloadLevel) {
		gLevels[gData.mCurrentLevel]->mUnloadLevel();
	}
	gData.mCurrentLevel = (gData.mCurrentLevel + 1) % gData.mAmount;
	gLevels[gData.mCurrentLevel]->mLoadLevel();
}

static void updatePukeRoute() {
	gLevels[gData.mCurrentLevel]->mUpdateLevel();

	if (gLevels[gData.mCurrentLevel]->mHasWon()) {
		loadNextLevelInRoute();	
	}
}

static int hasLostPukeRoute() {
	return gLevels[gData.mCurrentLevel]->mHasLost();
}

static int canPukeRouteBePlayed() {
	return !gData.mIsFinished;
}

Route PukeRoute = {
	.mLoadRoute = loadPukeRoute,
	.mReset = resetPukeRoute,
	.mUpdate = updatePukeRoute,
	.mHasLost = hasLostPukeRoute,
	.mCanBePlayed = canPukeRouteBePlayed,
};