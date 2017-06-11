#include "levelhandler.h"

#include <stdio.h>

#include <tari/texthandler.h>
#include <tari/timer.h>
#include <tari/math.h>

#include "mirklinghandler.h"
#include "player.h"

static struct {
	int mCurrentLevel;
	int mWaveText;
	int mFunnyText;
	TextureData mBGTexture;
	int mBG;
	int mIsWaitingToShow;
} gData;

static void unpauseGameplay() {
	unpauseMirklingGeneration();
	unpausePlayerShooting();
}

static void pauseGameplay() {
	pauseMirklingGeneration();
	pausePlayerShooting();
}

static void showNextLevelOver(void* tCaller) {
	(void)tCaller;
	removeHandledText(gData.mFunnyText);
	removeHandledText(gData.mWaveText);
	removeHandledAnimation(gData.mBG);
	unpauseGameplay();
}

static int gLevelLimits[] = { 10000, 200, 300 };

static void showNextLevel() {
	int levelAmount = (sizeof gLevelLimits) / sizeof(int);
	gData.mCurrentLevel = (gData.mCurrentLevel + 1) % levelAmount;
	
	char waveText[100];
	sprintf(waveText, "Wave %d", gData.mCurrentLevel + 1);
	gData.mWaveText = addHandledTextWithInfiniteDurationOnOneLine(makePosition(200, 200, 12), waveText, 0, COLOR_WHITE,makePosition(30,30,1));	
	gData.mFunnyText = addHandledTextWithBuildup(makePosition(150, 240, 12), "Super funny text", 0, COLOR_WHITE, makePosition(20, 20, 1), makePosition(0, 0, 0), makePosition(1000, 1000, 1), INF, 7);
	
	gData.mBG = playAnimationLoop(makePosition(0,0,11),&gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
	setAnimationSize(gData.mBG, makePosition(640, 480, 1), makePosition(0,0,0));
	addTimerCB(120, showNextLevelOver, NULL);
	resetMirklingAmount();
}

static void loadLevelHandler(void* tData) {
	(void)tData;
	
	gData.mBGTexture = loadTexture("assets/text/wave_text_bg.pkg");
	pauseGameplay();

	gData.mIsWaitingToShow = 0;
	gData.mCurrentLevel = -1;
	showNextLevel();
}

static void showNextLevelCB(void* tCaller) {
	(void)tCaller;
	pausePlayerShooting();
	showNextLevel();
	gData.mIsWaitingToShow = 0;
}


static void updateLevelHandler(void* tData) {
	(void)tData;

	if (getMirklingAmount() >= gLevelLimits[gData.mCurrentLevel]) {
		pauseMirklingGeneration();
		if (!getMirklingAmountOnScreen() && !gData.mIsWaitingToShow) {
			addTimerCB(120, showNextLevelCB, NULL);
			gData.mIsWaitingToShow = 1;
		}
	}
}

ActorBlueprint LevelHandlerBP = {
	.mLoad = loadLevelHandler,
	.mUpdate = updateLevelHandler
};