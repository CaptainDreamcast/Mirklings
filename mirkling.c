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
#include "explosion.h"

#define MAXIMUM_MIRKLING_AMOUNT 10000

typedef void(*RouteHitCB)(void* tCaller, void* tCollisionData);

typedef struct {
	int mActive;
	int mPhysics;
	int mAnimation;
	int mCollision;
	Collider mCollider;
	double mSpeed;
	Position mTarget;
	Color mColor;
	TextureData* mRealTextures;
	TextureData* mUnrealTextures;

	CollisionData mCollisionData;

	RouteHitCB mRouteHitCB;
	void* mRouteHitCaller;
} Mirkling;

static struct {
	Mirkling mMirklings[MAXIMUM_MIRKLING_AMOUNT];
	int mFreePointer;
	
	double mSpawnY;

	int mAreMirklingsInvisible;

	int mAreReal;
} gData;

void initMirklings() {
	gData.mFreePointer = 0;
	int i;	
	for(i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		gData.mMirklings[i].mActive = 0;
	}

	gData.mSpawnY = -20;
	gData.mAreMirklingsInvisible = 0;
	gData.mAreReal = 0;
}

static void unloadMirkling(Mirkling* e);

static void addMirklingExplosion(Position p) {
	p = vecAdd(p, makePosition(8, 8, 0));
	p.z = 5;
	addExplosion(p, 8);
}

static void mirklingHitByShot(void* mCaller, void* tColData) {
	
	Mirkling* e = mCaller;
	CollisionData* colData = tColData;
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);

	if (colData->mType == getPreciousPeopleCollisionList()) {
		addMirklingExplosion(p);
	}

	addBloodParticles(vecAdd(makePosition(8, 8, 0), p), e->mColor);
	drawBloodOnStage(p, e->mColor);
	addStageHandlerScreenShake(1);
	increaseDeathCount();
	
	if (e->mRouteHitCB) {
		e->mRouteHitCB(e->mRouteHitCaller, tColData);
	}
	
	unloadMirkling(e);
}

static void chooseNewBottomScreenTarget(Mirkling* e) {
	Position p = *getHandledPhysicsPositionReference(e->mPhysics);
	e->mTarget = makePosition(randfrom(40, 600), 1000, 2);
	Vector3D delta = vecNormalize(vecSub(e->mTarget, p));
	stopHandledPhysics(e->mPhysics);
	addAccelerationToHandledPhysics(e->mPhysics, vecScale(delta, e->mSpeed));
}


static Color gPossibleBloodColors[] = { COLOR_RED }; 

static void loadMirkling(Mirkling* e, Position p, double tSpeed) {
	e->mPhysics = addToPhysicsHandler(p);
	e->mSpeed = tSpeed;
	e->mTarget = makePosition(0, 0, 0);
	e->mRealTextures = getMirklingRealTextures();
	e->mUnrealTextures = getMirklingWalkingTextures();
	TextureData* tex;
	if (gData.mAreReal) tex = e->mRealTextures;
	else tex = e->mUnrealTextures;
	e->mAnimation = playAnimationLoop(makePosition(0, 0, 0), tex, getMirklingWalkingAnimation(), makeRectangleFromTexture(tex[0]));
	setAnimationBasePositionReference(e->mAnimation, getHandledPhysicsPositionReference(e->mPhysics));
	setAnimationScreenPositionReference(e->mAnimation, getStagePositionReference());
	setAnimationCenter(e->mAnimation, makePosition(8,8,0));
	if (randfrom(0, 2) < 1) inverseAnimationVertical(e->mAnimation);
	if (gData.mAreMirklingsInvisible) {
		setAnimationScale(e->mAnimation, makePosition(0, 0, 0), makePosition(0, 0, 0));
	}
	e->mCollider = makeColliderFromCirc(makeCollisionCirc(makePosition(8,8,0), 8));
	e->mCollisionData = makeCollisionData(getMirklingsCollisionList());
	e->mCollision = addColliderToCollisionHandler(getMirklingsCollisionList(), getHandledPhysicsPositionReference(e->mPhysics), e->mCollider, mirklingHitByShot, e, &e->mCollisionData);	
	e->mRouteHitCB = NULL;
	e->mRouteHitCaller = NULL;

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
}


void updateMirklings() {
	int i;
	for(i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		if(!gData.mMirklings[i].mActive) continue;

		updateMirkling(&gData.mMirklings[i]);
	}

}

void setMirklingRouteHitCB(int tID, void(*tCB)(void *tCaller, void *tCollisionData), void * tCaller)
{
	Mirkling* e = &gData.mMirklings[tID];
	e->mRouteHitCB = tCB;
	e->mRouteHitCaller = tCaller;
}

void setMirklingSpawnY(double tY)
{
	gData.mSpawnY = tY;
}

void setMirklingsInvisible()
{
	gData.mAreMirklingsInvisible = 1;
}

void setMirklingsVisible()
{
	gData.mAreMirklingsInvisible = 0;
}

static void setSingleMirklingReal(Mirkling* e) {
	changeAnimation(e->mAnimation, e->mRealTextures, getMirklingWalkingAnimation(), makeRectangleFromTexture(e->mRealTextures[0]));
}

static void setSingleMirklingUnreal(Mirkling* e) {
	changeAnimation(e->mAnimation, e->mUnrealTextures, getMirklingWalkingAnimation(), makeRectangleFromTexture(e->mUnrealTextures[0]));
}

static void setMirklingsReal() {
	int i;
	for (i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		if (!gData.mMirklings[i].mActive) continue;

		setSingleMirklingReal(&gData.mMirklings[i]);
	}

	gData.mAreReal = 1;
}

static void setMirklingsUnreal() {
	int i;
	for (i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		if (!gData.mMirklings[i].mActive) continue;

		setSingleMirklingUnreal(&gData.mMirklings[i]);
	}

	gData.mAreReal = 0;
}

void invertMirklingsReality()
{
	if (gData.mAreReal) setMirklingsUnreal();
	else setMirklingsReal();
}

Position getLowestMirklingPosition()
{
	Position lowest = makePosition(0, 0, 0);
	int i;
	for (i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		Mirkling* e = &gData.mMirklings[i];
		if (!e->mActive) continue;

		Position p = *getHandledPhysicsPositionReference(e->mPhysics);
		if (p.y > lowest.y) {
			lowest = p;
		}
	}

	return lowest;
}


static int findFreeMirklingSpotIndex() {
	int i;

	for(i = 0; i < MAXIMUM_MIRKLING_AMOUNT; i++) {
		if(!gData.mMirklings[gData.mFreePointer].mActive) return gData.mFreePointer;
		gData.mFreePointer = (gData.mFreePointer + 1) % MAXIMUM_MIRKLING_AMOUNT;
	}

	logError("Unable to find new free Mirkling spot.");
	abortSystem();

	return -1;
}

void addMirkling(double tSpeed)
{
	int id = findFreeMirklingSpotIndex();
	Mirkling* e = &gData.mMirklings[id];
	loadMirkling(e, makePosition(randfrom(-8, 632), gData.mSpawnY, 2), tSpeed);
	chooseNewBottomScreenTarget(e);
}

int addMirklingManual(Position tPos, Vector3D tDir, double tSpeed)
{
	int id = findFreeMirklingSpotIndex();
	Mirkling* e = &gData.mMirklings[id];
	loadMirkling(e, tPos, tSpeed);
	addAccelerationToHandledPhysics(e->mPhysics, vecScale(tDir, tSpeed));
	return id;
}