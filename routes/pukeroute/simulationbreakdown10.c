#include "simulationbreakdown10.h"

#include <tari/math.h>
#include <tari/texthandler.h>

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

static void loadSimulationBreakdown10() {
	setStandardWaveText("...");
	
	setStandardFunnyText("Sorry, but I really want my BAFTA, and making your players kill real people is the easiest way.");
	setMirklingSpeed(1, 4);

	setMirklingsGeneratedPerFrame(5);
	setStandardLevelMirklingAmount(5000);
	loadStandard();
}

Level SimulationBreakdown10 = {
	.mLoadLevel = loadSimulationBreakdown10,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
