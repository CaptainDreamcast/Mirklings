#include "pukeroute.h"

#include <tari/wrapper.h>

#include "../levelhandler.h"
#include "../endingscreen.h"

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
#include "pukeroute/simulationbreakdown6.h"
#include "pukeroute/simulationbreakdown7.h"
#include "pukeroute/simulationbreakdown8.h"
#include "pukeroute/simulationbreakdown9.h"
#include "pukeroute/simulationbreakdown10.h"
#include "pukeroute/simulationbreakdown11.h"

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
	&PlayForYouLevel,
	//&SimulationBreakdown1,
	//&SimulationBreakdown2,
	//&SimulationBreakdown3,
	//&SimulationBreakdown4,
	//&SimulationBreakdown5,
	//&SimulationBreakdown6,
	//&SimulationBreakdown7,
	&SimulationBreakdown8,
	&SimulationBreakdown9,
	&SimulationBreakdown10,
	&SimulationBreakdown11,
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
	gData.mCurrentLevel++;

	if (gData.mCurrentLevel >= gData.mAmount) {
		setNewScreen(&EndingScreen);
		return;
	}

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