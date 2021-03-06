#include "gameoverscreen.h"

#include <stdio.h>

#include <tari/input.h>
#include <tari/animation.h>
#include <tari/texthandler.h>
#include <tari/math.h>
#include <tari/timer.h>
#include <tari/optionhandler.h>

#include "titlescreen.h"
#include "soundeffect.h"
#include "gamescreen.h"
#include "routehandler.h"
#include "deathcount.h"

static struct {
	TextureData mBGTexture;
	int mBG;
	int mFunnyText;
} gData;

static char gFunnyTexts[][1024] = { 
	"don't feel bad, mirklings is a hard game, y'know" ,
	"you were close, only [numerror] mirklings more",
	"everyone is dead and it's probably your fault"
};

static char gFunnyTextAmount = 3;

static void addGameOverText() {
	Position textPos = makePosition(85, 190, 2);
	
	int i = randfromInteger(0, gFunnyTextAmount - 1);
	gData.mFunnyText = addHandledTextWithBuildup(textPos, gFunnyTexts[i], 0, COLOR_WHITE, makePosition(15, 15, 1), makePosition(-5,0,0), makePosition(INF, INF, INF), INF, 10);
	setHandledTextSoundEffects(gData.mFunnyText, getTextSoundEffectCollection());
	playSoundEffect(getTextSoundEffectCollection().mSoundEffects[0]);
}

static void selectContinueOption(void* tCaller) {
	(void)tCaller;
	setCurrentRouteToContinue();
	setDeathCountToContinue();
	setNewScreen(&GameScreen);
}

static void selectTitleOption(void* tCaller) {
	(void)tCaller;
	setNewScreen(&TitleScreen);
}

static void loadGameOverScreen() {
	initGameSoundEffects();
	gData.mBGTexture = loadTexture("assets/gameover/BG.pkg");
	gData.mBG = playAnimationLoop(makePosition(0,0,1), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
	addGameOverText();
	instantiateActor(getOptionHandlerBlueprint());
	setOptionButtonA();
	setOptionButtonStart();
	setOptionTextSize(20);
	setOptionTextBreakSize(-5);
	int optionX = 80;
	addOption(makePosition(optionX, 270, 2), "Continue (not recommended)" , selectContinueOption, NULL);
	addOption(makePosition(optionX, 330, 2), "Return to title and give up", selectTitleOption, NULL);
	addOption(makePosition(optionX, 360, 2), "because life is empty and", selectTitleOption, NULL);
	addOption(makePosition(optionX, 390, 2), "winning Mirklings won't change that", selectTitleOption, NULL);
}

static Screen* getNextGameOverScreenScreen() {
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen GameOverScreen = {
	.mLoad = loadGameOverScreen,
	.mGetNextScreen = getNextGameOverScreenScreen
};
