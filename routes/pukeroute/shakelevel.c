#include "shakelevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/stagehandler.h>


#include "../standardroute/standard.h"
#include "../../stage.h"
#include "../../mirkling.h"
#include "../../mirklinghandler.h"


static char gFunnyTexts[][1024] = {
	"In case it helps you, I also got pretty seasick from making the game, we're pretty much puke-buddies.",
	"This level is dedicated to Vlambeer.",
	"Try closing your eyes to amplify the seasickness effect. It really makes things worse."
};


static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadShakeLevel() {
	setStandardWaveText("Wave 10");
	setRandomFunnyText();
	setMirklingSpeed(2, 4);
	setMirklingsGeneratedPerFrame(10);

	setStandardLevelMirklingAmount(30000);
	loadStandard();
	setMirklingSpawnY(-150);

	int i;
	for (i = 0; i < 7; i++) {
		increaseScreenShake();
	}
}

static void unloadShakeLevel() {
	resetScreenShakeLimit();
	setMirklingSpawnY(-20);
}

static void updateShake() {
	addStageHandlerScreenShake(10);
}

static void updateShakeLevel() {
	updateShake();
	updateStandard();
}


Level ShakeLevel = {

	.mLoadLevel = loadShakeLevel,
	.mUpdateLevel = updateShakeLevel,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadShakeLevel
};
