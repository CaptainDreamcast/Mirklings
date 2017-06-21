#include "simulationbreakdown5.h"

#include <tari/math.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"
#include "../../stage.h"
#include "../../preciouspeople.h"
#include "../../particles.h"
#include "../../mirkling.h"

#include "../standardroute/standard.h"

static struct {
	Duration mNow;
	Duration mDuration;

} gData;

static void setNewScreenNoise() {
	addScreenNoise(randfromInteger(5, 10));
	gData.mNow = 0;
	gData.mDuration = randfromInteger(30, 40);
	if(randfromInteger(0,1)) invertStageReality();
	if (randfromInteger(0, 1)) invertPreciousPeopleReality();
	if (randfromInteger(0, 1)) invertParticleReality();
	if (randfromInteger(0, 1)) invertMirklingsReality();
}

static void loadSimulationBreakdown5() {
	setStandardWaveText("Welcome Massacre");
	
	setStandardFunnyText("I warned you.");
	setMirklingSpeed(3, 4);

	setMirklingsGeneratedPerFrame(1);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
	setStandardFunnyTextPositionAfterLoad(makePosition(200, 240, 12));
	setNewScreenNoise();
}


static void updateSimulationBreakdown5() {
	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNewScreenNoise();
	}

	updateStandard();
}

Level SimulationBreakdown5 = {
	.mLoadLevel = loadSimulationBreakdown5,
	.mUpdateLevel = updateSimulationBreakdown5,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
