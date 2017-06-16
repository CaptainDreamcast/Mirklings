#include "explosion.h"

#include <tari/animation.h>
#include <tari/stagehandler.h>
#include <tari/soundeffect.h>

#include "stage.h"

static struct {
	int mBoomSFX;

	Animation mExplosionAnimation;
	TextureData mExplosion[10];
} gData;

void loadExplosions()
{
	gData.mExplosionAnimation = createEmptyAnimation();
	gData.mExplosionAnimation.mFrameAmount = 8;
	gData.mExplosionAnimation.mDuration = 3;
	loadConsecutiveTextures(gData.mExplosion, "assets/effects/EXPLOSION.pkg", gData.mExplosionAnimation.mFrameAmount);
	gData.mBoomSFX = loadSoundEffect("assets/sfx/boom.wav");
}

void addExplosion(Position p, double r) {
	playSoundEffect(gData.mBoomSFX);
	addStageHandlerScreenShake(50);

	p = vecSub(p, makePosition(r, r, 0));

	int anim = playAnimation(p, gData.mExplosion, gData.mExplosionAnimation, makeRectangleFromTexture(gData.mExplosion[0]), NULL, NULL);
	setAnimationScreenPositionReference(anim, getStagePositionReference());
	setAnimationSize(anim, makePosition(2*r, 2*r, 1), makePosition(0, 0, 0));
}
