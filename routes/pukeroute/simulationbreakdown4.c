#include "simulationbreakdown3.h"

#include <tari/math.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"
#include "../../stage.h"
#include "../../preciouspeople.h"
#include "../../particles.h"
#include "../../deathcount.h"

#include "../standardroute/standard.h"

static struct {
	Duration mNow;
	Duration mDuration;

} gData;

static void setNewScreenNoise() {
	addScreenNoise(randfromInteger(5, 10));
	gData.mNow = 0;
	gData.mDuration = randfromInteger(30, 40);
	invertStageReality();
	invertPreciousPeopleReality();
	invertParticleReality();
	invertDeathCountReality();
}

static void loadSimulationBreakdown4() {
	setStandardWaveText("34°10'9.51\"N 73°14'32.78\"E");
	setStandardFunnyText("Going further may not be the best idea. You can tell the game's soon going to start hammering its super-deep leason.");
	setMirklingSpeed(1, 2);

	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
	setNewScreenNoise();
}


static void updateSimulationBreakdown4() {
	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNewScreenNoise();
	}

	updateStandard();
}

Level SimulationBreakdown4 = {
	.mLoadLevel = loadSimulationBreakdown4,
	.mUpdateLevel = updateSimulationBreakdown4,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
