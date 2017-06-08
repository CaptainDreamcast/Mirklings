#include "collision.h"

#include <tari/collisionhandler.h>

static struct {
	int mShotCollisionList;
	int mMirklingCollisionList;
	int mPreciousPeopleCollisionList;
} gData;

void loadMirklingsCollisions()
{
	gData.mShotCollisionList = addCollisionListToHandler();
	gData.mMirklingCollisionList = addCollisionListToHandler();
	gData.mPreciousPeopleCollisionList = addCollisionListToHandler();
	addCollisionHandlerCheck(gData.mShotCollisionList, gData.mMirklingCollisionList);
	addCollisionHandlerCheck(gData.mPreciousPeopleCollisionList, gData.mMirklingCollisionList);
}

int getShotCollisionList()
{
	return gData.mShotCollisionList;
}

int getMirklingsCollisionList()
{
	return gData.mMirklingCollisionList;
}

int getPreciousPeopleCollisionList()
{
	return gData.mPreciousPeopleCollisionList;
}
