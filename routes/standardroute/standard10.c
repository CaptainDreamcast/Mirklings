#include "standard10.h"

#include <tari/math.h>
#include <tari/texthandler.h>
#include <tari/timer.h>

#include "standard.h"
#include "../../preciouspeople.h"
#include "../../mirklinghandler.h"
#include "../../collision.h"
#include "../../mirkling.h"
#include "../../soundeffect.h"

static struct {
	int mMirkling;

	int mHellText;
} gData;

static void setFunnyText() {
	if (getPreciousPeopleAmount() < 2) {
		setStandardFunnyText("Remember, you could have prevented this. Protect your house. Protect the people precious to you.");
		return;
	}
	
	setStandardFunnyText("Think about this.");
}

static void unleashHell(void* tCaller) {
	(void)tCaller;
	setMirklingSpeed(8, 10);
	setMirklingsGeneratedPerFrame(80);
}

static void setHell() {
	Position p = makePosition(50, 70, 12);
	gData.mHellText = addHandledTextWithBuildup(p, "Now you've made a mistake, buddy", 0, COLOR_WHITE, makePosition(50,50,1), makePosition(0,0,0), makePosition(540, INF, INF), 280, 200);
	setHandledTextSoundEffects(gData.mHellText, getTextSoundEffectCollection());
	addTimerCB(280, unleashHell, NULL);
}

static void specialMirklingHit(void* tCaller, void* tCollisionData) {
	(void)tCaller;
	CollisionData* colData = tCollisionData;

	if (colData->mType == getShotCollisionList()) {
		setHell();
	}
	else {
		setStandardLevelMirklingAmount(0);
	}
}

static void generateSpecialMirkling() {
	Position p = makePosition(320, -70, 3);
	Velocity v = makePosition(0, 0.5, 0);

	gData.mMirkling = addMirklingManual(p, v, 1);
	setMirklingRouteHitCB(gData.mMirkling, specialMirklingHit, NULL);
}

static void loadStandard10() {
	setStandardWaveText("Wave 10");
	setFunnyText();
	setMirklingSpeed(1, 1);
	setMirklingsGeneratedPerFrame(0);
	setStandardLevelMirklingAmount(100000);
	loadStandard();
	setStandardFunnyTextPositionAfterLoad(makePosition(180, 240, 12));

	generateSpecialMirkling();
}


Level StandardLevel10 = {

	.mLoadLevel = loadStandard10,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard
};
