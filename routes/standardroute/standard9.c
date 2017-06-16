#include "standard9.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"Hey, that one was okay. Don't glare at me like that. It's a learning experience for both of us.",
	"Do you enjoy those levels the most, the ones where you can blow up the defenseless masses?",
	"I told you so."
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
	setStandardWaveText("Wave 9");
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
