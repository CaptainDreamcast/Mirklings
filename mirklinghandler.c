#include "mirklinghandler.h"

#include <stdio.h>

#include <tari/wrapper.h>
#include <tari/datastructures.h>
#include <tari/math.h>
#include <tari/file.h>
#include <tari/texthandler.h>
#include <tari/system.h>

#include "mirkling.h"

static struct {
	int mTypeAmount;
	TextureData mWalkingTextures[10][2];
	Animation mWalkingAnimation;

	TextureData mRealTextures[2];

	int mAmount;
	int mAmountOnScreen;

	int mIsGenerationPaused;

	double mMirklingsGeneratedPerFrame;
	double mMirklingSpeedMin;
	double mMirklingSpeedMax;
} gData;

static void loadSingleMirklingType(int i) {
	char path[1024];
	sprintf(path, "assets/mirklings/WALKING%d_.pkg", i);

	loadConsecutiveTextures(gData.mWalkingTextures[i], path, gData.mWalkingAnimation.mFrameAmount);
}

static void loadRealMirklingType() {
	loadConsecutiveTextures(gData.mRealTextures, "assets/mirklings/REAL_WALKING.pkg", gData.mWalkingAnimation.mFrameAmount);
}

static void loadMirklingTypes() {
	int i;
	for (i = 0; i < gData.mTypeAmount; i++) {
		loadSingleMirklingType(i);
	}

	loadRealMirklingType();
}

static void loadMirklingHandler(void* tData) {
	(void)tData;
	gData.mTypeAmount = 2;
	gData.mWalkingAnimation = createEmptyAnimation();
	gData.mWalkingAnimation.mFrameAmount = 2;
	gData.mWalkingAnimation.mDuration = 3;
	loadMirklingTypes();

	gData.mAmount = 0;
	gData.mAmountOnScreen = 0;

	gData.mIsGenerationPaused = 0;
	
	gData.mMirklingsGeneratedPerFrame = 10;
	gData.mMirklingSpeedMin = 1;
	gData.mMirklingSpeedMax = 2;

	initMirklings();
}

static void updateMirklingHandler(void* tData) {
	(void)tData;

	updateMirklings();

	if (gData.mIsGenerationPaused || isWrapperPaused()) return;

	double generatedMirklingsTotal = gData.mMirklingsGeneratedPerFrame*PERFORMANCE_FACTOR;

	int generatedMirklingsAbsolute = (int)generatedMirklingsTotal;
	double generatedMirklingsFraction = generatedMirklingsTotal - generatedMirklingsAbsolute;

	int i;
	for (i = 0; i < generatedMirklingsAbsolute; i++) {
		addMirkling(randfrom(gData.mMirklingSpeedMin, gData.mMirklingSpeedMax));
	}


	double prob = randfrom(0, 1);
	if (prob < generatedMirklingsFraction) {
		addMirkling(randfrom(gData.mMirklingSpeedMin, gData.mMirklingSpeedMax));
	}
}

ActorBlueprint MirklingHandlerBP = {
	.mLoad = loadMirklingHandler,
	.mUpdate = updateMirklingHandler
};

TextureData* getMirklingWalkingTextures()
{
	int i = randfromInteger(0, gData.mTypeAmount - 1);
	return gData.mWalkingTextures[i];
}

TextureData* getMirklingRealTextures()
{
	return gData.mRealTextures;
}

Animation getMirklingWalkingAnimation()
{
	return gData.mWalkingAnimation;
}

void resetMirklingAmount()
{
	gData.mAmount = 0;
	gData.mAmountOnScreen = 0;
}

void increaseMirklingAmount()
{
	gData.mAmount++;
	gData.mAmountOnScreen++;
}

void decreaseMirklingAmountOnScreen()
{
	gData.mAmountOnScreen--;
}

int getMirklingAmount()
{
	return gData.mAmount;
}

int getMirklingAmountOnScreen()
{
	return gData.mAmountOnScreen;
}

void pauseMirklingGeneration()
{
	gData.mIsGenerationPaused = 1;
}

void unpauseMirklingGeneration()
{
	gData.mIsGenerationPaused = 0;
}

void setMirklingSpeed(double tSpeedMin, double tSpeedMax)
{
	gData.mMirklingSpeedMin = tSpeedMin;
	gData.mMirklingSpeedMax = tSpeedMax;
}

void setMirklingsGeneratedPerFrame(double tMirklingsPerFrame)
{
	gData.mMirklingsGeneratedPerFrame = tMirklingsPerFrame;
}
