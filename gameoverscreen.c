#include "gameoverscreen.h"

#include <stdio.h>

#include <tari/input.h>
#include <tari/animation.h>
#include <tari/texthandler.h>
#include <tari/math.h>
#include <tari/timer.h>

#include "titlescreen.h"
#include "soundeffect.h"

static struct {
	TextureData mBGTexture;
	int mBG;
	int mFunnyText;
} gData;

char gFunnyText[] = "how did you even manage to die i mean wtf dude";

static void forceToTitle(void* tCaller) {
	(void)tCaller;
	
	setNewScreen(&TitleScreen);
}

static void addGameOverText() {
	Position textPos = makePosition(85, 278, 2);
	gData.mFunnyText = addHandledTextWithBuildup(textPos, gFunnyText, 0, COLOR_WHITE, makePosition(15, 15, 1), makePosition(-5,0,0), makePosition(INF, INF, INF), INF, 10);
	setHandledTextSoundEffects(gData.mFunnyText, getTextSoundEffectCollection());
	playSoundEffect(getTextSoundEffectCollection().mSoundEffects[0]);
}

static void loadGameOverScreen() {
	initGameSoundEffects();
	gData.mBGTexture = loadTexture("assets/gameover/BG.pkg");
	gData.mBG = playAnimationLoop(makePosition(0,0,1), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
	addGameOverText();
	addTimerCB(200, forceToTitle, NULL);
}

static Screen* getNextGameOverScreenScreen() {
	if (hasPressedAbortFlank() || hasPressedStartFlank()) {
		return &TitleScreen;
	}

	return NULL;
}

Screen GameOverScreen = {
	.mLoad = loadGameOverScreen,
	.mGetNextScreen = getNextGameOverScreenScreen
};
