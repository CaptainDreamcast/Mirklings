#include "standard8.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"You're almost done. There's only 10 waves per route. Probably. I can really only talk for this route here.",
	"If you still have houses left, the game up 'till this point must have been too easy.",
	"Have a little break."
};

static char gFailText[1024] = "On the upside, if you can make it through this with one house, you'll be a legend.";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 2) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard8() {
	setStandardWaveText("Wave 8");
	setRandomFunnyText();
	setMirklingSpeed(0.5, 1);
	setMirklingsGeneratedPerFrame(5);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
}

Level StandardLevel8 = {

	.mLoadLevel = loadStandard8,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};