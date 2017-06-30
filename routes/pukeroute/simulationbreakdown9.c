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

static void loadSimulationBreakdown9() {
	setStandardWaveText("...");
	
	setStandardFunnyText("You were controlling a drone shooting down people in Afghanistan, as you can tell by these hyperrealistic video recordings.");
	setMirklingSpeed(1, 2);

	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(5000);
	loadStandard();
}

Level SimulationBreakdown9 = {
	.mLoadLevel = loadSimulationBreakdown9,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
