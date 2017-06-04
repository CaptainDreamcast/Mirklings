#include "mirkling.h"

#include <tari/actorhandler.h>
#include <tari/memoryhandler.h>
#include <tari/physicshandler.h>
#include <tari/animation.h>
#include <tari/math.h>

#include "mirklinghandler.h"
#include "stage.h"

typedef struct {
	int mActor;
	int mPhysics;
	int mAnimation;

} Mirkling;


static void loadMirkling(void* tData) {
	Mirkling* e = tData;
	Position p = makePosition(randfrom(40, 600), -20, 2);
	e->mPhysics = addToPhysicsHandler(p);
	addAccelerationToHandledPhysics(e->mPhysics, makePosition(0, randfrom(0.2, 1), 0));
	e->mAnimation = playAnimationLoop(makePosition(0, 0, 0), getMirklingWalkingTextures(), getMirklingWalkingAnimation(), makeRectangleFromTexture(getMirklingWalkingTextures()[0]));
	setAnimationBasePositionReference(e->mAnimation, getHandledPhysicsPositionReference(e->mPhysics));
	setAnimationScreenPositionReference(e->mAnimation, getStagePositionReference());
}

static void unloadMirkling(void* tData) {
	Mirkling* e = tData;
	removeHandledAnimation(e->mAnimation);
	removeFromPhysicsHandler(e->mPhysics);

}

static void updateMirkling(void* tData) {
	Mirkling* e = tData;
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	
	if (p.y > 480*2+20) {
		removeActor(e->mActor);
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
