#include "limitedsightlevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/texthandler.h>

#include "../standardroute/standard.h"

static char gFunnyTexts[][1024] = {
	"This game is so fun, you'll puke with joy! Joy, supper, lunch... anything, really!",
	"You thought screen shake was bad? Check this out:",
	"Every day we stray further from God's light into the unfeeling abyss of darkness."
};

static struct {
	int mTextPhysics;
	int mText;
} gData;

static char gBlockingText[] = "fefefwefwwe ewfw fwf wf ewffffff ffffffff few fwewwwwwwwww wwwwwwwwwwww eeeeeeeeeeeee eeeeeeeeeeeee eeeeeeeee eeeeeeeee eeeeeeee eeeeeeeee eeeeeee eeeeee eeeeeeeeeee eeeeeeeee eeeeeeeee eeeeeeeee eeeeeeee eeeeeeee eeeeeeeeeeee eeeeeeeeeeeeeeeeeee eeeeeeeeeeeeeeeeee eeeeeeeeeeeeeeeeee eeeeeeeeeeeeeeeeeeeee eeeeeeeeeeeeeee eeeeeeeeeeeeeeeeeeeeeee eeeeeeeeeeeeeeeeeeeeeeeeeeee";


static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}

static void loadBlockingText(void* tCaller) {
	(void) tCaller;
	gData.mTextPhysics = addToPhysicsHandler(makePosition(20, 20, 9));
	addAccelerationToHandledPhysics(gData.mTextPhysics, makePosition(0, -0.1, 0));

	Vector3D size = makePosition(40, 40, 1);
	Vector3D breakSize = makePosition(0, 0, 0);
	gData.mText = addHandledText(makePosition(0,0,0), gBlockingText, 0, COLOR_WHITE, size, breakSize, makePosition(620, INF, INF), INF);
	setHandledTextBasePositionReference(gData.mText, getHandledPhysicsPositionReference(gData.mTextPhysics));
}

static void loadTextBlockingViewLevel() {
	setStandardWaveText("Round 5");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	loadStandard();
	setStandardStoppedShowingWaveScreenCB(loadBlockingText, NULL);
}

static void unloadTextBlockingViewLevel() {
	removeHandledText(gData.mText);
	removeFromPhysicsHandler(gData.mTextPhysics);
}




Level TextBlockingViewLevel = {

	.mLoadLevel = loadTextBlockingViewLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadTextBlockingViewLevel
};
