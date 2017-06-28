#include "invisiblemirklingslevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>

#include "../standardroute/standard.h"
#include "../../mirkling.h"

static char gFunnyTexts[][1024] = {
	"Heads up: The Mirklings in this level are invisible. No, they really are, keep bombing the air and you'll see."
};

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadInvisibleMirklingsLevel() {
	setStandardWaveText("Round 19");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	setMirklingsInvisible();
}

static void unloadInvisibleMirklingsLevel() {
	setMirklingsVisible();
}




Level InvisibleMirklingsLevel = {

	.mLoadLevel = loadInvisibleMirklingsLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadInvisibleMirklingsLevel
};
