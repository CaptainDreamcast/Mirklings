#include "mirklinghandler.h"

#include <stdio.h>

#include <tari/datastructures.h>
#include <tari/math.h>
#include <tari/file.h>

#include "mirkling.h"

static struct {
	TextureData mWalkingTextures[2];
	Animation mWalkingAnimation;

} gData;

static void loadMirklingHandler(void* tData) {
	(void)tData;

	gData.mWalkingAnimation = createEmptyAnimation();
	gData.mWalkingAnimation.mFrameAmount = 2;
	loadConsecutiveTextures(gData.mWalkingTextures, "assets/mirklings/WALKING.pkg", gData.mWalkingAnimation.mFrameAmount);
}

static void updateMirklingHandler(void* tData) {
	(void)tData;

	double x = randfrom(0, 100);
	if (x <= 99) {
		addMirkling();
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
