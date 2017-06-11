#include "player.h"

#include <tari/input.h>
#include <tari/datastructures.h>
#include <tari/memoryhandler.h>
#include <tari/timer.h>
#include <tari/collisionhandler.h>
#include <tari/soundeffect.h>
#include <tari/stagehandler.h>

#include "collision.h"
#include "stage.h"

typedef struct {
	int mCollisionID;
	Position mPosition;
} Shot;

static struct {
	int mBoomSFX;
	int mCanShoot;
} gData;

static void loadPlayer(void* tData) {
	(void)tData;
	gData.mBoomSFX = loadSoundEffect("assets/sfx/boom.wav");
	gData.mCanShoot = 1;
}

static void shotFinished(void* tCaller) {
	Shot* s = tCaller;
	removeFromCollisionHandler(getShotCollisionList(), s->mCollisionID);
	freeMemory(s);
}

static void addShot(Position p, double r) {
	Shot* s = allocMemory(sizeof(Shot));
	s->mPosition = p;
	Collider c = makeColliderFromCirc(makeCollisionCirc(makePosition(0,0,0), r));
	s->mCollisionID = addColliderToCollisionHandler(getShotCollisionList(), &s->mPosition, c, NULL, NULL, NULL);
	addTimerCB(2, shotFinished, s);
}

static void shoot() {
	Position p = getShotPosition();
	p = vecAdd(p, *getStagePositionReference());
	addShot(p, 200);
	playSoundEffect(gData.mBoomSFX);
	addStageHandlerScreenShake(50);
	
}

static void updatePlayer(void* tData) {
	(void)tData;
	if (!gData.mCanShoot) return;
	
	if (hasShotGunFlank()) {
		shoot();
	}

}

ActorBlueprint PlayerBP = {
	.mLoad = loadPlayer,
	.mUpdate = updatePlayer
};

void pausePlayerShooting()
{
	gData.mCanShoot = 0;
}

void unpausePlayerShooting()
{
	gData.mCanShoot = 1;
}
