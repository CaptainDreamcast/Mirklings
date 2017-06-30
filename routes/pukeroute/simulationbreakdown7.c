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

static void loadSimulationBreakdown7() {
	setStandardWaveText("Wave 46");
	
	setStandardFunnyText("Mirklings will proceed as originally scheduled now. Just blast away, carefully.");
	setMirklingSpeed(3, 4);

	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(8000);
	loadStandard();
	setGameUnreal();
}

Level SimulationBreakdown7 = {
	.mLoadLevel = loadSimulationBreakdown7,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
