#include "simulationbreakdown3.h"

#include <tari/math.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"
#include "../../stage.h"

#include "../standardroute/standard.h"

static struct {
	Duration mNow;
	Duration mDuration;

} gData;

static void setNewScreenNoise() {
	addScreenNoise(randfromInteger(20, 30));
	gData.mNow = 0;
	gData.mDuration = randfromInteger(60, 120);
	invertStageReality();
}

static void loadSimulationBreakdown3() {
	setStandardWaveText("Wave 1");
	setStandardFunnyText("Oh oh oh oh oh oh oh oh oh oh oh oh oh oh oh oh oh this is bad");
	setMirklingSpeed(1, 2);

	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	setNewScreenNoise();
}


static void updateSimulationBreakdown3() {
	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNewScreenNoise();
	}

	updateStandard();
}

Level SimulationBreakdown3 = {
	.mLoadLevel = loadSimulationBreakdown3,
	.mUpdateLevel = updateSimulationBreakdown3,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
