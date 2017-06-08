#include "preciouspeople.h"

#include <tari/actorhandler.h>
#include <tari/animation.h>
#include <tari/collisionhandler.h>
#include <tari/stagehandler.h>

#include "stage.h"
#include "collision.h"

typedef struct {
	Position p;
	char* mPath;
	TextureData mTexture;

	int mAnimation;
	int mActor;
	int mCollision;
	Collider mCollider;

	int mHealth;

} PreciousPerson;

static struct {
	int mPreciousPeopleAmount;
} gData;

static Animation gPeopleAnimation = {
	.mDuration = 7,
	.mFrameAmount = 1
};

static void preciousPersonHit(void* tCaller, void* tData) {
	(void)tData;
	addStageHandlerScreenShake(1);

	PreciousPerson* e = tCaller;
	e->mHealth--;

	if (!e->mHealth) {
		removeActor(e->mActor);
	}
}

static void loadPreciousPerson(void* tData) {
	PreciousPerson* e = tData;
	e->mTexture = loadTexture(e->mPath);
	e->mAnimation = playAnimationLoop(e->p, &e->mTexture, gPeopleAnimation, makeRectangleFromTexture(e->mTexture));
	setAnimationScreenPositionReference(e->mAnimation, getStagePositionReference());
	e->mCollider = makeColliderFromRect(makeCollisionRect(makePosition(0, 0, 0), makePosition(64, 64, 0)));
	e->mCollision = addColliderToCollisionHandler(getPreciousPeopleCollisionList(), &e->p, e->mCollider, preciousPersonHit, e, NULL);
	e->mHealth = 100;
	gData.mPreciousPeopleAmount++;

}

static void unloadPreciousPerson(void* tData) {
	PreciousPerson* e = tData;
	removeFromCollisionHandler(getPreciousPeopleCollisionList(), e->mCollision);
	destroyCollider(&e->mCollider);
	removeHandledAnimation(e->mAnimation);
	unloadTexture(e->mTexture);
	gData.mPreciousPeopleAmount--;
}

ActorBlueprint PreciousPersonBlueprint = {
	.mLoad = loadPreciousPerson,
	.mUnload = unloadPreciousPerson
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
