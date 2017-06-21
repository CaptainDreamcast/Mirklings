#include "invisiblemirklingslevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>

#include "../standardroute/standard.h"
#include "../../mirkling.h"

static char gFunnyTexts[][1024] = {
	"This game is so fun, you'll puke with joy! Joy, supper, lunch... anything, really!",
	"You thought screen shake was bad? Check this out:",
	"Every day we stray further from God's light into the unfeeling abyss of darkness."
};

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadInvisibleMirklingsLevel() {
	setStandardWaveText("Round 4");
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
