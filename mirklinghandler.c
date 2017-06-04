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

	int mAmountText;
	int mAmount;

} gData;

static void loadMirklingHandler(void* tData) {
	(void)tData;

	gData.mWalkingAnimation = createEmptyAnimation();
	gData.mWalkingAnimation.mFrameAmount = 2;
	loadConsecutiveTextures(gData.mWalkingTextures, "assets/mirklings/WALKING.pkg", gData.mWalkingAnimation.mFrameAmount);

	gData.mAmount = 0;
	gData.mAmountText = addHandledTextWithInfiniteDurationOnOneLine(makePosition(20, 20, 15), "Mirkling amount: 0", 0, COLOR_YELLOW, makePosition(20, 20, 1));
}

static void updateMirklingHandler(void* tData) {
	(void)tData;

	double x = randfrom(0, 100);
	if (x <= 99) {
		addMirkling();
	}

	char nText[1024];
	sprintf(nText, "Mirkling amount: %d", gData.mAmount);
	setHandledText(gData.mAmountText, nText);
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

void increaseMirklingAmount()
{
	gData.mAmount++;
}

void decreaseMirklingAmount()
{
	gData.mAmount--;
}
