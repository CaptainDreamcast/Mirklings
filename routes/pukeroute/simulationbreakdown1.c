#include "simulationbreakdown1.h"

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
	gData.mDuration = randfromInteger(15, 60);
}

static void loadSimulationBreakdown1() {
	setStandardWaveText("Wave ?309");
	setStandardFunnyText("Ah, we're having small graphics glitches. Nothing new here, you should be used to this level of quality by now.");
	setMirklingSpeed(1, 2);
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	setNewScreenNoise();
}


static void updateSimulationBreakdown1() {
	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNewScreenNoise();
	}

	updateStandard();
}

Level SimulationBreakdown1 = {
	.mLoadLevel = loadSimulationBreakdown1,
	.mUpdateLevel = updateSimulationBreakdown1,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
