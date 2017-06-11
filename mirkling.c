#include "mirkling.h"

#include <tari/actorhandler.h>
#include <tari/memoryhandler.h>
#include <tari/physicshandler.h>
#include <tari/animation.h>
#include <tari/math.h>
#include <tari/input.h>
#include <tari/collisionhandler.h>
#include <tari/stagehandler.h>
#include <tari/log.h>
#include <tari/system.h>

#include "mirklinghandler.h"
#include "stage.h"
#include "collision.h"
#include "particles.h"
#include "deathcount.h"

#define MAXIMUM_MIRKLING_AMOUNT 10000

typedef struct {
	int mActive;
	int mPhysics;
	int mAnimation;
	int mCollision;
	Collider mCollider;
	double mSpeed;
	Position mTarget;
	Color mColor;
} Mirkling;

static struct {
	Mirkling mMirklings[MAXIMUM_MIRKLING_AMOUNT];
	int mFreePointer;
} gData;

void initMirklings() {
	gData.mFreePointer = 0;
	int i;	
	for(i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		gData.mMirklings[i].mActive = 0;
	}
}

static void unloadMirkling(Mirkling* e);


static void mirklingHitByShot(void* mCaller, void* mColData) {
	(void)mColData;
	
	Mirkling* e = mCaller;
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	addBloodParticles(vecAdd(makePosition(8, 8, 0), p), e->mColor);
	drawBloodOnStage(p, e->mColor);
	addStageHandlerScreenShake(1);
	increaseDeathCount();
	unloadMirkling(e);
}

static void chooseNewTarget(Mirkling* e) {
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	e->mTarget = makePosition(randfrom(40, 600), 1000, 2);
	Vector3D delta = vecNormalize(vecSub(e->mTarget, p));
	stopHandledPhysics(e->mPhysics);
	addAccelerationToHandledPhysics(e->mPhysics, vecScale(delta, e->mSpeed));
}


static Color gPossibleBloodColors[] = {COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW};

static void loadMirkling(Mirkling* e) {
	Position p = makePosition(randfrom(-8, 632), -20, 2);
	
	e->mPhysics = addToPhysicsHandler(p);
	e->mSpeed = randfrom(1, 2);
	chooseNewTarget(e);
	e->mAnimation = playAnimationLoop(makePosition(0, 0, 0), getMirklingWalkingTextures(), getMirklingWalkingAnimation(), makeRectangleFromTexture(getMirklingWalkingTextures()[0]));
	setAnimationBasePositionReference(e->mAnimation, getHandledPhysicsPositionReference(e->mPhysics));
	setAnimationScreenPositionReference(e->mAnimation, getStagePositionReference());
	e->mCollider = makeColliderFromCirc(makeCollisionCirc(makePosition(8,8,0), 8));
	e->mCollision = addColliderToCollisionHandler(getMirklingsCollisionList(), getHandledPhysicsPositionReference(e->mPhysics), e->mCollider, mirklingHitByShot, e, NULL);	
	
	int colorAmount = (sizeof gPossibleBloodColors) / sizeof(Color);
	e->mColor = gPossibleBloodColors[randfromInteger(0, colorAmount - 1)];
	e->mActive = 1;

	increaseMirklingAmount();
}

static void unloadMirkling(Mirkling* e) {
	removeFromCollisionHandler(getMirklingsCollisionList(), e->mCollision);
	destroyCollider(&e->mCollider);
	removeHandledAnimation(e->mAnimation);
	removeFromPhysicsHandler(e->mPhysics);
	e->mActive = 0;
	decreaseMirklingAmountOnScreen();
}

void shutdownMirklings() {
	int i;
	for(i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		if(!gData.mMirklings[i].mActive) continue;

		unloadMirkling(&gData.mMirklings[i]);
	}
}


static void updateMirkling(Mirkling* e) {
	Position* p = getHandledPhysicsPositionReference(e->mPhysics);
	double downY = 480 + 20;

	double t = getLinearInterpolationFactor(-100, downY, p->y);
	p->z = interpolateLinear(2, 3, t);
	
	if (p->y > downY) {
		unloadMirkling(e);
		return;
	}

	if (getDistance2D(*p, e->mTarget) < 2) {
		chooseNewTarget(e);
	}
}


void updateMirklings() {
	int i;
	for(i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		if(!gData.mMirklings[i].mActive) continue;

		updateMirkling(&gData.mMirklings[i]);
	}

}


static Mirkling* findFreeMirklingSpot() {
	int start = gData.mFreePointer++;
	while(gData.mFreePointer != start) {
		if(!gData.mMirklings[gData.mFreePointer].mActive) return &gData.mMirklings[gData.mFreePointer];

		gData.mFreePointer = (gData.mFreePointer + 1) % MAXIMUM_MIRKLING_AMOUNT;
	}

	logError("Unable to find new free Mirkling spot.");
	abortSystem();

	#ifdef DREAMCAST
	return NULL;
	#endif
}

void addMirkling()
{
	Mirkling* e = findFreeMirklingSpot();
	loadMirkling(e);
}
