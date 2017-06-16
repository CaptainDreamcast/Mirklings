#include "standard7.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"I know what you're thinking, and yes."
};

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard7() {
	setStandardWaveText("Wave 7");
	setRandomFunnyText();
	setMirklingSpeed(4, 8);
	setMirklingsGeneratedPerFrame(40);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
}

Level StandardLevel7 = {

	.mLoadLevel = loadStandard7,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};