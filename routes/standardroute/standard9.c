#include "standard9.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"This is a completely boring standard level. Don't worry. Trust me.",
};

static char gFailText[1024] = "You must be sweating right now! Another joke level and you're dead!";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 2) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard9() {
	setStandardWaveText("Wave 18");
	setRandomFunnyText();
	setMirklingSpeed(0.5, 1);
	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(100000);
	loadStandard();
}

Level StandardLevel9 = {

	.mLoadLevel = loadStandard9,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
