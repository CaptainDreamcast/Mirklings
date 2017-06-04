#include "stage.h"

#include <stdio.h>

#include <tari/animation.h>
#include <tari/stagehandler.h>
#include <tari/input.h>

static struct {
	int planeID;
} gData;

static void loadStage(void* tData) {
	(void)tData;

	setStageHandlerNoDelayedLoading();
	setStageHandlerTweening();
	gData.planeID = addScrollingBackground(1, 1);
	addBackgroundElement(gData.planeID, makePosition(-100, -50, 0), "assets/stage/BG.pkg", createOneFrameAnimation());
	setStageCameraRange(makeGeoRectangle(0,0,0,480));
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
