#include "pukeroute.h"

#include <tari/wrapper.h>

#include "../levelhandler.h"
#include "../endingscreen.h"

#include "standardroute/trailerroute.h"
#include "standardroute/standard1.h"
#include "standardroute/standard2.h"
#include "standardroute/standard3.h"
#include "standardroute/standard4.h"
#include "standardroute/standard5.h"
#include "standardroute/standard6.h"
#include "standardroute/standard7.h"
#include "standardroute/standard8.h"
#include "standardroute/standard9.h"
#include "standardroute/standard10.h"
#include "pukeroute/rotatelevel.h"
#include "pukeroute/shakelevel.h"
#include "pukeroute/limitedsightlevel.h"
#include "pukeroute/nosightlevel.h"
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
#include "pukeroute/willkillyourparentslevel.h"
#include "pukeroute/maybekilledyourparentslevel.h"
#include "pukeroute/discotatelevel.h"

static struct {
	int mCurrentLevel;
	int mAmount;

	int mIsFinished;
	int mIsContinuing;

} gData;


static Level* gLevels[] = {
	//&TrailerRoute,
	//&StandardLevel1,
	//&StandardLevel2,
	//&StandardLevel3,
	//&StandardLevel4,
	//&StandardLevel5,
	//&StandardLevel6,
	//&LimitedSightLevel,
	//&NoSightLevel,
	//&StandardLevel7,
	//&ShakeLevel,						// 10

	//&RotateLevel,
	//&StandardLevel8,
	//&WillKillYourParentsLevel,
	//&MaybeKilledYourParentsLevel,		// 15
	//&DiscoLevel,
	//&DiscotateLevel,
	//&StandardLevel9,
	//&InvisibleMirklingsLevel,
	&StandardLevel10,					//20
	
	//&TextBlockingViewLevel,
	//&PlayForYouLevel,
	//&SimulationBreakdown1,
	//&SimulationBreakdown2,
	//&SimulationBreakdown3,
	//&SimulationBreakdown4,
	//&SimulationBreakdown5,
	//&SimulationBreakdown6,
	//&SimulationBreakdown7,
	//&SimulationBreakdown8,
	//&SimulationBreakdown9,
	//&SimulationBreakdown10,
	//&SimulationBreakdown11,
};

static void loadPukeRoute() {
	gData.mAmount = (sizeof gLevels) / sizeof(Level*);

	if (!gData.mIsContinuing) {
		gData.mCurrentLevel = 0;
	}
	gData.mIsContinuing = 0;

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

static void setPukeRouteToContinue() {
	gData.mIsContinuing = 1;
}

Route PukeRoute = {
	.mLoadRoute = loadPukeRoute,
	.mReset = resetPukeRoute,
	.mUpdate = updatePukeRoute,
	.mHasLost = hasLostPukeRoute,
	.mCanBePlayed = canPukeRouteBePlayed,
	.mSetToContinue = setPukeRouteToContinue,
};