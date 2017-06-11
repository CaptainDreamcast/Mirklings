#include "preciouspeople.h"

#include <tari/actorhandler.h>
#include <tari/animation.h>
#include <tari/collisionhandler.h>
#include <tari/stagehandler.h>
#include <tari/tweening.h>

#include "stage.h"
#include "collision.h"

#define MAX_HEALTH 100

typedef struct {
	Position p;
	char* mPath;
	TextureData mTexture;

	int mAnimation;
	int mActor;
	int mCollision;
	Collider mCollider;

	double mSqueezeFactor;
	int mSqueeze;

	int mHealth;
	int mHealthBar;

} PreciousPerson;

static struct {
	int mPreciousPeopleAmount;

	TextureData mHealthBarTexture;
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
	double healthFac = e->mHealth / (double)MAX_HEALTH;
	setAnimationSize(e->mHealthBar, makePosition(healthFac * 50, 5, 1), makePosition(0, 0, 0));
	if (healthFac > 0.5) setAnimationColorType(e->mHealthBar, COLOR_GREEN);
	else if (healthFac > 0.2) setAnimationColorType(e->mHealthBar, COLOR_YELLOW);
	else setAnimationColorType(e->mHealthBar, COLOR_RED);

}

static void preciousPersonHit(void* tCaller, void* tData) {
	(void)tData;
	addStageHandlerScreenShake(2);

	PreciousPerson* e = tCaller;
	e->mHealth--;
	updateHealthBar(e);

	addSqueeze(e);

	if (!e->mHealth) {
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

	e->mCollider = makeColliderFromRect(makeCollisionRect(makePosition(0, 20, 0), makePosition(64, 64, 0)));
	e->mCollision = addColliderToCollisionHandler(getPreciousPeopleCollisionList(), &e->p, e->mCollider, preciousPersonHit, e, NULL);
	
	e->mSqueezeFactor = 1;
	e->mSqueeze = -1;

	gData.mPreciousPeopleAmount++;

}

static void unloadPreciousPerson(void* tData) {
	PreciousPerson* e = tData;
	if (e->mSqueeze != -1) removeTween(e->mSqueeze);
	removeFromCollisionHandler(getPreciousPeopleCollisionList(), e->mCollision);
	destroyCollider(&e->mCollider);
	removeHandledAnimation(e->mHealthBar);
	removeHandledAnimation(e->mAnimation);
	unloadTexture(e->mTexture);
	gData.mPreciousPeopleAmount--;
}

static void updatePreciousPerson(void* tData) {
	PreciousPerson* e = tData;
	setAnimationScale(e->mAnimation, makePosition(1 + (1-e->mSqueezeFactor), e->mSqueezeFactor, 1), makePosition(32, 32, 0));
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


void loadPreciousPeople()
{
	gData.mPreciousPeopleAmount = 0;
	resetAnimation(&gPeopleAnimation);
	gData.mHealthBarTexture = loadTexture("assets/debug/collision_rect.pkg");
	
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
