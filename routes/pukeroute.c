#include "pukeroute.h"

#include "../levelhandler.h"

#include "pukeroute/rotatelevel.h"
#include "pukeroute/shakelevel.h"
#include "pukeroute/limitedsightlevel.h"
#include "pukeroute/discolevel.h"
#include "pukeroute/invisiblemirklingslevel.h"
#include "pukeroute/textblockingviewlevel.h"
#include "pukeroute/playforyoulevel.h"
#include "pukeroute/simulationbreakdown1.h"
#include "pukeroute/simulationbreakdown2.h"
#include "pukeroute/simulationbreakdown3.h"
#include "pukeroute/simulationbreakdown4.h"
#include "pukeroute/simulationbreakdown5.h"

static struct {
	int mCurrentLevel;
	int mAmount;

	int mIsFinished;
	
} gData;


static Level* gLevels[] = {
	//&RotateLevel,
	//&ShakeLevel,
	//&LimitedSightLevel,
	//&DiscoLevel,
	//&InvisibleMirklingsLevel,
	//&TextBlockingViewLevel,
	//&PlayForYouLevel,
	//&SimulationBreakdown1,
	//&SimulationBreakdown2,
	//&SimulationBreakdown3,
	//&SimulationBreakdown4,
	&SimulationBreakdown5,
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