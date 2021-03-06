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
	"You'd do well to remember this previous level and learn from it."
};

static struct {
	int mTextPhysics;
	int mText;

	TextureData mBGTexture;
	int mBG;
} gData;

static char gBlockingText[] = "Mirklings is going to be incredibly popular with kids, you can just picture them running in toy stores wanting the new Mirklings plushie, shirt, or sleeping pills. Research shows that kids love squishy yellow/orange things. You thought this was a coincidence? Pikachu, minions, Spongebob... all yellow! It's a goddamn conspiracy and nobody dares to speak out. Fine, let them have it their way, but Mirklings merch will be going to the moon along with them. They'll probably make a Mirklings TV series, too! And a video game! The guy who played the Hoompa Loompas in Charlie and the Chocolate Factory will play all the Mirklings and it will be top of the charts. Finally, time for some fame.";

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
