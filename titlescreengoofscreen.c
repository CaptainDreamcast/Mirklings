#include "titlescreengoofscreen.h"

#include <stdio.h>
#include <tari/wrapper.h>
#include <tari/animation.h>
#include <tari/input.h>
#include <tari/soundeffect.h>
#include <tari/sound.h>

#include "titlescreen.h"

static struct {
	TextureData mBGTextureData;

} gData;

static void loadTitleScreenGoofScreen() {
	gData.mBGTextureData = loadTexture("assets/title/GOOF.pkg");
	playOneFrameAnimationLoop(makePosition(0, 0, 1), &gData.mBGTextureData);

	int sfx = loadSoundEffect("assets/sfx/noise/noise.wav");
	playSoundEffect(sfx);
	pauseTrack();
}

static Screen* getTitleScreenGoofScreenNextScreen() {
	if (hasPressedAbortFlank() || hasPressedStartFlank() || hasPressedAFlank() || hasPressedBFlank()) {
		return &TitleScreen;
	}

	return NULL;
}


Screen TitleScreenGoofScreen = {
	.mLoad = loadTitleScreenGoofScreen,
	.mGetNextScreen = getTitleScreenGoofScreenNextScreen,
};