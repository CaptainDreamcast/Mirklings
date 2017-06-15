#include "standardroute.h"

#include "../levelhandler.h"

#include "standardroute/standard1.h"
#include "standardroute/standard2.h"
#include "standardroute/standard3.h"
#include "standardroute/standard4.h"
#include "standardroute/standard5.h"


static struct {
	int mCurrentLevel;
	int mAmount;

	int mIsFinished;
	
} gData;

static Level* gLevels[] = {
	&StandardLevel1,
	&StandardLevel2,
	&StandardLevel3,
	&StandardLevel4,
	&StandardLevel5,
};

static void loadStandardRoute() {
	gData.mAmount = (sizeof gLevels) / sizeof(Level*);
	gData.mCurrentLevel = 0;

	gLevels[gData.mCurrentLevel]->mLoadLevel();
}

static void resetStandardRoute() {
	gData.mIsFinished = 0;
}

static void loadNextLevelInRoute() {
	gData.mCurrentLevel = (gData.mCurrentLevel + 1) % gData.mAmount;
	gLevels[gData.mCurrentLevel]->mLoadLevel();
}

static void updateStandardRoute() {
	gLevels[gData.mCurrentLevel]->mUpdateLevel();

	if (gLevels[gData.mCurrentLevel]->mHasWon()) {
		loadNextLevelInRoute();	
	}
}

static int hasLostStandardRoute() {
	return gLevels[gData.mCurrentLevel]->mHasLost();
}

static int canStandardRouteBePlayed() {
	return !gData.mIsFinished;
}

Route StandardRoute = {
	.mLoadRoute = loadStandardRoute,
	.mReset = resetStandardRoute,
	.mUpdate = updateStandardRoute,
	.mHasLost = hasLostStandardRoute,
	.mCanBePlayed = canStandardRouteBePlayed,
};