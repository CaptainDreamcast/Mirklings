#include "maybekilledyourparentslevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/texthandler.h>

#include "../standardroute/standard.h"
#include "../../deathcount.h"
#include "../../mirkling.h"
#include "../../mirklinghandler.h"

static struct {
	int mStart;
	int mEnd;
	int mTarget;
} gData;

static void loadWillKillYourParentsLevel() {
	setStandardWaveText("Wave 13");
	setStandardFunnyText("I swear to God if you don't destroy all the Mirklings in this level I will kill your parents and everything you love. I'll do it, I no longer have anything to lose, don't try me.");
	setStandardLevelMirklingAmount(6000);
	setMirklingSpeed(6, 8);
	setMirklingsGeneratedPerFrame(1);
	loadStandard();

	gData.mStart = getDeathCount();
}

static void unloadWillKillYourParentsLevel() {
	gData.mEnd = getDeathCount();
	gData.mTarget = getStandardGeneratedMirklingAmount();
}

int getPlayerParentKillMissedMirklingAmount() {
	return gData.mTarget - (gData.mEnd - gData.mStart);
}

Level WillKillYourParentsLevel = {

	.mLoadLevel = loadWillKillYourParentsLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadWillKillYourParentsLevel,
};
