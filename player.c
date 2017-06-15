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
#include "preciouspeople.h"
#include "explosion.h"

typedef struct {
	int mCollisionID;
	Position mPosition;
	Collider mCollider;
	CollisionData mCollisionData;
} Shot;

static struct {
	int mCanShoot;
} gData;


static void loadPlayer(void* tData) {
	(void)tData;
	gData.mCanShoot = 1;
}

static void shotFinished(void* tCaller) {
	Shot* s = tCaller;
	removeFromCollisionHandler(getShotCollisionList(), s->mCollisionID);
	destroyCollider(&s->mCollider);
	freeMemory(s);
}

static void addShot(Position p, double r) {
	Shot* s = allocMemory(sizeof(Shot));
	s->mPosition = p;
	s->mCollider = makeColliderFromCirc(makeCollisionCirc(makePosition(0,0,0), r));
	s->mCollisionData = makeCollisionData(getShotCollisionList());
	s->mCollisionID = addColliderToCollisionHandler(getShotCollisionList(), &s->mPosition, s->mCollider, NULL, NULL, &s->mCollisionData);
	p.z = 3;
	addExplosion(p, r);
	addTimerCB(2, shotFinished, s);
}


static void shoot() {
	Position p = getShotPosition();
	p = vecAdd(p, *getStagePositionReference());
	addShot(p, 40 * getPreciousPeopleAmount());	
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
