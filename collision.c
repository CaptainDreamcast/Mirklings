#include "collision.h"

#include <tari/collisionhandler.h>

static struct {
	int mShotCollisionList;
	int mMirklingCollisionList;

} gData;

void loadMirklingsCollisions()
{
	gData.mShotCollisionList = addCollisionListToHandler();
	gData.mMirklingCollisionList = addCollisionListToHandler();
	addCollisionHandlerCheck(gData.mShotCollisionList, gData.mMirklingCollisionList);
}

int getShotCollisionList()
{
	return gData.mShotCollisionList;
}

int getMirklingsCollisionList()
{
	return gData.mMirklingCollisionList;
}
