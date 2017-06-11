#include "deathcount.h"

#include <tari/texthandler.h>

static struct {
	int mDeathCountText;
	int mDeathCount;
} gData;


static void loadDeathCount(void* tData) {
	(void)tData;

	gData.mDeathCount = 0;
	gData.mDeathCount = addHandledTextWithInfiniteDurationOnOneLine(makePosition(20, 20, 15), "Death Count: 0", 0, COLOR_YELLOW, makePosition(20, 20, 1));

}

static void updateDeathCount(void* tData) {
	(void)tData;

	char nText[1024];
	sprintf(nText, "Death Count: %d", gData.mDeathCount);
	setHandledText(gData.mDeathCountText, nText);
}

ActorBlueprint DeathCountBP = {
	.mLoad = loadDeathCount,
	.mUpdate = updateDeathCount
};

void increaseDeathCount()
{
	gData.mDeathCount++;
}

void resetDeathCount()
{
	gData.mDeathCount = 0;
}
