#include "limitedsightlevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>

#include "../standardroute/standard.h"

static char gFunnyTexts[][1024] = {
	"This game is so fun, you'll puke with joy! Joy, supper, lunch... anything, really!",
	"You thought screen shake was bad? Check this out:",
	"Every day we stray further from God's light into the unfeeling abyss of darkness."
};

static struct {
	Duration mNow;
	Duration mDuration;
	int mCurrentTint;
} gData;

#define SCREEN_TINT_AMOUNT 4

static double gScreenTints[SCREEN_TINT_AMOUNT][3] = {
	{0.5,0.5,1},
	{1, 0.5,0.5},
	{0.5,1,0.5},
	{1, 0.5, 1},
};



static void setNextScreenTint() {
	int i = gData.mCurrentTint;
	while (i == gData.mCurrentTint) {
		i = randfromInteger(0, SCREEN_TINT_AMOUNT - 1);
	}
	gData.mCurrentTint = i;
}

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadDiscoLevel() {
	setStandardWaveText("Round 3");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	gData.mNow = 0;
	gData.mDuration = 20;
	setNextScreenTint();
}

static void updateDiscoLevel() {

	if (handleDurationAndCheckIfOver(&gData.mNow, gData.mDuration)) {
		setNextScreenTint();
		gData.mNow = 0;
	}

	setAnimationHandlerScreenTint(gScreenTints[gData.mCurrentTint][0], gScreenTints[gData.mCurrentTint][1], gScreenTints[gData.mCurrentTint][2]);

	updateStandard();
}

static void unloadDiscoLevel() {
	resetAnimationHandlerScreenTint();
}




Level DiscoLevel = {

	.mLoadLevel = loadDiscoLevel,
	.mUpdateLevel = updateDiscoLevel,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadDiscoLevel
};
