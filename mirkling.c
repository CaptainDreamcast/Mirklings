#include "mirkling.h"

#include <tari/actorhandler.h>
#include <tari/memoryhandler.h>
#include <tari/physicshandler.h>
#include <tari/animation.h>
#include <tari/math.h>
#include <tari/input.h>
#include <tari/collisionhandler.h>

#include "mirklinghandler.h"
#include "stage.h"
#include "collision.h"

typedef struct {
	int mActor;
	int mPhysics;
	int mAnimation;
	int mCollision;
	double mSpeed;
	Position mTarget;
} Mirkling;


static void mirklingHitByShot(void* mCaller, void* mColData) {
	(void)mColData;
	
	Mirkling* e = mCaller;
	removeActor(e->mActor);
}

static void chooseNewTarget(Mirkling* e) {
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	e->mTarget = makePosition(randfrom(40, 600), 928, 2);
	Vector3D delta = vecNormalize(vecSub(e->mTarget, p));
	stopHandledPhysics(e->mPhysics);
	addAccelerationToHandledPhysics(e->mPhysics, vecScale(delta, e->mSpeed));
}

static void loadMirkling(void* tData) {
	Mirkling* e = tData;
	Position p = makePosition(randfrom(40, 600), -20, 2);
	
	e->mPhysics = addToPhysicsHandler(p);
	e->mSpeed = randfrom(0.2, 1);
	chooseNewTarget(e);
	//e->mAnimation = playAnimationLoop(makePosition(0, 0, 0), getMirklingWalkingTextures(), getMirklingWalkingAnimation(), makeRectangleFromTexture(getMirklingWalkingTextures()[0]));
	//setAnimationBasePositionReference(e->mAnimation, getHandledPhysicsPositionReference(e->mPhysics));
	//setAnimationScreenPositionReference(e->mAnimation, getStagePositionReference());
	// Collider c = makeColliderFromCirc(makeCollisionCirc(makePosition(8,8,0), 8));
	// e->mCollision = addColliderToCollisionHandler(getMirklingsCollisionList(), getHandledPhysicsPositionReference(e->mPhysics), c, mirklingHitByShot, e, NULL);
	increaseMirklingAmount();
}

static void unloadMirkling(void* tData) {
	Mirkling* e = tData;
	removeFromCollisionHandler(getMirklingsCollisionList(), e->mCollision);
	removeHandledAnimation(e->mAnimation);
	removeFromPhysicsHandler(e->mPhysics);
	decreaseMirklingAmount();
}

static void updateMirkling(void* tData) {
	Mirkling* e = tData;
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	
	if (p.y > 480*2+20) {
		removeActor(e->mActor);
	}

	if (getDistance2D(p, e->mTarget) < 2) {
		chooseNewTarget(e);
	}
}



static ActorBlueprint MirklingBP = {
	.mLoad = loadMirkling,
	.mUnload = unloadMirkling,
	//.mUpdate = updateMirkling
};


void addMirkling()
{
	Mirkling* e = allocMemory(sizeof(Mirkling));
	e->mActor = instantiateActorWithData(MirklingBP, e, 1);
}
