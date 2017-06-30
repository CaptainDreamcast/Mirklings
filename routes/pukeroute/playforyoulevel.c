#include "playforyoulevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/texthandler.h>

#include "../standardroute/standard.h"
#include "../../player.h"
#include "../../mirkling.h"
#include "../../mirklinghandler.h"


static char gFunnyTexts[][1024] = {
	"You suck at this. I hereby revoke your player license."
};

static struct {
	Duration mNow;
	Duration mDuration;
	int mIsShooting;
} gData;

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}

static void startShooting(void* tCaller) {
	(void)tCaller;
	gData.mIsShooting = 1;
}

static void loadPlayForYouLevel() {
	setStandardWaveText("Wave 22");
	setRandomFunnyText();
	
	setMirklingSpeed(1, 2);
	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(15000);
	loadStandard();

	pausePlayerShooting();
	setStandardKeepPlayerShotPaused();
	gData.mNow = 0;
	gData.mDuration = 30;
	gData.mIsShooting = 0;
	setStandardStoppedShowingWaveScreenCB(startShooting, NULL);
}

static void shootAtLowestMirkling() {
	Position p = getLowestMirklingPosition();
	if (p.y == 0) {
		p = makePosition(320, 240, 0);
	}

	addPlayerShotManual(p, 200);
}

static void updatePlayForYouLevel() {
	if (gData.mIsShooting && handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		gData.mNow = 0;
		shootAtLowestMirkling();
		gData.mDuration = randfromInteger(30, 40);
	}
	updateStandard();
}

static void unloadPlayForYouLevel() {
	unpausePlayerShooting();
}




Level PlayForYouLevel = {

	.mLoadLevel = loadPlayForYouLevel,
	.mUpdateLevel = updatePlayForYouLevel,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadPlayForYouLevel
};
