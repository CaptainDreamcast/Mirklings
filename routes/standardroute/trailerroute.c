#include "trailerroute.h"

#include <tari/math.h>

#include "standard.h"

static char gFunnyTexts[][1024] = {
	"Yeah, you hated La Morte di un Cane's trailer, so I'll do the opposite with Mirklings. Pure Gameplay. Suffer.",
};


static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}

static void loadTrailerRoute() {
	setStandardWaveText("Super trailer wave");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000000);
	loadStandard();
}

Level TrailerRoute = {

	.mLoadLevel = loadTrailerRoute,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
