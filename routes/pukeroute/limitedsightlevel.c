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
	TextureData mLimitedSightTexture;
	int mLimitedSight;

} gData;

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);


}


static void loadLimitedSightLevel() {
	setStandardWaveText("Round 3");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	gData.mLimitedSightTexture = loadTexture("assets/effects/LIMITEDSIGHT.pkg");
	gData.mLimitedSight = playAnimationLoop(makePosition(0, 0, 9), &gData.mLimitedSightTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mLimitedSightTexture));
	setAnimationSize(gData.mLimitedSight, makePosition(640,480,1), makePosition(0,0,0));
}

static void unloadLimitedSightLevel() {
	removeHandledAnimation(gData.mLimitedSight);
	unloadTexture(gData.mLimitedSightTexture);
}




Level LimitedSightLevel = {

	.mLoadLevel = loadLimitedSightLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadLimitedSightLevel
};
