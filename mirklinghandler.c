#include "mirklinghandler.h"

#include <stdio.h>

#include <tari/datastructures.h>
#include <tari/math.h>
#include <tari/file.h>
#include <tari/texthandler.h>

#include "mirkling.h"

static struct {
	TextureData mWalkingTextures[2];
	Animation mWalkingAnimation;

	int mAmount;
	int mAmountOnScreen;

	int mIsGenerationPaused;

	double mMirklingsGeneratedPerFrame;
	double mMirklingSpeedMin;
	double mMirklingSpeedMax;
} gData;

static void loadMirklingHandler(void* tData) {
	(void)tData;

	gData.mWalkingAnimation = createEmptyAnimation();
	gData.mWalkingAnimation.mFrameAmount = 2;
	gData.mWalkingAnimation.mDuration = 3;
	loadConsecutiveTextures(gData.mWalkingTextures, "assets/mirklings/WALKING.pkg", gData.mWalkingAnimation.mFrameAmount);

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

	if (gData.mIsGenerationPaused) return;

	int i;
	for (i = 0; i < gData.mMirklingsGeneratedPerFrame; i++) {
		addMirkling(randfrom(gData.mMirklingSpeedMin, gData.mMirklingSpeedMax));
	}
	
}

ActorBlueprint MirklingHandlerBP = {
	.mLoad = loadMirklingHandler,
	.mUpdate = updateMirklingHandler
};

TextureData* getMirklingWalkingTextures()
{
	return gData.mWalkingTextures;
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
