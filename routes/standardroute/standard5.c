#include "standard5.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"The cramp in your hand means you're alive.",
};

static char gFailText[1024] = "Don't worry about the broken houses my dude, next levels are gonna be chill. No, really. Then again, maybe not, I don't know man, I'm working on Wave 5 now how should I know.";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 3) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard5() {
	setStandardWaveText("Wave 5");
	setRandomFunnyText();
	setMirklingSpeed(1, 2);
	setMirklingsGeneratedPerFrame(10);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
}

Level StandardLevel5 = {

	.mLoadLevel = loadStandard5,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
