#include "standard2.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"

static char gFunnyTexts[][1024] = {
	"Yeah sorry that was a little long I don't know what went wrong here, let me try again.",
	"Boom boom boom, that was fun, eh? You won't close the game anytime soon, right? BY GOD PLEASE DON'T LEAVE",
	"They're squishy, they explode. It's a simple Mirklings life. We should envy them and their sweet release of death.",
};

static char gFailText[] = "Look dude, I know \"everybody plays differently\" and shit, but how did you lose a damn house this soon?";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 5) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard2() {
	setStandardWaveText("Wave 2");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(10);
	loadStandard();
}

Level StandardLevel2 = {

	.mLoadLevel = loadStandard2,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
