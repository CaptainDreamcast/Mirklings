#include "preciouspeople.h"

#include <tari/actorhandler.h>
#include <tari/animation.h>
#include <tari/collisionhandler.h>
#include <tari/stagehandler.h>
#include <tari/tweening.h>
#include <tari/soundeffect.h>
#include <tari/timer.h>
#include <tari/system.h>

#include "stage.h"
#include "collision.h"
#include "pussymode.h"

#define MAX_HEALTH ((int)(100*PERFORMANCE_FACTOR))

typedef struct {
	Position p;
	char* mPath;
	TextureData mTexture;

	int mShadow;
	int mAnimation;
	int mActor;
	int mCollision;
	Collider mCollider;

	double mSqueezeFactor;
	int mSqueeze;

	int mHealth;
	int mHealthBar;

	int mCanScream;

	CollisionData mCollisionData;

	int mIsReal;
} PreciousPerson;

static struct {
	int mPreciousPeopleAmount;
	TextureData mHealthBarTexture;
	TextureData mShadowTexture;
	SoundEffectCollection mScreams;

	int mIsReal;
} gData;

static Animation gPeopleAnimation = {
	.mDuration = 7,
	.mFrameAmount = 1
};

static void squeezeOver(void* tCaller) {
	PreciousPerson* e = tCaller;
	e->mSqueeze = -1;
}

static void addSqueeze(PreciousPerson* e) {
	if (e->mSqueeze != -1) removeTween(e->mSqueeze);
	e->mSqueeze = tweenDouble(&e->mSqueezeFactor, 0.5, 1.0, overshootTweeningFunction, 20, squeezeOver, e);
}

static void updateHealthBar(PreciousPerson* e) {
	if (e->mIsReal) return;
	double healthFac = e->mHealth / (double)MAX_HEALTH;
	setAnimationSize(e->mHealthBar, makePosition(healthFac * 50, 5, 1), makePosition(0, 0, 0));
	if (healthFac > 0.5) setAnimationColorType(e->mHealthBar, COLOR_GREEN);
	else if (healthFac > 0.2) setAnimationColorType(e->mHealthBar, COLOR_YELLOW);
	else setAnimationColorType(e->mHealthBar, COLOR_RED);

}

static void resetScream(void* tCaller) {
	PreciousPerson* e = tCaller;
	e->mCanScream = 1;
}

static void setScream(PreciousPerson* e) {
	if (!e->mCanScream) return;

	playRandomSoundEffectFromCollection(gData.mScreams);

	e->mCanScream = 0;
	addTimerCB(60, resetScream, e);
}


static void preciousPersonHit(void* tCaller, void* tData) {
	(void)tData;
	if (!isInPussyMode()) {
		addStageHandlerScreenShake(2);
	}

	PreciousPerson* e = tCaller;
	e->mHealth--;
	updateHealthBar(e);

	setScream(e);
	addSqueeze(e);

	if (!e->mHealth) {
		increaseScreenShake();
		removeActor(e->mActor);
	}
	
}

static void loadPreciousPerson(void* tData) {
	PreciousPerson* e = tData;
	e->mTexture = loadTexture(e->mPath);
	e->mAnimation = playAnimationLoop(e->p, &e->mTexture, gPeopleAnimation, makeRectangleFromTexture(e->mTexture));
	setAnimationScreenPositionReference(e->mAnimation, getStagePositionReference());

	e->mHealth = MAX_HEALTH;
	e->mHealthBar = playAnimationLoop(vecAdd(e->p, makePosition(5,10,1)), &gData.mHealthBarTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mHealthBarTexture));
	setAnimationScreenPositionReference(e->mHealthBar, getStagePositionReference());
	updateHealthBar(e);

	e->mShadow = playAnimationLoop(vecAdd(e->p, makePosition(0, 42, -0.1)), &gData.mShadowTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mShadowTexture));
	setAnimationScreenPositionReference(e->mShadow, getStagePositionReference());

	e->mCollider = makeColliderFromRect(makeCollisionRect(makePosition(0, 20, 0), makePosition(64, 64, 0)));
	e->mCollisionData = makeCollisionData(getPreciousPeopleCollisionList());
	e->mCollision = addColliderToCollisionHandler(getPreciousPeopleCollisionList(), &e->p, e->mCollider, preciousPersonHit, e, &e->mCollisionData);
	
	e->mSqueezeFactor = 1;
	e->mSqueeze = -1;

	e->mCanScream = 1;
	e->mIsReal = 0;

	gData.mPreciousPeopleAmount++;

}

static void unloadPreciousPerson(void* tData) {
	PreciousPerson* e = tData;
	if (e->mSqueeze != -1) removeTween(e->mSqueeze);

	if (!gData.mIsReal) {
		removeFromCollisionHandler(getPreciousPeopleCollisionList(), e->mCollision);
	}
	
	destroyCollider(&e->mCollider);
	removeHandledAnimation(e->mHealthBar);
	removeHandledAnimation(e->mAnimation);
	removeHandledAnimation(e->mShadow);
	unloadTexture(e->mTexture);
	gData.mPreciousPeopleAmount--;
}

static void setPreciousPersonReal(PreciousPerson* e) {
	setAnimationScale(e->mAnimation, makePosition(0, 0, 1), makePosition(0, 0, 0));
	setAnimationScale(e->mShadow, makePosition(0, 0, 1), makePosition(0, 0, 0));
	setAnimationScale(e->mHealthBar, makePosition(0, 0, 1), makePosition(0, 0, 0));
	removeFromCollisionHandler(getPreciousPeopleCollisionList(), e->mCollision);
	e->mIsReal = 1;
}

static void setPreciousPersonUnreal(PreciousPerson* e) {
	setAnimationScale(e->mAnimation, makePosition(1, 1, 1), makePosition(0, 0, 0));
	setAnimationScale(e->mShadow, makePosition(1, 1, 1), makePosition(0, 0, 0));
	updateHealthBar(e);
	e->mCollision = addColliderToCollisionHandler(getPreciousPeopleCollisionList(), &e->p, e->mCollider, preciousPersonHit, e, &e->mCollisionData);
	e->mIsReal = 0;
}

static void updateReality(PreciousPerson* e) {
	if (e->mIsReal != gData.mIsReal) {
		if (gData.mIsReal) setPreciousPersonReal(e);
		else setPreciousPersonUnreal(e);
	}


}

static void updateBounce(PreciousPerson* e) {
	if (e->mIsReal) return;

	double xfac = 1 + (1 - e->mSqueezeFactor);
	double yfac = e->mSqueezeFactor;
	setAnimationScale(e->mAnimation, makePosition(xfac, yfac, 1), makePosition(32, 32, 0));
	setAnimationScale(e->mShadow, makePosition(xfac, yfac, 1), makePosition(32, -10, 0));
}

static void updatePreciousPerson(void* tData) {
	PreciousPerson* e = tData;

	updateHealthBar(e);
	updateBounce(e);
	updateReality(e);
}

ActorBlueprint PreciousPersonBlueprint = {
	.mLoad = loadPreciousPerson,
	.mUnload = unloadPreciousPerson,
	.mUpdate = updatePreciousPerson
};

static char gPeoplePaths[5][1024] = {
	"assets/precious/HOUSE0.pkg",
	"assets/precious/HOUSE1.pkg",
	"assets/precious/HOUSE2.pkg",
	"assets/precious/HOUSE3.pkg",
	"assets/precious/HOUSE4.pkg"
};

static void loadPreciousPeopleSoundEffects() {
	gData.mScreams = loadConsecutiveSoundEffectsToCollection("assets/sfx/screams/SCREAM.wav", 3);
}

void loadPreciousPeople()
{
	gData.mIsReal = 0;
	gData.mPreciousPeopleAmount = 0;
	resetAnimation(&gPeopleAnimation);
	gData.mHealthBarTexture = loadTexture("assets/debug/collision_rect.pkg");
	gData.mShadowTexture = loadTexture("assets/precious/SHADOW.pkg");
	loadPreciousPeopleSoundEffects();

	int preciousPeopleAmount = 5;
	Position p = makePosition(70, 370, 4);

	int i;
	for (i = 0; i < preciousPeopleAmount; i++) {
		PreciousPerson* e = allocMemory(sizeof(PreciousPerson));
		e->p = p;
		e->mPath = gPeoplePaths[i];
		e->mActor = instantiateActorWithData(PreciousPersonBlueprint, e, 1);
		p.x += 100;
	}


}

int hasPreciousPeopleLeft() {
	return gData.mPreciousPeopleAmount;
}

int getPreciousPeopleAmount()
{
	return gData.mPreciousPeopleAmount;
}

void setPreciousPeopleReal() {
	gData.mIsReal = 1;
}

void setPreciousPeopleUnreal() {
	gData.mIsReal = 0;
}

void invertPreciousPeopleReality()
{
	gData.mIsReal ^= 1;
}
