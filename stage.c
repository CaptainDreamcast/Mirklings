#include "stage.h"

#include <stdio.h>

#include <tari/animation.h>
#include <tari/stagehandler.h>
#include <tari/input.h>

#include "preciouspeople.h"

static struct {
	int planeID;
	int realPlaneID;
	int mBGTexture;
	int mRealTexture;
	double mShakeMaximum;

	Vector3D mStageOffset;

	int mIsReal;
} gData;


void increaseScreenShake() {
	gData.mShakeMaximum += 10;
	setStageHandlerMaximumScreenShake(gData.mShakeMaximum);
}

void resetScreenShakeLimit()
{
	gData.mShakeMaximum = getPreciousPeopleAmount()*10;
}


static void loadStage(void* tData) {
	(void)tData;

	gData.mStageOffset = makePosition(-300, -300, 0);

	setStageHandlerNoDelayedLoading();
	setStageHandlerTweening();
	gData.planeID = addScrollingBackground(1, 1);
	gData.realPlaneID = addScrollingBackground(1, 1);
	gData.mBGTexture = addBackgroundElement(gData.planeID, gData.mStageOffset, "assets/stage/BG.pkg", createOneFrameAnimation());
	gData.mRealTexture = addBackgroundElement(gData.realPlaneID, gData.mStageOffset, "assets/stage/REAL.pkg", createOneFrameAnimation());
	setScrollingBackgroundInvisible(gData.realPlaneID);

	setStageCameraRange(makeGeoRectangle(0,0,320,1080));
	gData.mShakeMaximum = 0;
	increaseScreenShake();
	gData.mIsReal = 0;
}

static void setStageReal() {
	setScrollingBackgroundVisible(gData.realPlaneID);
	setScrollingBackgroundInvisible(gData.planeID);
	gData.mIsReal = 1;
}

static void setStageUnreal() {
	setScrollingBackgroundVisible(gData.planeID);
	setScrollingBackgroundInvisible(gData.realPlaneID);
	gData.mIsReal = 0;
}

void invertStageReality()
{
	if (gData.mIsReal) setStageUnreal();
	else setStageReal();
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
	if (c == COLOR_RED) {
		c = COLOR_DARK_RED;
	}
	else if (c == COLOR_BLUE) {
		c = COLOR_DARK_BLUE;
	}
	else if (c == COLOR_GREEN) {
		c = COLOR_DARK_GREEN;
	}
	else if (c == COLOR_YELLOW) {
		c = COLOR_DARK_YELLOW;
	}

	TextureData* tex;
	if (gData.mIsReal) {
		tex = getBackgroundElementTextureData(gData.realPlaneID, gData.mRealTexture);
		c = COLOR_WHITE;
	}
	else {
		tex = getBackgroundElementTextureData(gData.planeID, gData.mBGTexture);
	}

	p = vecSub(p, gData.mStageOffset);

	drawColoredRectangleToTexture(tex[0], c, makeRectangle((int)p.x, (int)p.y, 2, 2));
}
