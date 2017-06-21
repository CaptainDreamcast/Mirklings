#include "simulationbreakdown2.h"

#include <tari/math.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"

#include "../standardroute/standard.h"

static struct {
	Duration mNow;
	Duration mDuration;

} gData;

static void setNewScreenNoise() {
	addScreenNoise(randfromInteger(7, 12));
	gData.mNow = 0;
	gData.mDuration = randfromInteger(15, 30);
}

static void loadSimulationBreakdown2() {
	setStandardWaveText("Wave wave eavesa eave");
	setStandardFunnyText("Hey, this might make for an interesting new gimmick. When life gives you lemons, you know?");
	setMirklingSpeed(3, 4);
	setMirklingsGeneratedPerFrame(20);
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	setNewScreenNoise();
}


static void updateSimulationBreakdown2() {
	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNewScreenNoise();
	}

	updateStandard();
}

Level SimulationBreakdown2 = {
	.mLoadLevel = loadSimulationBreakdown2,
	.mUpdateLevel = updateSimulationBreakdown2,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
