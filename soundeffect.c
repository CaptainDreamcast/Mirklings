#include "soundeffect.h"

#include <tari/file.h>
#include <tari/memoryhandler.h>

static struct {
	SoundEffectCollection mTextSoundEffects;

} gData;

void initGameSoundEffects()
{
	gData.mTextSoundEffects = loadConsecutiveSoundEffectsToCollection("assets/sfx/text/NORMAL.wav", 5);
}

SoundEffectCollection getTextSoundEffectCollection()
{
	return gData.mTextSoundEffects;
}
