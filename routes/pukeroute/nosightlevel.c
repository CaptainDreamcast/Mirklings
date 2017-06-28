#include "nosightlevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>

#include "../standardroute/standard.h"

static char gFunnyTexts[][1024] = {
	"Let's see how far we can push this joke."
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


static void loadNoSightLevel() {
	setStandardWaveText("Wave 8");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	gData.mLimitedSightTexture = loadTexture("assets/debug/collision_rect.pkg");
	gData.mLimitedSight = playAnimationLoop(makePosition(0, 0, 9), &gData.mLimitedSightTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mLimitedSightTexture));
	setAnimationSize(gData.mLimitedSight, makePosition(640,480,1), makePosition(0,0,0));
	setAnimationColor(gData.mLimitedSight, 0,0,0);
}

static void unloadNoSightLevel() {
	removeHandledAnimation(gData.mLimitedSight);
	unloadTexture(gData.mLimitedSightTexture);
}




Level NoSightLevel = {
	.mLoadLevel = loadNoSightLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadNoSightLevel
};
