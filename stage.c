#include "stage.h"

#include <stdio.h>

#include <tari/animation.h>
#include <tari/stagehandler.h>
#include <tari/input.h>

static struct {
	int planeID;
	int mBGTexture;

	Vector3D mStageOffset;
} gData;



static void loadStage(void* tData) {
	(void)tData;

	gData.mStageOffset = makePosition(-300, -300, 0);

	setStageHandlerNoDelayedLoading();
	setStageHandlerTweening();
	gData.planeID = addScrollingBackground(1, 1);
	gData.mBGTexture = addBackgroundElement(gData.planeID, gData.mStageOffset, "assets/stage/BG.pkg", createOneFrameAnimation());
	setStageCameraRange(makeGeoRectangle(0,0,320,480));
}

static void updateStage(void* tData) {
	(void)tData;
	if (hasPressedDown()) {
		scrollBackgroundDown(10);
	}

	if (hasPressedUp()) {
		scrollBackgroundDown(-10);
	}
}



ActorBlueprint StageBP = {
	.mLoad = loadStage,
	.mUpdate = updateStage,
	.mUnload = NULL,
	.mIsActive = NULL
};

Position* getStagePositionReference()
{
	return getScrollingBackgroundPositionReference(gData.planeID);
}

void drawBloodOnStage(Position p, Color c)
{
	
	TextureData* tex = getBackgroundElementTextureData(gData.planeID, gData.mBGTexture);
	
	if (c == COLOR_RED) {
		c = COLOR_DARK_RED;
	}

	p = vecSub(p, gData.mStageOffset);

	drawColoredRectangleToTexture(tex[0], c, makeRectangle((int)p.x, (int)p.y, 8, 8));
}
