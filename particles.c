#include "particles.h"

#include <tari/actorhandler.h>
#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/math.h>

#include "stage.h"

#define MAX_PARTICLE_AMOUNT 500

static struct {
	TextureData mBlood;
	int mAmount;
} gData;

void loadParticles() {
	gData.mBlood = loadTexture("assets/particles/blood.pkg");
	gData.mAmount = 0;
}

typedef struct {
	int mAnimation;
	int mPhysics;
	Duration mNow;
	Duration mDuration;
	int mActor;
	Color mColor;
	double mRotation;
	double mRotationDelta;
	Position mCenter;
} Particle;


static void updateParticle(void* tData) {
	Particle* e = tData;

	e->mRotation += e->mRotationDelta;
	setAnimationRotationZ(e->mAnimation, e->mRotation, e->mCenter);

	if (handleDurationAndCheckIfOver(&e->mNow, e->mDuration)) {
		removeActor(e->mActor);
	}
	
}

static void unloadParticle(void* tData) {
	Particle* e = tData;
	drawBloodOnStage(*getHandledPhysicsPositionReference(e->mPhysics), e->mColor);
	removeHandledAnimation(e->mAnimation);
	removeFromPhysicsHandler(e->mPhysics);
	gData.mAmount--;
	
}

ActorBlueprint ParticleBP = {
	.mUpdate = updateParticle,
	.mUnload = unloadParticle
};

static void addParticle(int tAmount, Position pos, Color tColor, TextureData* tTexture, GeoRectangle tPosRange, GeoRectangle tVelRange, double tMinRotationDelta, double tMaxRotationDelta, Duration tDuration) {
	if (gData.mAmount >= MAX_PARTICLE_AMOUNT) return;

	int i;
	for (i = 0; i < tAmount; i++) {

		double rx = randfrom(tPosRange.mTopLeft.x, tPosRange.mBottomRight.x);
		double ry = randfrom(tPosRange.mTopLeft.y, tPosRange.mBottomRight.y);

		double vx = randfrom(tVelRange.mTopLeft.x, tVelRange.mBottomRight.x);
		double vy = randfrom(tVelRange.mTopLeft.y, tVelRange.mBottomRight.y);

		Particle* p = allocMemory(sizeof(Particle));
		p->mPhysics = addToPhysicsHandler(vecAdd(pos, makePosition(rx, ry, 0)));
		addAccelerationToHandledPhysics(p->mPhysics, makePosition(vx, vy, 0));
		setHandledPhysicsGravity(p->mPhysics, makePosition(0, 0.1, 0));
		p->mRotation = randfrom(-1, 1);
		p->mRotationDelta = randfrom(tMinRotationDelta, tMaxRotationDelta);

		p->mAnimation = playAnimationLoop(makePosition(0,0,0), tTexture, createOneFrameAnimation(), makeRectangleFromTexture(tTexture[0]));
		setAnimationBasePositionReference(p->mAnimation, getHandledPhysicsPositionReference(p->mPhysics));
		setAnimationScreenPositionReference(p->mAnimation, getStagePositionReference());
		setAnimationColorType(p->mAnimation, tColor);
		p->mCenter = makePosition(tTexture->mTextureSize.x / 2, tTexture->mTextureSize.y / 2, 0);
		setAnimationRotationZ(p->mAnimation, p->mRotation, p->mCenter);

		p->mNow = 0;
		p->mDuration = tDuration + randfromInteger(-5 , 5);
		
		p->mColor = tColor;

		p->mActor = instantiateActorWithData(ParticleBP, p, 1);

		gData.mAmount++;
	}

}

void addBloodParticles(Position p, Color c){
	p.z = 5;
	addParticle(2, p, c, &gData.mBlood, makeGeoRectangle(-8 - 4, -8 - 4, -8 + 4, -8 + 4), makeGeoRectangle(-1, -2, 2, 1), -1, 1, 40);
}


