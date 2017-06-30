#include "standard6.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"Mirklings are closely related to the pufferfish. A pufferfish's natural prey are mollusks.",
};

static char gFailText[1024] = "Your gameplay style is like a car crash in motion, we all know it's not gonna end well, but we can't avert our eyes.";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 2) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard6() {
	setStandardWaveText("Wave 6");
	setRandomFunnyText();
	setMirklingSpeed(6, 8);
	setMirklingsGeneratedPerFrame(40);
	setStandardLevelMirklingAmount(40000);
	loadStandard();
}

Level StandardLevel6 = {

	.mLoadLevel = loadStandard6,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
