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
#include <tari/system.h>

#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"
#include "../../collision.h"
#include "../../soundeffect.h"
#include "../../player.h"
#include "../../stage.h"
#include "../../particles.h"
#include "../../mirkling.h"
#include "../../noise.h"
#include "../../deathcount.h"
#include "../../pausemenu.h"


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

	int mIsKeepingPlayerShotPaused;

	void(*mStoppedShowingWaveScreenCB)(void*);
	void* mStoppedShowingWaveScreenCaller;

} gData;


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
	unpauseMirklingGeneration();
	setPauseMenuPossible();

	if (!gData.mIsKeepingPlayerShotPaused) {
		unpausePlayerShooting();
	}

	if (gData.mStoppedShowingWaveScreenCB) {
		gData.mStoppedShowingWaveScreenCB(gData.mStoppedShowingWaveScreenCaller);
	}
}

static void showFunnyText() {
	Position p = makePosition(50, 240, 12);
	Vector3D size = makePosition(20, 20, 1);
	Vector3D breakSize = makePosition(-5, 0, 0);
	Vector3D textBoxSize = makePosition(540, 300, 1);
	Duration buildSpeed = 120;

	gData.mFunnyText = addHandledTextWithBuildup(p, gData.mFunnyString, 0, COLOR_WHITE, size, breakSize, textBoxSize, INF, buildSpeed);
}

static void showWaveText() {
	double dx = strlen(gData.mWaveString) * 30;
	Position p = makePosition(320 - dx / 2, 200, 12);
	gData.mWaveText = addHandledTextWithInfiniteDurationOnOneLine(p, gData.mWaveString, 0, COLOR_WHITE, makePosition(30, 30, 1));
}

static void showNextLevelUI() {

	showWaveText();
	showFunnyText();
	setHandledTextSoundEffects(gData.mFunnyText, getTextSoundEffectCollection());
	setPauseMenuImpossible();

	gData.mBG = playAnimationLoop(makePosition(-320, -240, 11), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));
	setAnimationSize(gData.mBG, makePosition(1280, 960, 1), makePosition(0, 0, 0));
	gData.mIsShowingUI = 1;
	gData.mTimer = addTimerCB(400, showNextLevelUIOver, NULL);
}

void loadStandard()
{
	gData.mBGTexture = loadTexture("assets/text/WAVE_TEXT_BG.pkg");
	pauseGameplay();

	gData.mIsWaitingToShow = 0;
	gData.mHasWon = 0;
	gData.mStoppedShowingWaveScreenCB = NULL;
	gData.mStoppedShowingWaveScreenCaller = NULL;
	gData.mIsKeepingPlayerShotPaused = 0;
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
	int variance = (int)(0.1*tLimit);
	tLimit = randfromInteger(tLimit-variance, tLimit);

	gData.mLimit = (int)max(1, tLimit*PERFORMANCE_FACTOR);
}

int getStandardLevelMirklingAmount() {
	return gData.mLimit;
}

void setStandardFunnyTextPositionAfterLoad(Position tPos)
{
	setHandledTextPosition(gData.mFunnyText, tPos);
}

void setStandardStoppedShowingWaveScreenCB(void(*tCB)(void *), void * tCaller)
{
	gData.mStoppedShowingWaveScreenCB = tCB;
	gData.mStoppedShowingWaveScreenCaller = tCaller;
}

void setStandardKeepPlayerShotPaused()
{
	gData.mIsKeepingPlayerShotPaused = 1;
}

int getStandardGeneratedMirklingAmount()
{
	return getMirklingAmount();
}

void setGameReal() {
	addScreenNoise(randfromInteger(5, 10));
	setStageReal();
	setPreciousPeopleReal();
	setParticlesReal();
	setMirklingsReal();
	setDeathCountReal();
}

void setGameUnreal() {
	addScreenNoise(randfromInteger(5, 10));
	setStageUnreal();
	setPreciousPeopleUnreal();
	setParticlesUnreal();
	setMirklingsUnreal();
	setDeathCountUnreal();
}
