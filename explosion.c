#include "explosion.h"

#include <tari/animation.h>
#include <tari/stagehandler.h>
#include <tari/soundeffect.h>

#include "stage.h"

static struct {
	int mBoomSFX;

	Animation mExplosionAnimation;
	TextureData mExplosion[20];
} gData;

void loadExplosions()
{
	gData.mExplosionAnimation = createEmptyAnimation();
	gData.mExplosionAnimation.mFrameAmount = 17;
	gData.mExplosionAnimation.mDuration = 3;
	loadConsecutiveTextures(gData.mExplosion, "assets/effects/EXPLOSION.pkg", gData.mExplosionAnimation.mFrameAmount);
	gData.mBoomSFX = loadSoundEffect("assets/sfx/boom.wav");
}

void addExplosion(Position p, double r) {
	playSoundEffect(gData.mBoomSFX);
	addStageHandlerScreenShake(50);

	double fac = 2.5;
	double cfac = fac / 2;

	p = vecSub(p, makePosition(cfac*r, cfac*r, 0));

	int anim = playAnimation(p, gData.mExplosion, gData.mExplosionAnimation, makeRectangleFromTexture(gData.mExplosion[0]), NULL, NULL);
	setAnimationScreenPositionReference(anim, getStagePositionReference());
	setAnimationSize(anim, makePosition(fac*r, fac*r, 1), makePosition(0, 0, 0));
}
