#include "simulationbreakdown11.h"

#include <tari/math.h>
#include <tari/texthandler.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"
#include "../../stage.h"
#include "../../preciouspeople.h"
#include "../../particles.h"
#include "../../mirkling.h"
#include "../../endingscreen.h"

#include "../standardroute/standard.h"


static void lastMirklingHit(void* tCaller, void* tCollisionData) {
	(void)tCaller;
	(void)tCollisionData;
	setBadEnding();
}

static void loadSimulationBreakdown11() {
	setStandardWaveText("...");
	
	setStandardFunnyText("Time for a super-advanced karma choice, so Mirklings can say \"karma system\" on the box.");
	setMirklingSpeed(1, 4);

	setMirklingsGeneratedPerFrame(0);
	setStandardLevelMirklingAmount(1);
	loadStandard();
	int mirkling = addMirklingManual(makePosition(320, -100, 2), makePosition(0, 1, 0), 0.5);
	setMirklingRouteHitCB(mirkling, lastMirklingHit, NULL);
	setGoodEnding();
}

Level SimulationBreakdown11 = {
	.mLoadLevel = loadSimulationBreakdown11,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
