#include "stage.h"

#include <stdio.h>

#include <tari/animation.h>
#include <tari/stagehandler.h>
#include <tari/input.h>
#include <tari/sound.h>

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
	gData.mShakeMaximum = 10;
	gData.mShakeMaximum += 10 * (5 - getPreciousPeopleAmount());
	setStageHandlerMaximumScreenShake(gData.mShakeMaximum);
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
	playTrack(1);
	gData.mIsReal = 0;
}

void setStageReal() {
	if (gData.mIsReal) return;
	setScrollingBackgroundVisible(gData.realPlaneID);
	setScrollingBackgroundInvisible(gData.planeID);
	pauseTrack();
	gData.mIsReal = 1;
}

void setStageUnreal() {
	if (!gData.mIsReal) return;
	setScrollingBackgroundVisible(gData.planeID);
	setScrollingBackgroundInvisible(gData.realPlaneID);
	resumeTrack();
	gData.mIsReal = 0;
}

void invertStageReality()
{
	if (gData.mIsReal) setStageUnreal();
	else setStageReal();
}


ActorBlueprint StageBP = {
	.mLoad = loadStage,
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
		return;
	}
	else {
		tex = getBackgroundElementTextureData(gData.planeID, gData.mBGTexture);
	}

	p = vecSub(p, gData.mStageOffset);

	drawColoredRectangleToTexture(tex[0], c, makeRectangle((int)p.x, (int)p.y, 2, 2));
}
