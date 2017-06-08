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

	int mDeathCountText;
	int mDeathCount;

} gData;

static void loadMirklingHandler(void* tData) {
	(void)tData;

	gData.mWalkingAnimation = createEmptyAnimation();
	gData.mWalkingAnimation.mFrameAmount = 2;
	gData.mWalkingAnimation.mDuration = 3;
	loadConsecutiveTextures(gData.mWalkingTextures, "assets/mirklings/WALKING.pkg", gData.mWalkingAnimation.mFrameAmount);

	gData.mDeathCount = 0;
	gData.mDeathCount = addHandledTextWithInfiniteDurationOnOneLine(makePosition(20, 20, 15), "Death Count: 0", 0, COLOR_YELLOW, makePosition(20, 20, 1));
}

static void updateMirklingHandler(void* tData) {
	(void)tData;

	int i;
	for (i = 0; i < 5; i++) {
		addMirkling();
	}
	
	char nText[1024];
	sprintf(nText, "Death Count: %d", gData.mDeathCount);
	setHandledText(gData.mDeathCountText, nText);
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

void increaseDeathCount()
{
	gData.mDeathCount++;
}

void resetDeathCount()
{
	gData.mDeathCount = 0;
}
