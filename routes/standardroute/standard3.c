#include "standard3.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"Mirklings are very shy. Scholars suggest it may be because they are prone to being blown to bits.",
};

static char gFailText[1024] = "I- it's okay, you can still do it. Sure. You can do it. Believe in me. You can do it. Stop looking at me like that.";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 4) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard3() {
	setStandardWaveText("Wave 3");
	setRandomFunnyText();
	setMirklingSpeed(100, 200);
	setMirklingsGeneratedPerFrame(1000);
	setStandardLevelMirklingAmount(1000);
	loadStandard();
}

Level StandardLevel3 = {

	.mLoadLevel = loadStandard3,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
