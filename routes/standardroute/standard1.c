#include "standard1.h"

#include <tari/math.h>

#include "standard.h"

static char gFunnyTexts[][1024] = {
	"Welcome to Mirklings, first game to kill a man through repetitive gameplay.",
	"There will be like eight Mirklings coming, try to shoot them or not, it's not really my problem, you know.",
	"I swear there will be better levels later on, you've gotta believe me. You believe me, right?"
};


static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard1() {
	setStandardWaveText("Wave 1");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	loadStandard();
}

Level StandardLevel1 = {

	.mLoadLevel = loadStandard1,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
