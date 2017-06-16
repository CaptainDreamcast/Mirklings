#include "standard.h"

#include <stdio.h>
#include <string.h>

#include <tari/animation.h>
#include <tari/math.h>
#include <tari/collisionhandler.h>
#include <tari/texthandler.h>
#include <tari/timer.h>
#include <tari/soundeffect.h>
#include <tari/input.h>

#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"
#include "../../collision.h"
#include "../../soundeffect.h"
#include "../../player.h"

static struct {
	char mWaveString[1024];
	int mWaveText;
	char mFunnyString[1024];
	int mFunnyText;
	TextureData mBGTexture;
	int mBG;
	int mIsWaitingToShow;
	int mHasWon;
	int mIsShowingUI;
	int mTimer;

	int mLimit;
} gData;

static void unpauseGameplay() {
	unpauseMirklingGeneration();
	unpausePlayerShooting();
}

static void pauseGameplay() {
	pauseMirklingGeneration();
	pausePlayerShooting();
}

static void showNextLevelUIOver(void* tCaller) {
	(void)tCaller;
	removeHandledText(gData.mFunnyText);
	removeHandledText(gData.mWaveText);
	removeHandledAnimation(gData.mBG);
	unloadTexture(gData.mBGTexture);
	gData.mIsShowingUI = 0;
	unpauseGameplay();

}

static void showFunnyText() {
	Position p = makePosition(50, 240, 12);
	Vector3D size = makePosition(20, 20, 1);
	Vector3D breakSize = makePosition(-5, 0, 0);
	Vector3D textBoxSize = makePosition(540, 300, 1);
	Duration buildSpeed = 120;

	gData.mFunnyText = addHandledTextWithBuildup(p, gData.mFunnyString, 0, COLOR_WHITE, size, breakSize, textBoxSize, INF, buildSpeed);

}

static void showNextLevelUI() {

	gData.mWaveText = addHandledTextWithInfiniteDurationOnOneLine(makePosition(200, 200, 12), gData.mWaveString, 0, COLOR_WHITE, makePosition(30, 30, 1));
	showFunnyText();
	setHandledTextSoundEffects(gData.mFunnyText, getTextSoundEffectCollection());

	gData.mBG = playAnimationLoop(makePosition(-320, -240, 11), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
	setAnimationSize(gData.mBG, makePosition(1280, 960, 1), makePosition(0, 0, 0));
	gData.mIsShowingUI = 1;
	gData.mTimer = addTimerCB(200, showNextLevelUIOver, NULL);
}

void loadStandard()
{
	gData.mBGTexture = loadTexture("assets/text/WAVE_TEXT_BG.pkg");
	pauseGameplay();

	gData.mIsWaitingToShow = 0;
	gData.mHasWon = 0;
	showNextLevelUI();
	resetMirklingAmount();
}

static void showNextLevelCB(void* tCaller) {
	(void)tCaller;
	pausePlayerShooting();
	gData.mHasWon = 1;
}

void updateStandard()
{
	if (getMirklingAmount() >= gData.mLimit) {
		pauseMirklingGeneration();
		if (!getMirklingAmountOnScreen() && !gData.mIsWaitingToShow) {
			addTimerCB(120, showNextLevelCB, NULL);
			gData.mIsWaitingToShow = 1;
		}
	}

	if (gData.mIsShowingUI && hasPressedStartFlank()) {
		removeTimer(gData.mTimer);
		showNextLevelUIOver(NULL);
	}
}

int hasLostStandard()
{
	return !hasPreciousPeopleLeft();
}

int hasWonStandard()
{
	return gData.mHasWon;
}

void setStandardWaveText(char * tText)
{
	strcpy(gData.mWaveString, tText);
}

void setStandardFunnyText(char * tText)
{
	strcpy(gData.mFunnyString, tText);
}

void setStandardLevelMirklingAmount(int tLimit)
{
	gData.mLimit = tLimit;
}

void setStandardFunnyTextPositionAfterLoad(Position tPos)
{
	setHandledTextPosition(gData.mFunnyText, tPos);
}
