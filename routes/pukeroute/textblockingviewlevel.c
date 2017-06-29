#include "limitedsightlevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/texthandler.h>

#include "../standardroute/standard.h"
#include "../../mirkling.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"Interesting choice. Can't say I agree with it, though. Anyway, you'd do well to remember this."
};

static struct {
	int mTextPhysics;
	int mText;

	TextureData mBGTexture;
	int mBG;
} gData;

static char gBlockingText[] = "Finally I can talk as much as I want without restrictions. You see, Mirklings is a very special game. A game called Mirklings took last place in the Imagine Cup 2014. Although that was a different Mirkllings. All in all, fuck Microsoft. Then again, the year after said, we got an Xbox One. Problem with that is that it's always installing updates. Lie, you want to play a new game? Screw you, mandatory 4GB update. Won't happen with Mirkllings, I promise. Anyway, back to the whole \"Second Mirklings\" thing. I traced the logo from the original one's design. Problem is: I didn't design that one. So whatever you do, don't tell the original designer, ok?";

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}

static void loadBlockingText(void* tCaller) {
	(void) tCaller;
	gData.mTextPhysics = addToPhysicsHandler(makePosition(20, 650, 9));
	addAccelerationToHandledPhysics(gData.mTextPhysics, makePosition(0, -1, 0));

	Vector3D size = makePosition(40, 40, 1);
	Vector3D breakSize = makePosition(-10, 0, 0);
	gData.mText = addHandledText(makePosition(0,0,0), gBlockingText, 0, COLOR_WHITE, size, breakSize, makePosition(600, INF, INF), INF);
	setHandledTextBasePositionReference(gData.mText, getHandledPhysicsPositionReference(gData.mTextPhysics));
	gData.mBGTexture = loadTexture("assets/debug/collision_rect.pkg");
	gData.mBG = playOneFrameAnimationLoop(makePosition(-200,-200,8), &gData.mBGTexture);
	setAnimationSize(gData.mBG, makePosition(1100, 800, 0), makePosition(0, 0, 0));
	setAnimationColorType(gData.mBG, COLOR_BLACK);
	setAnimationTransparency(gData.mBG, 0.3);
}

static void loadTextBlockingViewLevel() {
	setStandardWaveText("Wave 21");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(30000);
	setMirklingSpeed(4, 8);
	setMirklingsGeneratedPerFrame(20);
	loadStandard();
	setStandardStoppedShowingWaveScreenCB(loadBlockingText, NULL);
}

static void unloadTextBlockingViewLevel() {
	removeHandledText(gData.mText);
	removeFromPhysicsHandler(gData.mTextPhysics);
	removeHandledAnimation(gData.mBG);
	unloadTexture(gData.mBGTexture);
}




Level TextBlockingViewLevel = {

	.mLoadLevel = loadTextBlockingViewLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadTextBlockingViewLevel
};
