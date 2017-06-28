#include "routehandler.h"

#include <tari/math.h>
#include <tari/wrapper.h>

#include "routes/standardroute.h"
#include "routes/pukeroute.h"

#include "levelhandler.h"
#include "route.h"
#include "gameoverscreen.h"
#include "titlescreen.h"

static struct {
	int mCurrentRoute;
	int mAmount;
	int mIsContinuing;
} gData;

static Route* gRoutes[] = {
	//&StandardRoute,
	&PukeRoute,
};

static void resetAllRoutes() {
	int i;
	for (i = 0; i < gData.mAmount; i++) {
		gRoutes[i]->mReset();
	}
}

void reloadRoute() {
	if (gData.mIsContinuing) {
		gData.mIsContinuing = 0;
		return;
	}
	gData.mAmount = (sizeof gRoutes) / sizeof(Route*);

	int i;
	for (i = 0; i < gData.mAmount; i++) {
		gData.mCurrentRoute = randfromInteger(0, gData.mAmount - 1);
		if (gRoutes[gData.mCurrentRoute]->mCanBePlayed()) break;
	}

	if (!gRoutes[gData.mCurrentRoute]->mCanBePlayed()) {
		resetAllRoutes();
		reloadRoute();
	}

}

void startNewRoute() {
	gRoutes[gData.mCurrentRoute]->mLoadRoute();
}

void updateRouteHandler() {
	if (gRoutes[gData.mCurrentRoute]->mHasLost()) {
		setNewScreen(&GameOverScreen);
	}

	gRoutes[gData.mCurrentRoute]->mUpdate();
}

void setCurrentRouteToContinue()
{
	gData.mIsContinuing = 1;
	if (gRoutes[gData.mCurrentRoute]->mSetToContinue) {
		gRoutes[gData.mCurrentRoute]->mSetToContinue();
	}
}
