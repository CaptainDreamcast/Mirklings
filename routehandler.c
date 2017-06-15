#include "routehandler.h"

#include <tari/math.h>
#include <tari/wrapper.h>

#include "routes/standardroute.h"
#include "levelhandler.h"
#include "route.h"
#include "gameoverscreen.h"
#include "titlescreen.h"

static struct {
	int mCurrentRoute;
	int mAmount;
} gData;

static Route* gRoutes[] = {
	&StandardRoute,
};

static void resetAllRoutes() {
	int i;
	for (i = 0; i < gData.mAmount; i++) {
		gRoutes[i]->mReset();
	}
}

void reloadRoute() {
	gData.mAmount = (sizeof gRoutes) / sizeof(Route*);

	int i;
	for (i = 0; i < gData.mAmount; i++) {
		gData.mCurrentRoute = randfromInteger(0, gData.mAmount - 1);
		if (gRoutes[gData.mCurrentRoute]->mCanBePlayed) break;
	}

	if (!gRoutes[gData.mCurrentRoute]->mCanBePlayed) {
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