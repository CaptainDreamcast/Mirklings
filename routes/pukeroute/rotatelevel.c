#include "rotatelevel.h"

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>

#include "../standardroute/standard.h"
#include "../../player.h"
#include "../../mirkling.h"

static char gFunnyTexts[][1024] = {
	"You thought screen shake was bad? Check this out:",
};


static struct {
	double mAngle;
	double mAngleDelta;
	int mAngleDir;
} gData;

static void setRandomFunnyText() {
	int amount = (sizeof gFunnyTexts) / sizeof(gFunnyTexts[0]);
	int i = randfromInteger(0, amount - 1);
	setStandardFunnyText(gFunnyTexts[i]);


}


static void loadRotateLevel() {
	setStandardWaveText("Wave 11");
	setRandomFunnyText();
	setStandardLevelMirklingAmount(15000);
	setMirklingSpawnY(-320);
	loadStandard();

	gData.mAngle = 0;
	gData.mAngleDelta = 0;
	gData.mAngleDir = 1;
}

static void unloadRotateLevel() {
	setAnimationHandlerScreenRotationZ(0, makePosition(0,0,0));
	setPlayerShotRotation(0, makePosition(0,0,0));
	setMirklingSpawnY(-20);
}

static void updateRotation() {
	ScreenSize sz = getScreenSize();
	Position center = makePosition(sz.x / 2, sz.y / 2, 0);
	setAnimationHandlerScreenRotationZ(gData.mAngle, center);
	setPlayerShotRotation(gData.mAngle, center);
	gData.mAngle += gData.mAngleDelta;

	gData.mAngleDelta += randfrom(0.001, 0.002)*gData.mAngleDir;
	if (gData.mAngleDelta > 0.1 && gData.mAngleDir == 1) gData.mAngleDir *= -1;
	else if (gData.mAngleDelta < -0.1 && gData.mAngleDir == -1) gData.mAngleDir *= -1;
	else if (randfrom(0, 100) < 2) gData.mAngleDir *= -1;

	
}

static void updateRotateLevel() {
	updateRotation();
	updateStandard();
}


Level RotateLevel = {

	.mLoadLevel = loadRotateLevel,
	.mUpdateLevel = updateRotateLevel,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
	.mUnloadLevel = unloadRotateLevel
};
