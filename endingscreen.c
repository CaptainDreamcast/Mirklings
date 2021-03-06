#include "endingscreen.h"

#include <stdio.h>
#include <string.h>

#include <tari/input.h>
#include <tari/animation.h>
#include <tari/texthandler.h>
#include <tari/math.h>
#include <tari/timer.h>
#include <tari/screeneffect.h>

#include "titlescreen.h"
#include "soundeffect.h"
#include "deathcount.h"
#include "baftascreen.h"


static struct {
	int mIsGoodEnding;

	TextureData mBGTexture;
	int mBG;

	int mCounterText;
	int mCounterValue;
	char mEndCounterText[100];
	int mSetAmount;

	Duration mCounterNow;
	Duration mCounterSingleDuration;

	int mIsGameFinished;
} gData;

static void updateCounterText() {
	if (handleDurationAndCheckIfOver(&gData.mCounterNow, gData.mCounterSingleDuration)) {
		gData.mSetAmount = min(gData.mSetAmount + 1, (int)strlen(gData.mEndCounterText));
		gData.mCounterNow = 0;
	}

	char newCounterText[100];
	strcpy(newCounterText, gData.mEndCounterText);

	int l = strlen(gData.mEndCounterText);
	int i;
	for (i = 0; i < l - gData.mSetAmount; i++) {
		newCounterText[i] = (char)randfromInteger('0', '9');
	}
	setHandledText(gData.mCounterText, newCounterText);
}

static void loadBadEndingScreen() {
	gData.mBGTexture = loadTexture("assets/ending/BAD_ENDING.pkg");
	gData.mBG = playAnimationLoop(makePosition(0, 0, 1), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
}

static void loadGoodEndingScreen() {
	gData.mBGTexture = loadTexture("assets/ending/GOOD_ENDING.pkg");
	gData.mBG = playAnimationLoop(makePosition(0,0,1), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
}

static void loadEndingScreen() {
	
	gData.mCounterValue = getDeathCount();
	gData.mCounterText = addHandledText(makePosition(370, 345, 2), "0", 0, COLOR_WHITE, makePosition(32, 32, 1), makePosition(-10, 0, 0), makePosition(INF, INF, INF), INF);
	sprintf(gData.mEndCounterText, "%d", gData.mCounterValue);
	gData.mSetAmount = 0;
	gData.mCounterNow = 0;
	gData.mCounterSingleDuration = 25;

	updateCounterText();

	if (gData.mIsGoodEnding) {
		loadGoodEndingScreen();
	}
	else {
		loadBadEndingScreen();
	}

	gData.mIsGameFinished = 1;
	addFadeIn(60, NULL, NULL);
}

static void updateEndingScreen() {
	updateCounterText();
}

static void goToBaftaScreen(void* tCaller) {
	(void)tCaller;

	setNewScreen(&BaftaScreen);
}

static Screen* getNextEndingScreenScreen() {
	if (hasPressedAbortFlank()) {
		return &TitleScreen;
	}

	if (hasPressedStartFlank()) {
		addFadeOut(60, goToBaftaScreen, NULL);
	}

	return NULL;
}

Screen EndingScreen = {
	.mLoad = loadEndingScreen,
	.mGetNextScreen = getNextEndingScreenScreen,
	.mUpdate = updateEndingScreen
};

void setGoodEnding() {
	gData.mIsGoodEnding = 1;
}

void setBadEnding() {
	gData.mIsGoodEnding = 0;
}

int hasPlayerFinishedGame()
{
	return gData.mIsGameFinished;
}
