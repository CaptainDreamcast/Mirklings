#include "simulationbreakdown6.h"

#include <tari/math.h>
#include <tari/texthandler.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"
#include "../../stage.h"
#include "../../preciouspeople.h"
#include "../../particles.h"
#include "../../mirkling.h"
#include "../../deathcount.h"

#include "../standardroute/standard.h"

static struct {
	Duration mNow;
	Duration mDuration;

	TextureData mTitleTexture;
	int mTitle;
	int mTitleText;
} gData;

static void setNewScreenNoise() {
	addScreenNoise(randfromInteger(5, 10));
	gData.mNow = 0;
	gData.mDuration = randfromInteger(30, 40);
	if(randfromInteger(0,1)) invertStageReality();
	if (randfromInteger(0, 1)) invertPreciousPeopleReality();
	if (randfromInteger(0, 1)) invertParticleReality();
	if (randfromInteger(0, 1)) invertMirklingsReality();
	if (randfromInteger(0, 1)) invertDeathCountReality();
}

static void showBreakdownTitle(void* tCaller) {
	(void)tCaller;
	gData.mTitleTexture = loadTexture("assets/title/TITLE.pkg");
	gData.mTitle = playAnimationLoop(makePosition(0,0,20), &gData.mTitleTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mTitleTexture));
	gData.mTitleText = addHandledTextWithInfiniteDurationOnOneLine(makePosition(70, 300, 21), "PRESS START AND SHOOT AT THE SCREEN", 0, COLOR_WHITE, makePosition(15, 15, 1));
	
}

static void loadSimulationBreakdown6() {
	setStandardWaveText("CONGRATULATIONS");
	
	setStandardFunnyText("YOU WON");
	setMirklingSpeed(3, 4);

	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
	setStandardFunnyTextPositionAfterLoad(makePosition(250, 240, 12));
	setNewScreenNoise();
	setStandardStoppedShowingWaveScreenCB(showBreakdownTitle, NULL);
}


static void updateSimulationBreakdown6() {
	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNewScreenNoise();
	}

	updateStandard();
}

static void unloadSimulationBreakdown6() {
	removeHandledText(gData.mTitleText);
	removeHandledAnimation(gData.mTitle);
	unloadTexture(gData.mTitleTexture);
}

Level SimulationBreakdown6 = {
	.mLoadLevel = loadSimulationBreakdown6,
	.mUpdateLevel = updateSimulationBreakdown6,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadSimulationBreakdown6,
};
