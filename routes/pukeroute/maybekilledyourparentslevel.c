#include "maybekilledyourparentslevel.h"

#include <stdio.h>

#include <tari/math.h>
#include <tari/animation.h>
#include <tari/system.h>
#include <tari/animation.h>
#include <tari/physicshandler.h>
#include <tari/texthandler.h>

#include "../standardroute/standard.h"
#include "willkillyourparentslevel.h"

static void loadPlayForYouLevel() {
	setStandardWaveText("Wave 14");
	int missAmount = getPlayerParentKillMissedMirklingAmount();
	char funnyText[1024];
	if (missAmount) {
		sprintf(funnyText, "You missed %d Mirklings, champ. Hope you told your parents you loved them. Mirklings is serious business, don't let the MS Paint art and edgy humour fool you.", missAmount);
	}
	else {
		sprintf(funnyText, "Woah, you saved your parents. But if you REALLY loved your parents, you would play Mirklings to the end, just saying.");
	}
	setStandardFunnyText(funnyText);
	setStandardLevelMirklingAmount(10000);
	loadStandard();
}

Level MaybeKilledYourParentsLevel = {

	.mLoadLevel = loadPlayForYouLevel,
	.mUpdateLevel = updateStandard,
	.mHasLost = hasLostStandard,
	.mHasWon = hasWonStandard,
};
