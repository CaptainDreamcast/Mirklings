#include "titlescreen.h"

#include <stdio.h>

#include <tari/input.h>
#include <tari/animation.h>
#include <tari/texthandler.h>
#include <tari/math.h>

#include "mirklinghandler.h"
#include "stage.h"
#include "collision.h"
#include "gamescreen.h"

static struct {
	TextureData mBGTexture;
	int mBG;

	int mPressStartText;
} gData;

static void loadTitleScreen() {
	gData.mBGTexture = loadTexture("assets/title/TITLE.pkg");
	gData.mBG = playAnimationLoop(makePosition(0, 0, 12), &gData.mBGTexture, createOneFrameAnimation(), makeRectangleFromTexture(gData.mBGTexture));

	Position pressStartPosition = makePosition(20, 300, 13);
	gData.mPressStartText = addHandledTextWithBuildup(pressStartPosition, "Press start and please don't shoot at the title screen because I am the title screen and I generally don't appreciate being shot at", 0, COLOR_WHITE, makePosition(20, 20, 1), makePosition(0, 10, 0), makePosition(600, INF, 0), INF, 60);
	loadMirklingsCollisions();
	instantiateActor(StageBP);
	instantiateActor(MirklingHandlerBP);
}

static Screen* getNextTitleScreenScreen() {
	if (hasPressedAbortFlank()) {
		abortScreenHandling();
	}
	else if (hasPressedStartFlank()) {
		return &GameScreen;
	}

	return NULL;
}

Screen TitleScreen = {
	.mLoad = loadTitleScreen,
	.mGetNextScreen = getNextTitleScreenScreen
};
