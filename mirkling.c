#include "mirkling.h"

#include <tari/actorhandler.h>
#include <tari/memoryhandler.h>
#include <tari/physicshandler.h>
#include <tari/animation.h>
#include <tari/math.h>
#include <tari/input.h>
#include <tari/collisionhandler.h>
#include <tari/stagehandler.h>

#include "mirklinghandler.h"
#include "stage.h"
#include "collision.h"
#include "particles.h"
#include "deathcount.h"

typedef struct {
	int mActor;
	int mPhysics;
	int mAnimation;
	int mCollision;
	Collider mCollider;
	double mSpeed;
	Position mTarget;
	Color mColor;
} Mirkling;


static void mirklingHitByShot(void* mCaller, void* mColData) {
	(void)mColData;
	
	Mirkling* e = mCaller;
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	addBloodParticles(vecAdd(makePosition(8, 8, 0), p), e->mColor);
	drawBloodOnStage(p, e->mColor);
	addStageHandlerScreenShake(1);
	increaseDeathCount();
	removeActor(e->mActor);
}

static void chooseNewTarget(Mirkling* e) {
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	e->mTarget = makePosition(randfrom(40, 600), 1000, 2);
	Vector3D delta = vecNormalize(vecSub(e->mTarget, p));
	stopHandledPhysics(e->mPhysics);
	addAccelerationToHandledPhysics(e->mPhysics, vecScale(delta, e->mSpeed));
}


static Color gPossibleBloodColors[] = {COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW};

static void loadMirkling(void* tData) {
	Mirkling* e = tData;
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

	increaseMirklingAmount();
}

static void unloadMirkling(void* tData) {
	Mirkling* e = tData;
	removeFromCollisionHandler(getMirklingsCollisionList(), e->mCollision);
	destroyCollider(&e->mCollider);
	removeHandledAnimation(e->mAnimation);
	removeFromPhysicsHandler(e->mPhysics);
	decreaseMirklingAmountOnScreen();
}

static void updateMirkling(void* tData) {
	Mirkling* e = tData;
	Position* p = getHandledPhysicsPositionReference(e->mPhysics);
	double downY = 480 + 20;

	double t = getLinearInterpolationFactor(-100, downY, p->y);
	p->z = interpolateLinear(2, 3, t);
	
	if (p->y > downY) {
		removeActor(e->mActor);
		return;
	}

	if (hasPressedA()) {
		mirklingHitByShot(e, NULL);
		return;
	}

	if (getDistance2D(*p, e->mTarget) < 2) {
		chooseNewTarget(e);
	}
}



static ActorBlueprint MirklingBP = {
	.mLoad = loadMirkling,
	.mUnload = unloadMirkling,
	.mUpdate = updateMirkling
};


void addMirkling()
{
	Mirkling* e = allocMemory(sizeof(Mirkling));
	e->mActor = instantiateActorWithData(MirklingBP, e, 1);
}
