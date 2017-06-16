#include "standard6.h"

#include <tari/math.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"

static char gFunnyTexts[][1024] = {
	"This is kinda the normal route where we pretend Mirklings is a proper game.",
	"Make sure to rate this game 4/5 stars so nobody thinks we're faking 5/5 star ratings, okay?",
	"I feel like this is a good time for a marketing plug, buy all your light pistols at the Retrospiel video game store in cologne. Retrospiel. Google it."
};

static char gFailText[1024] = "Your gameplay style is like a car crash in motion, we all know it's not gonna end well, but we can't avert our eyes.";

static void setRandomFunnyText() {
	if (getPreciousPeopleAmount() < 2) {
		setStandardFunnyText(gFailText);
		return;
	}

	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);
}


static void loadStandard6() {
	setStandardWaveText("Wave 6");
	setRandomFunnyText();
	setMirklingSpeed(2, 4);
	setMirklingsGeneratedPerFrame(20);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
}

Level StandardLevel6 = {

	.mLoadLevel = loadStandard6,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
