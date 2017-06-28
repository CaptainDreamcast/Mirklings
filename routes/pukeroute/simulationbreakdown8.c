#include "simulationbreakdown7.h"

#include <tari/math.h>
#include <tari/texthandler.h>

#include "../../noise.h"
#include "../../mirklinghandler.h"
#include "../../stage.h"
#include "../../preciouspeople.h"
#include "../../particles.h"
#include "../../mirkling.h"

#include "../standardroute/standard.h"

static void loadSimulationBreakdown8() {
	setStandardWaveText("...");
	
	setStandardFunnyText("You know what? I give up. There were no Mirklings.");
	setMirklingSpeed(3, 4);
	
	setMirklingsGeneratedPerFrame(3);
	setStandardLevelMirklingAmount(2000);
	loadStandard();
	setGameReal();
}

Level SimulationBreakdown8 = {
	.mLoadLevel = loadSimulationBreakdown8,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
