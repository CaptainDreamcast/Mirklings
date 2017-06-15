#include "standard4.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"HOLY SHIT WHAT JUST HAPPENED"
};

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard4() {
	setStandardWaveText("Wave 4");
	setRandomFunnyText();
	setMirklingSpeed(5, 6);
	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(200); // TODO: 20000
	loadStandard();
}

Level StandardLevel4 = {

	.mLoadLevel = loadStandard4,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
